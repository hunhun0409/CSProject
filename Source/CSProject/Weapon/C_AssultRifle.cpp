// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_AssultRifle.h"
#include "Character/C_CSCharacter.h"
#include "Components/C_StatusComponent.h"


void AC_AssultRifle::BeginAction()
{
	if (!IsValid(GetOwner()))
		return;

	if (Timer == FTimerHandle())
	{
		AC_CSCharacter* WeaponOwner = Cast<AC_CSCharacter>(GetOwner());

		if (WeaponOwner)
		{
			float attackRate = Cast<AC_CSCharacter>(GetOwner())->GetStatus()->GetAttackRate();
			float FinalInterval = FireInterval / attackRate;

			GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::BeginAction, FinalInterval, true, 0);
			return;
		}
	}
	Super::BeginAction();

	if (++CurFireCount == FirePerAttack)
	{
		EndAction();
		return;
	}
}

void AC_AssultRifle::EndAction()
{
	Super::EndAction();
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "Riffle EndAction!");
	if (Timer != FTimerHandle())
	{
		CurFireCount = 0;
		GetWorld()->GetTimerManager().ClearTimer(Timer);
	}
}
