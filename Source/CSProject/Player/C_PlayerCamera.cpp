// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PlayerCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Curves/CurveVector.h"
#include "Kismet/KismetMathLibrary.h"
#include "C_GameModeBase.h"
#include "../Environment/C_Field.h"
#include "../Environment/C_Base.h"

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
	
	if (ZoomCurve)
	{
		NewSocketOffsetZ = ZoomCurve->GetVectorValue(0).X;
		NewFieldOfView = ZoomCurve->GetVectorValue(0).Z;
	}

	UpdateUIData();

}

// Called every frame
void AC_PlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (abs(CameraMovement) <= 0.01)
		CameraMovement = 0;
	else
		CameraMovement = UKismetMathLibrary::FInterpTo(CameraMovement, 0.0f, 0.1f, 0.5f);

	AddMovementInput(FVector(0.0f, CameraMovement, 0.0f));

	SpringArm->SocketOffset.Z = UKismetMathLibrary::FInterpTo(SpringArm->SocketOffset.Z, NewSocketOffsetZ, 0.2f, 0.5f);
	Camera->FieldOfView = UKismetMathLibrary::FInterpTo(Camera->FieldOfView, NewFieldOfView, 0.2f, 0.5f);

}

// Called to bind functionality to input
void AC_PlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AC_PlayerCamera::BeginCharacterSelect()
{
}

void AC_PlayerCamera::EndCharacterSelect()
{
}

void AC_PlayerCamera::Zoom(const float Value)
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

void AC_PlayerCamera::KeyBoardCameraMove(const float Value)
{
	CameraMovement = Value;
}

void AC_PlayerCamera::MouseDelta(const float DeltaX, const float DeltaY)
{
	CameraMovement = -DeltaX;
}

void AC_PlayerCamera::UpdateUIData()
{
	if (auto* GameMode = Cast<AC_GameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		if(!GameMode->UIDataUpdated.IsBound())
			GameMode->UIDataUpdated.BindUFunction(this, "UpdateUIData");

		Datas = GameMode->GetUIData();
	}
}
