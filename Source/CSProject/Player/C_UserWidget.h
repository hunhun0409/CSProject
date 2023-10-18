// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int CurCost;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float PlayerBaseHP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float EnemyBaseHP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float CostRegenRatio;

	UPROPERTY(EditDefaultsOnly)
		class UMaterialInstance* CostMaterialInstance;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		class UMaterialInstanceDynamic* CostMaterialInstanceDynamic;
	UPROPERTY(EditDefaultsOnly)
		FName CostPercentParamName;
};
