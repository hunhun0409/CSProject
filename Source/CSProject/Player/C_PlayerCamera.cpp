// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PlayerCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "Curves/CurveVector.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Environment/C_GameModeBase.h"
#include "C_UserWidget.h"
#include "Environment/C_Field.h"
#include "Environment/C_Base_V2.h"
#include "Environment/C_HUD.h"

// Sets default values
AC_PlayerCamera::AC_PlayerCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SetRootComponent(SpringArm);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");

}

// Called when the game starts or when spawned
void AC_PlayerCamera::BeginPlay()
{
	Super::BeginPlay();

	if (auto* GameMode = Cast<AC_GameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		if (!GameMode->UIDataUpdated.IsBound())
		{
			GameMode->UIDataUpdated.BindUFunction(this, "UpdateUIData");
			CameraMovableY = GameMode->GetMaxYPos();
			FVector StartPoint = GetActorLocation();
			StartPoint.Y = CameraMovableY.Y;
			SetActorLocation(StartPoint);
			GetUIData.BindUFunction(GameMode, "GetUIData");
			//SpawnOrder.BindUFunction(GameMode, "SpawnCharacter");
			SpawnOrder.BindUFunction(GameMode->GetField()->AccessBaseData(1), "SpawnCharacter");
			ShowAreaOrder.BindUFunction(GameMode, "SetVisiblePlayerSpawnableArea");
			GameMode->SpawnDamageHUD.BindUFunction(this, "SpawnDamageHUD");
		}

		Datas = GameMode->GetUIData();
	}
	
	if (ZoomCurve)
	{
		NewSocketOffsetZ = ZoomCurve->GetVectorValue(0).X;
		NewFieldOfView = ZoomCurve->GetVectorValue(0).Z;
	}

	UpdateUIData();
	
	if (UIWidgetClass)
	{
		UIWidget = Cast<UC_UserWidget>(CreateWidget(GetWorld()->GetFirstPlayerController(), UIWidgetClass, "UIWidget"));

		if (UIWidget)
		{
			UIWidget->AddToViewport();
			UIWidget->UpdateUIData(Datas);

			UIWidget->SpawnOrdered.BindUFunction(this, "Spawn");
			UIWidget->SelectedPreview.BindUFunction(this, "Preview");
			UIWidget->CancelPreview.BindUFunction(this, "CancelSelect");
		}
	}

	if (auto* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (auto* HUD = Cast<AC_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
		{
			DamageText.BindUFunction(HUD, "AddDamageText");
			UpdateHUDCamreaPos.BindUFunction(HUD, "SetCameraPos");
			UpdateHUDCamreaPos.ExecuteIfBound(GetActorLocation());
		}
	}
}

// Called every frame
void AC_PlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ī�޶� �� �� �̵�
	if (abs(CameraMovement) <= 0.01f)
		CameraMovement = 0;
	else
	{
		if (GetActorLocation().Y <= CameraMovableY.Y)
		{
			if (CameraMovement < 0)
				CameraMovement = 0;
		}
		else if (GetActorLocation().Y >= CameraMovableY.X)
		{
				if (CameraMovement > 0)
					CameraMovement = 0;
		}

		CameraMovement = UKismetMathLibrary::FInterpTo(CameraMovement, 0, 0.1f, 0.5f);

		UpdateHUDCamreaPos.ExecuteIfBound(GetActorLocation());

		AddMovementInput(FVector(0, CameraMovement, 0));
	}

	// ī�޶� ���� �������� ����
	if (abs(SpringArm->SocketOffset.Z - NewSocketOffsetZ) <= 0.01f)
		SpringArm->SocketOffset.Z = NewSocketOffsetZ;
	else
		SpringArm->SocketOffset.Z = UKismetMathLibrary::FInterpTo(SpringArm->SocketOffset.Z, NewSocketOffsetZ, 0.2f, 0.5f);

	//ī�޶� ���� FOV
	if (abs(Camera->FieldOfView - NewFieldOfView) <= 0.01f)
		Camera->FieldOfView = NewFieldOfView;
	else
		Camera->FieldOfView = UKismetMathLibrary::FInterpTo(Camera->FieldOfView, NewFieldOfView, 0.2f, 0.5f);

	//��ȯ Preview
	if (CalculatePreviewLoc)
	{
		if(FindCurserHitResult.IsBound())
			SpawnLocation = FindCurserHitResult.Execute().Location;

		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), SpawnLocation);
	}
}

// Called to bind functionality to input
void AC_PlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AC_PlayerCamera::Zoom(const float& Value)
{
	if (!ZoomCurve)
		return;

	if (ZoomTime <= 0)
		ZoomTime = 0;
	else if (ZoomTime >= 10.0f)
		ZoomTime = 10.0f;
	ZoomTime += Value;

	FVector ZoomCurveData = ZoomCurve->GetVectorValue(ZoomTime);
	
	NewSocketOffsetZ = ZoomCurveData.X;
	NewFieldOfView = ZoomCurveData.Z;
}

void AC_PlayerCamera::KeyBoardCameraMove(const float& Value)
{
	CameraMovement = Value;
}

void AC_PlayerCamera::MouseDelta(const FVector2D& MouseDelta)
{
	CameraMovement = -MouseDelta.X * 10.0f;
}

void AC_PlayerCamera::MousePos(const FVector2D& MousePos)
{
	if (UIWidget)
		UIWidget->UpdateMousePos(MousePos);
}

void AC_PlayerCamera::MouseLBPressing(const bool& IsPressing)
{
	//������ Widget�� ���� ����, ���� ���� ����. ��ġ������ �����ϸ� Click, �ٸ��� Press�� �Ǻ�
	// ���� �Ƶ� Release���� ��ȯ Ȯ��

	if (UIWidget)
		UIWidget->UpdateMouseLBPressing(IsPressing);

}

void AC_PlayerCamera::MouseRBPressing(const bool& IsPressing)
{
	
}

void AC_PlayerCamera::KeyNumPress(const int& KeyNum)
{
	//UIWidget�� Click�� �ش��ϴ� Keynum��� ����
	if (UIWidget)
		UIWidget->KeyBoardNumPress(KeyNum);
}

void AC_PlayerCamera::UpdateUIData()
{
	if(GetUIData.IsBound())
		Datas = GetUIData.Execute();

	if (UIWidget)
		UIWidget->UpdateUIData(Datas);
}

void AC_PlayerCamera::Spawn(int SlotNum)
{
	//GameMode�� Location�� ����. ���� ���� Field�� Collider ���θ� Spawn + CostReduce

	CalculatePreviewLoc = false;

	SpawnOrder.ExecuteIfBound(SpawnLocation, SlotNum + 1, true);
	ShowAreaOrder.ExecuteIfBound(false);
}

void AC_PlayerCamera::Preview(int SlotNum)
{
	SelectedSlot = SlotNum;
	CalculatePreviewLoc = true;

	ShowAreaOrder.ExecuteIfBound(true);
	//SpawnLocation ��� <- Tick���� �ǽð� �浹
}

void AC_PlayerCamera::CancelSelect()
{
	CalculatePreviewLoc = false;
	
	ShowAreaOrder.ExecuteIfBound(false);
}

void AC_PlayerCamera::SpawnDamageHUD(const float& FinalDamage, const bool& bCrit, const bool& bEvade, const FVector& ActorLocation)
{
	FVector2D ScreenPosition;

	if (auto* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		PlayerController->ProjectWorldLocationToScreen(ActorLocation + FVector(0, 0, 100), ScreenPosition);

		DamageText.ExecuteIfBound(FinalDamage, bCrit, bEvade, ScreenPosition);

	}

}
