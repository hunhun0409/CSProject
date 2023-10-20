// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_AssultRifle.h"
#include "Character/C_CSCharacter.h"
#include "Components/C_StatusComponent.h"


void AC_AssultRifle::ActivateAttack()
{
	if (!IsValid(GetOwner()))
		return;

	if (Timer == FTimerHandle())
	{
		float attackRate = Cast<AC_CSCharacter>(GetOwner())->GetStatus()->GetAttackRate();
		float FinalInterval = FireInterval / attackRate;

		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::ActivateAttack, FinalInterval, true, 0);
		return;
	}

	Super::ActivateAttack();
	if (++CurFireCount == FirePerAttack)
	{
		DeactivateAttack();
		return;
	}
}

void AC_AssultRifle::DeactivateAttack()
{
	Super::DeactivateAttack();
	if (Timer != FTimerHandle())
	{
		CurFireCount = 0;
		GetWorld()->GetTimerManager().ClearTimer(Timer);
	}
}
