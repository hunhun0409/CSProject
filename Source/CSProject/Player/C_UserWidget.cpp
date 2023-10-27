// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/C_UserWidget.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Components/Image.h"
#include "Components/PanelSlot.h"

void UC_UserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UC_UserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (CostMaterialInstance)
		CostMaterialInstanceDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(
			this, CostMaterialInstance);

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

	for (int i = 0; i < UnitButtonName.Num(); i++)
	{
		UnitButton.Emplace(Cast<UImage>(GetWidgetFromName(UnitButtonName[i])));
	}

	//if(!Button1.IsNone())
	//	UnitButton1 = Cast<UImage>(GetWidgetFromName(Button1));

	//if(!Button2.IsNone())
	//	UnitButton2 = Cast<UImage>(GetWidgetFromName(Button2));

	//if(!Button3.IsNone())
	//	UnitButton3 = Cast<UImage>(GetWidgetFromName(Button3));

	//if(!Button4.IsNone())
	//	UnitButton4 = Cast<UImage>(GetWidgetFromName(Button4));

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
	for (int i = 0; i < UnitButton.Num(); i++)
	{
		if(UIData.UnitImage.IsValidIndex(i))
			UnitButton[i]->SetBrushFromTexture(UIData.UnitImage[i]);
		//해당 값으로 GrayScale Material 설정. UIData.UnitOnFieldData.Find(UIData.ButtonUnitName[i]);
	}
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

	if (!UnitSelected)
	{
		if (IsPressing)
		{
			//Press
			ClickedPos = MousePos;
			// UnitButton 위치 체크하여 tint
			for (int i = 0; i < UnitButton.Num(); i++)
				if (IsMousePosInUImage(UnitButton[i]))
				{
					SetUnitButtonSelect(true, i);
					break;
				}

			if (UnitSelected)
				SelectedPreview.ExecuteIfBound(ButtonNum);
		}
	}
	else
	{
		if (IsPressing)
		{
			ClickedPos = MousePos;

			bool ButtonPressed = false;

			for (int i = 0; i < UnitButton.Num(); i++)
			{
				if (IsMousePosInUImage(UnitButton[i]))
				{
					SetUnitButtonSelect(true, i);
					ButtonPressed = true;
					break;
				}
			}

			if (!ButtonPressed)
			{
				SetUnitButtonSelect(false);

				SpawnOrdered.ExecuteIfBound(ButtonNum);
			}
		}
		else
		{
			if (ClickedPos.Equals(MousePos, 1.0f))
			{
				//Click
				// unit selected 유지
				if(UnitSelected)
					SelectedPreview.ExecuteIfBound(ButtonNum);

			}
			else
			{
				//Release
				// spawn unit, selected 해제
				SetUnitButtonSelect(false);

				SpawnOrdered.ExecuteIfBound(ButtonNum);
			}
		}
	}
}

void UC_UserWidget::KeyBoardNumPress(const int& InNum)
{
	switch (InNum)
	{
	case 0:
		if (ButtonNum == 1 && UnitSelected)
			SetUnitButtonSelect(false);
		else
			SetUnitButtonSelect(true, 1);
		break;
	case 1:
		if (ButtonNum == 2 && UnitSelected)
			SetUnitButtonSelect(false);
		else
			SetUnitButtonSelect(true, 2);
		break;
	case 2:
		if (ButtonNum == 3 && UnitSelected)
			SetUnitButtonSelect(false);
		else
			SetUnitButtonSelect(true, 3);
		break;
	case 3:
		if (ButtonNum == 4 && UnitSelected)
			SetUnitButtonSelect(false);
		else
			SetUnitButtonSelect(true, 4);
		break;
	default:
		break;
	}

	if (UnitSelected)
		SelectedPreview.ExecuteIfBound(ButtonNum);
	else
		CancelPreview.ExecuteIfBound();
}

void UC_UserWidget::RBEvent(bool IsPressed)
{
	
}

bool UC_UserWidget::IsMousePosInUImage(UImage* Target)
{
	FVector2D LT = Target->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D::ZeroVector);
	FVector2D RB = LT + Target->GetCachedGeometry().GetLocalSize();

	if (MousePos >= LT && MousePos <= RB)
		return true;
	else
		return false;
}

void UC_UserWidget::SetUnitButtonSelect(const bool& Selected, const int& ButtonNumber)
{
	UnitSelected = Selected;
	if (UnitSelected)
	{
		ButtonNum = ButtonNumber;
		for (int i = 0; i < UnitButton.Num(); i++)
		{
			if (i == ButtonNum)
				UnitButton[i]->SetRenderScale(FVector2D(1.1f));
			else
				UnitButton[i]->SetRenderScale(FVector2D(1.0f));
		}
	}
	else
	{
		for (int i = 0; i < UnitButton.Num(); i++)
			UnitButton[i]->SetRenderScale(FVector2D(1.0f));
	}
}
