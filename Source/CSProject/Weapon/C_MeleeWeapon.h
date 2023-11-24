// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/C_Weapon.h"
#include "C_MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class CSPROJECT_API AC_MeleeWeapon : public AC_Weapon
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
		class UAudioComponent* SwingSound;

public:
	AC_MeleeWeapon();

	void OnConstruction(FTransform const& Transform) override;
protected:
	virtual void BeginPlay() override;

	void BeginAction() override;
	void EndAction() override;

	void ActivateTrail() override;
	void DeactivateTrail() override;

	void ActivateEffect() override;
	void DeactivateEffect() override;

};