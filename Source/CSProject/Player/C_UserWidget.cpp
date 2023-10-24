// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/C_UserWidget.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Components/Image.h"
#include "Components/PanelSlot.h"
#include "C_PlayerCamera.h"

void UC_UserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UC_UserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (CostMaterialInstance)
	{
		CostMaterialInstanceDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(
			this, CostMaterialInstance);
	}

}

void UC_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!CostImage.IsNone())
	{
		CostWidget = Cast<UImage>(GetWidgetFromName(CostImage));
		CostWidget->SetBrushFromMaterial(CostMaterialInstanceDynamic);
	}

	if (!MouseImage.IsNone())
	{
		MouseWidget = Cast<UImage>(GetWidgetFromName(MouseImage));
		MouseWidget->SetBrushFromTexture(MouseCurserNClick);
	}

	if(!Button1.IsNone())
	{
		UnitButton1 = Cast<UImage>(GetWidgetFromName(Button1));
	}

	if(!Button2.IsNone())
	{
		UnitButton2 = Cast<UImage>(GetWidgetFromName(Button2));

	}

	if(!Button3.IsNone())
	{
		UnitButton3 = Cast<UImage>(GetWidgetFromName(Button3));

	}

	if(!Button4.IsNone())
	{
		UnitButton4 = Cast<UImage>(GetWidgetFromName(Button4));

	}

	if (auto* Player = Cast<AC_PlayerCamera>(GetOwningPlayerPawn()))
	{
		Player->RBPressed.BindUFunction(this, "RBEvent");
	}
	//UImage에 UTexture2D는 Character로부터 받아 변경. Press 입력을 받으면 Release 될때가지 마우스 위치에 있던
	//Image의 Tint를 조정. 만약 소환된 Character면 어둡게 표시. <- 정보 받아야 함.
}

void UC_UserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CostMaterialInstanceDynamic)
	{
		float CostPercent = CostMaterialInstanceDynamic->K2_GetScalarParameterValue(CostPercentParamName);

		float NewCostPercent = CostPercent + CostRegenRatio * InDeltaTime;

		if (CurCost >= 10.0f)
			NewCostPercent = 1.0f;
		else if (NewCostPercent > 1.0f)
			NewCostPercent = 0.0f;

		CostMaterialInstanceDynamic->SetScalarParameterValue(CostPercentParamName, NewCostPercent);
	}

}

void UC_UserWidget::UpdateUIData(const FUIData& UIData)
{
	CurCost = UIData.CurCost;
	PlayerBaseHP = UIData.PlayerBaseHP;
	EnemyBaseHP = UIData.EnemyBaseHP;
	CostRegenRatio = UIData.CostRegenRatio;
}

void UC_UserWidget::UpdateMousePos(const FVector2D& InMousePos)
{
	FWidgetTransform Transform;
	MousePos = InMousePos * 1.5f;
	Transform.Translation = MousePos;
	
	MouseWidget->SetRenderTransform(Transform);
	
}

void UC_UserWidget::UpdateMouseLBPressing(const bool& IsPressing)
{
	if (MouseWidget)
	{
		if (IsPressing)
			MouseWidget->SetBrushFromTexture(MouseCurserClick);
		else
			MouseWidget->SetBrushFromTexture(MouseCurserNClick);

	}
}

void UC_UserWidget::RBEvent(bool IsPressed)
{
	if (!UnitSelected)
	{
		if (IsPressed)
		{
			//Press
			ClickedPos = MousePos;
			// UnitButton 위치 체크하여 tint
			//IsMousePosInUImage(CostWidget);
			if (IsMousePosInUImage(UnitButton1))
			{
				//1번 유닛 선택
				UnitButton1->SetRenderScale(FVector2D(1.1f));
				UnitSelected = true;
				ButtonNum = 1;
			}
			else if (IsMousePosInUImage(UnitButton2))
			{
				//2
				
				UnitButton2->SetRenderScale(FVector2D(1.1f));
				UnitSelected = true;
				ButtonNum = 2;

			}
			else if (IsMousePosInUImage(UnitButton3))
			{
				//3
				UnitButton3->SetRenderScale(FVector2D(1.1f));
				UnitSelected = true;
				ButtonNum = 3;

			}
			else if (IsMousePosInUImage(UnitButton4))
			{
				//4
				UnitButton4->SetRenderScale(FVector2D(1.1f));
				UnitSelected = true;
				ButtonNum = 4;

			}
		}
	}
	else
	{
		if (IsPressed)
		{
			//Spawn Unit, Selected 해제.
			UnitButton1->SetRenderScale(FVector2D(1.0f));
			UnitButton2->SetRenderScale(FVector2D(1.0f));
			UnitButton3->SetRenderScale(FVector2D(1.0f));
			UnitButton4->SetRenderScale(FVector2D(1.0f));

			UnitSelected = false;
		}
		else
		{
			if (ClickedPos.Equals(MousePos, 1.0f))
			{
				//Click
				// unit selected 유지
			}
			else
			{
				//Release
				// spawn unit, selected 해제
				UnitButton1->SetRenderScale(FVector2D(1.0f));
				UnitButton2->SetRenderScale(FVector2D(1.0f));
				UnitButton3->SetRenderScale(FVector2D(1.0f));
				UnitButton4->SetRenderScale(FVector2D(1.0f));

				UnitSelected = false;
			}
		}
	}
}

bool UC_UserWidget::IsMousePosInUImage(UImage* Target)
{
	FVector2D LT = Target->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D::ZeroVector);
	FVector2D RB = LT + Target->GetCachedGeometry().GetLocalSize();

	if (MousePos >= LT && MousePos <= RB)
	{
		return true;
	}
	else
	{
		return false;
	}
}
