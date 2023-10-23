// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/C_UserWidget.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Components/Image.h"
#include "Components/PanelSlot.h"
#include "Components/Button.h"

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

	if (!Button1.IsNone())
	{
		UnitButton1 = Cast<UButton>(GetWidgetFromName(Button1));
		UnitButton1->OnClicked.AddDynamic(this, &ThisClass::Button1Clicked);
		UnitButton1->OnPressed.AddDynamic(this, &ThisClass::Button1Pressed);
		UnitButton1->OnReleased.AddDynamic(this, &ThisClass::Button1Released);
		
	}

	if (!Button2.IsNone())
	{
		UnitButton2 = Cast<UButton>(GetWidgetFromName(Button2));
		UnitButton2->OnClicked.AddDynamic(this, &ThisClass::Button2Clicked);
		UnitButton2->OnPressed.AddDynamic(this, &ThisClass::Button2Pressed);
		UnitButton2->OnReleased.AddDynamic(this, &ThisClass::Button2Released);

	}

	if (!Button3.IsNone())
	{
		UnitButton3 = Cast<UButton>(GetWidgetFromName(Button3));
		UnitButton3->OnClicked.AddDynamic(this, &ThisClass::Button3Clicked);
		UnitButton3->OnPressed.AddDynamic(this, &ThisClass::Button3Pressed);
		UnitButton3->OnReleased.AddDynamic(this, &ThisClass::Button3Released);

	}

	if (!Button4.IsNone())
	{
		UnitButton4 = Cast<UButton>(GetWidgetFromName(Button4));
		UnitButton4->OnClicked.AddDynamic(this, &ThisClass::Button4Clicked);
		UnitButton4->OnPressed.AddDynamic(this, &ThisClass::Button4Pressed);
		UnitButton4->OnReleased.AddDynamic(this, &ThisClass::Button4Released);

	}

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
	Transform.Translation = InMousePos * 1.5f;
	
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

void UC_UserWidget::Button1Clicked()
{
	//Pawn에게 Selected 1, true
	//true면 Pawn에서 다시 클릭시 소환되도록
	//소환명령에서 충돌박스 점검
}

void UC_UserWidget::Button2Clicked()
{
}

void UC_UserWidget::Button3Clicked()
{
}

void UC_UserWidget::Button4Clicked()
{
}

void UC_UserWidget::Button1Pressed()
{
	//Pawn에게 Selected 1, false
	//Release일때 소환.
}

void UC_UserWidget::Button2Pressed()
{
}

void UC_UserWidget::Button3Pressed()
{
}

void UC_UserWidget::Button4Pressed()
{
}

void UC_UserWidget::Button1Released()
{
	//Pawn에서 소환 명령
	//Pawn은 충돌박스를 확인
}

void UC_UserWidget::Button2Released()
{
}

void UC_UserWidget::Button3Released()
{
}

void UC_UserWidget::Button4Released()
{
}


