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

	if(!Button1.IsNone())
		UnitButton1 = Cast<UImage>(GetWidgetFromName(Button1));

	if(!Button2.IsNone())
		UnitButton2 = Cast<UImage>(GetWidgetFromName(Button2));

	if(!Button3.IsNone())
		UnitButton3 = Cast<UImage>(GetWidgetFromName(Button3));

	if(!Button4.IsNone())
		UnitButton4 = Cast<UImage>(GetWidgetFromName(Button4));

	//UImage�� UTexture2D�� Character�κ��� �޾� ����. Press �Է��� ������ Release �ɶ����� ���콺 ��ġ�� �ִ�
	//Image�� Tint�� ����. ���� ��ȯ�� Character�� ��Ӱ� ǥ��. <- ���� �޾ƾ� ��.
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

	if (!UnitSelected)
	{
		if (IsPressing)
		{
			//Press
			ClickedPos = MousePos;
			// UnitButton ��ġ üũ�Ͽ� tint
			if (IsMousePosInUImage(UnitButton1))
				SetUnitButtonSelect(true, 1);
			else if (IsMousePosInUImage(UnitButton2))
				SetUnitButtonSelect(true, 2);
			else if (IsMousePosInUImage(UnitButton3))
				SetUnitButtonSelect(true, 3);
			else if (IsMousePosInUImage(UnitButton4))
				SetUnitButtonSelect(true, 4);

			if (UnitSelected)
				SelectedPreview.ExecuteIfBound(ButtonNum);
		}
	}
	else
	{
		if (IsPressing)
		{
			ClickedPos = MousePos;

			if (ButtonNum != 1 && IsMousePosInUImage(UnitButton1))
				SetUnitButtonSelect(true, 1);
			else if (ButtonNum != 2 && IsMousePosInUImage(UnitButton2))
				SetUnitButtonSelect(true, 2);
			else if (ButtonNum != 3 && IsMousePosInUImage(UnitButton3))
				SetUnitButtonSelect(true, 3);
			else if (ButtonNum != 4 && IsMousePosInUImage(UnitButton4))
				SetUnitButtonSelect(true, 4);
			else
			{
				//Spawn Unit, Selected ����.
				SetUnitButtonSelect(false);

				SpawnOrdered.ExecuteIfBound(ButtonNum);
			}
		}
		else
		{
			if (ClickedPos.Equals(MousePos, 1.0f))
			{
				//Click
				// unit selected ����
				if(UnitSelected)
					SelectedPreview.ExecuteIfBound(ButtonNum);

			}
			else
			{
				//Release
				// spawn unit, selected ����
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
		switch (ButtonNum)
		{
		case 1:
			UnitButton1->SetRenderScale(FVector2D(1.1f));
			UnitButton2->SetRenderScale(FVector2D(1.0f));
			UnitButton3->SetRenderScale(FVector2D(1.0f));
			UnitButton4->SetRenderScale(FVector2D(1.0f));
			break;
		case 2:
			UnitButton1->SetRenderScale(FVector2D(1.0f));
			UnitButton2->SetRenderScale(FVector2D(1.1f));
			UnitButton3->SetRenderScale(FVector2D(1.0f));
			UnitButton4->SetRenderScale(FVector2D(1.0f));
			break;
		case 3:
			UnitButton1->SetRenderScale(FVector2D(1.0f));
			UnitButton2->SetRenderScale(FVector2D(1.0f));
			UnitButton3->SetRenderScale(FVector2D(1.1f));
			UnitButton4->SetRenderScale(FVector2D(1.0f));
			break;
		case 4:
			UnitButton1->SetRenderScale(FVector2D(1.0f));
			UnitButton2->SetRenderScale(FVector2D(1.0f));
			UnitButton3->SetRenderScale(FVector2D(1.0f));
			UnitButton4->SetRenderScale(FVector2D(1.1f));
			break;
		default:
			break;
		}
	}
	else
	{
		UnitButton1->SetRenderScale(FVector2D(1.0f));
		UnitButton2->SetRenderScale(FVector2D(1.0f));
		UnitButton3->SetRenderScale(FVector2D(1.0f));
		UnitButton4->SetRenderScale(FVector2D(1.0f));
	}
}
