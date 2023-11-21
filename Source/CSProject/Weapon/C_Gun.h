// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/C_Weapon.h"
#include "C_Gun.generated.h"

/**
 * 
 */
UCLASS(ABSTRACT)
class CSPROJECT_API AC_Gun : public AC_Weapon
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
		FName MuzzleSocket;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* MuzzleFlash;

	UPROPERTY(EditDefaultsOnly)
		class UAudioComponent* GunshotSound;

public:
	AC_Gun();

	void OnConstruction(FTransform const& Transform) override;
protected:
	virtual void BeginPlay() override;

	void BeginAction() override;
	void EndAction() override;

	void ActivateTrail() override;
	void DeactivateTrail() override;

	void ActivateEffect() override;
	void DeactivateEffect() override;

protected:
	uint8 CurFireCount = 0;
};
