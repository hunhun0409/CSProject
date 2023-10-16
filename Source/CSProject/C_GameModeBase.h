// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	void RestoreCost(float DeltaTime);

public:

protected:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AC_Field> Field;

private:
	float CostRegenRatio = 1.0f;
	float MaxCost = 10.0f;
	float LeftCost = 0.0f;
	float RightCost = 0.0f;

};
