// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs.h"
#include "C_UserWidget.generated.h"
/**
 * 
 */
UCLASS()
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


	FVector2D MousePos;
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* MouseCurserNClick;
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* MouseCurserClick;
	UPROPERTY(EditDefaultsOnly)
		FName MouseImage;
	class UImage* MouseWidget;
};
