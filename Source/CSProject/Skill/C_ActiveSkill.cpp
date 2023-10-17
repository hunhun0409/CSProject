// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/C_ActiveSkill.h"

void AC_ActiveSkill::ApplyEffectToPawn(APawn* InPawn)
{
}

void AC_ActiveSkill::BeginAction()
{
}

void AC_ActiveSkill::EndAction()
{
}

void AC_ActiveSkill::Activate()
{
	
}

void AC_ActiveSkill::Deactivate()
{
	RestartCooldown();		
}

void AC_ActiveSkill::RestartCooldown()
{
	CurCooldown = 0;
	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::AddCooldown, AddInterval, true, AddInterval);
}
