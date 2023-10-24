// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs.h"
#include "C_UserWidget.generated.h"
/**
 * 
 */
UCLASS(Abstract)
class CSPROJECT_API UC_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeOnInitialized() override;
	void NativePreConstruct() override;
	void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateUIData(const FUIData& UIData);
	void UpdateMousePos(const FVector2D& InMousePos);
	void UpdateMouseLBPressing(const bool& IsPressing);
	void KeyBoardNumPress(const int& InNum);

	TDelegate<void(int)> SpawnOrdered;
	TDelegate<void(int)> SelectedPreview;

protected:
	UFUNCTION()
		void RBEvent(bool IsPressed);

private:
	bool IsMousePosInUImage(class UImage* Target);

protected:
	UPROPERTY(BlueprintReadOnly)
		int CurCost;
	UPROPERTY(BlueprintReadOnly)
		float PlayerBaseHP;
	UPROPERTY(BlueprintReadOnly)
		float EnemyBaseHP;
		float CostRegenRatio;

	UPROPERTY(EditDefaultsOnly)
		class UMaterialInstance* CostMaterialInstance;
	UPROPERTY()
		class UMaterialInstanceDynamic* CostMaterialInstanceDynamic;
	UPROPERTY(EditDefaultsOnly)
		FName CostPercentParamName;
	UPROPERTY(EditDefaultsOnly)
		FName CostImage;
	class UImage* CostWidget;

	class UImage* UnitButton1;
	UPROPERTY(EditDefaultsOnly)
		FName Button1;
	class UImage* UnitButton2;
	UPROPERTY(EditDefaultsOnly)
		FName Button2;
	class UImage* UnitButton3;
	UPROPERTY(EditDefaultsOnly)
		FName Button3;
	class UImage* UnitButton4;
	UPROPERTY(EditDefaultsOnly)
		FName Button4;
	FVector2D ClickedPos;
	int ButtonNum;
	bool UnitSelected = false;
	FLinearColor SpawnedTint = {0.2f, 0.2f, 0.2f, 1.0f};

	FVector2D MousePos;
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* MouseCurserNClick;
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* MouseCurserClick;
	UPROPERTY(EditDefaultsOnly)
		FName MouseImage;
	class UImage* MouseWidget;
};
