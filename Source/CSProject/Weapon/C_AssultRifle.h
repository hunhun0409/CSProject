// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/C_Gun.h"
#include "C_AssultRifle.generated.h"

/**
 * 
 */
UCLASS()
class CSPROJECT_API AC_AssultRifle : public AC_Gun
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "AttackSpeed", meta = (AllowPrivateAccess = "true"))
		float FireInterval = 0.125f;
	UPROPERTY(EditDefaultsOnly, Category = "AttackSpeed", meta = (AllowPrivateAccess = "true"))
		uint8 FirePerAttack = 3;
	
private:
	void ActivateAttack() final override;
	void DeactivateAttack() final override;

private:
	FTimerHandle Timer;
	uint8 CurFireCount = 0;
};
