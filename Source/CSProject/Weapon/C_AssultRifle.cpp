// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_AssultRifle.h"

void AC_AssultRifle::ActivateAttack()
{
	if (Timer == FTimerHandle())
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::ActivateAttack, FireInterval, true, 0);

	Super::ActivateAttack();

	CurFireCount++;
	if (CurFireCount == FirePerAttack)
	{
		CurFireCount = 0;
		DeactivateAttack();
	}
}

void AC_AssultRifle::DeactivateAttack()
{
	if (Timer != FTimerHandle())
	{
		GetWorld()->GetTimerManager().ClearTimer(Timer);
	}
}
