#include "Skill/C_PassiveSkill.h"
#include "Character/C_CSCharacter.h"
#include "Components/C_StatusComponent.h"

void AC_PassiveSkill::BeginPlay()
{
	Super::BeginPlay();
	ApplyEffectToPawn(Cast<APawn>(GetOwner()));
}

void AC_PassiveSkill::ApplyEffectToPawn(APawn* InPawn)
{
	//GEngine->AddOnScreenDebugMessage(1, 5, FColor::Green, TEXT("ApplyEffectToPawn"));
	AC_CSCharacter* InOwner = Cast<AC_CSCharacter>(InPawn);
	UC_StatusComponent* Status = InOwner->GetStatus();

	if (bChangeHP)
	{
		Status->SetMaxHealth(Status->GetMaxHealth() * ((100.0f + HP_IncreaseRate) / 100.0f));
	}
	if (bChangeAttack)
	{
		Status->SetAttack(Status->GetAttack() * ((100.0f + Attack_IncreaseRate) / 100.0f));
	}
	if (bChangeDefense)
	{
		Status->SetDefense(Status->GetDefense() * ((100.0f + Defense_IncreaseRate) / 100.0f));
	}
	if (bChangeCrit)
	{
		Status->SetCrit(Status->GetCrit() * ((100.0f + Crit_IncreaseRate) / 100.0f));
	}
	if (bChangeCrit_Damage)
	{
		Status->SetCritDamage(Status->GetCritDamage() * ((100.0f + Crit_Damage_IncreaseRate) / 100.0f));
	}
	if (bChangeHit)
	{
		Status->SetHit(Status->GetHit() * ((100.0f + Hit_IncreaseRate) / 100.0f));
	}
	if (bChangeAttackRate)
	{
		Status->SetAttackRate(Status->GetAttackRate() * ((100.0f + AttackRate_IncreaseRate) / 100.0f));
	}
	if (bChangeMaxSightRange)
	{
		Status->SetMaxSightRange(Status->GetMaxSightRange() * ((100.0f + MaxSightRange_IncreaseRate) / 100.0f));
	}
	if (bChangeMaxAttackRange)
	{
		Status->SetMaxAttackRange(Status->GetMaxAttackRange() * ((100.0f + MaxAttackRange_IncreaseRate) / 100.0f));
	}
	if (bChangeMovementSpeed)
	{
		Status->SetMovementSpeed(Status->GetMovementSpeed() * ((100.0f + MovementSpeed_IncreaseRate) / 100.0f));
	}
}
