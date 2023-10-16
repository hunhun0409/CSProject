// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
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

public:

protected:
	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* Field;

	UPROPERTY(EditDefaultsOnly)
		class AC_BaseSpawner* LeftBaseSpawner;
	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* LeftSpawnCollider;

	UPROPERTY(EditDefaultsOnly)
		class AC_BaseSpawner* RightBaseSpawner;
	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* RightSpawnCollider;


private:
	float MaxCost = 10.0f;
	float LeftCost = 0.0f;
	float RightCost = 0.0f;

};
