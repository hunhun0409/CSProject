#include "Components/C_StatusComponent.h"

void UC_StatusComponent::SetMaxHealth(float Value)
{
	float difference = Value - MaxHealth;
	if (difference >= 0)
	{
		MaxHealth = Value;
		AddHealth(difference);
	}
	else
	{
		MaxHealth = Value;
		if (CurHealth > Value)
		{
			CurHealth = Value;
		}
	}
}

UC_StatusComponent::UC_StatusComponent()
{
	
}


void UC_StatusComponent::ApplyStatus(FStatusData InData)
{
	Name = InData.Name;
	Cost = InData.Cost;
	CharacterRank = InData.CharacterRank;
	CharacterType = InData.CharacterType;
	ClassType = InData.ClassType;
	MoveType = InData.MoveType;
	AttackType = InData.AttackType;
	MaxHealth = InData.Health;
	CurHealth = MaxHealth;
	Attack = InData.Attack;
	Defense = InData.Defense;
	Crit = InData.Critk;
	CritDamage = InData.CritDamage;
	Hit = InData.Hit;
	Eva = InData.Eva;
	AttackRate = InData.AttackRate;
	MaxSightRange = InData.MaxSightRange;
	MaxAttackRange = InData.MaxAttackRange;
	MovementSpeed = InData.MovementSpeed;
}


void UC_StatusComponent::AddHealth(float InAmount)
{
	CurHealth = CurHealth + InAmount;

	CurHealth = FMath::Clamp(CurHealth, 0.0f, MaxHealth);
}




