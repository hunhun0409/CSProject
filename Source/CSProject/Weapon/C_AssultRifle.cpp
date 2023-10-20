// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_AssultRifle.h"
#include "Character/C_CSCharacter.h"
#include "Components/C_StatusComponent.h"

#include "Kismet/GameplayStatics.h"

void AC_AssultRifle::ActivateAttack()
{
	if (Timer == FTimerHandle())
	{
		float attackRate = Cast<AC_CSCharacter>(GetOwner())->GetStatus()->GetAttackRate();
		float FinalInterval = FireInterval / attackRate;

		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::ActivateAttack, FinalInterval, true, 0);
		return;
	}

	AC_CSCharacter* const WeaponOwner = Cast<AC_CSCharacter>(GetOwner());

	if (WeaponOwner)
	{
		//GEngine->AddOnScreenDebugMessage(0, 5, FColor::Green, TEXT("Cause Damage!"), true);

		UGameplayStatics::ApplyDamage(WeaponOwner->Target, 1000.0f, GetInstigatorController(), this, UDamageType::StaticClass());
	}

	//GEngine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::SanitizeFloat(CurFireCount), true);
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
