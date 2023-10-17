// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Structs.h"
#include "C_GameModeBase.generated.h"


/**
 * 
 */


class AC_Field;
UCLASS(Abstract)
class CSPROJECT_API AC_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AC_GameModeBase();

	const AC_Field* GetField() { return Map; }

	const UIData& GetUIData() { return Datas; }

	TDelegate<void()> UIDataUpdated;

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void CheckHP();
private:
	void RestoreCost(float DeltaTime);

public:

protected:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AC_Field> Field;

	UPROPERTY()
		class AC_Field* Map;

private:
	float CostRegenRatio = 1.0f;
	float MaxCost = 10.0f;
	BasicData RightBase;
	BasicData LeftBase;
	UIData Datas;

};
