// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/C_SwordManSP.h"
#include "Character/C_CSCharacter.h"
#include "Components/C_StatusComponent.h"

void AC_SwordManSP::BeginPlay()
{
	Super::BeginPlay();
}

void AC_SwordManSP::ApplyEffectToPawn(APawn* InPawn)
{
	Super::ApplyEffectToPawn(InPawn);
	AC_CSCharacter* InOwner = Cast<AC_CSCharacter>(InPawn);
	UC_StatusComponent* Status = InOwner->GetStatus();

	Status->SetAttackRate(0.5f);
}

void AC_SwordManSP::BeginAction()
{
	Super::BeginAction();
}

void AC_SwordManSP::EndAction()
{
	Super::EndAction();
}

void AC_SwordManSP::Activate()
{
	Super::Activate();

	if (GetOwner())
	{

	}
}

void AC_SwordManSP::Deactivate()
{
	Super::Deactivate();
}

void AC_SwordManSP::StartCooldown()
{
	Super::StartCooldown();
}

void AC_SwordManSP::RestartCooldown()
{
	Super::RestartCooldown();
}
