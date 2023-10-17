// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_AssultRifle.h"

void AC_AssultRifle::ActivateAttack()
{
	
	//GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, TEXT("AC_AssultRifle Attack!"));
	if (CurFireCount == FirePerAttack+1)
	{
		CurFireCount = 0;
		DeactivateAttack();
		return;
	}
	if (Timer == FTimerHandle())
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::ActivateAttack, FireInterval, true, 0);

	Super::ActivateAttack();
	CurFireCount++;
}

void AC_AssultRifle::DeactivateAttack()
{
	if (Timer != FTimerHandle())
	{
		GetWorld()->GetTimerManager().ClearTimer(Timer);
	}
}
