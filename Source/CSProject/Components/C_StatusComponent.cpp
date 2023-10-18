#include "Components/C_StatusComponent.h"

void UC_StatusComponent::SetMaxHealth(float Value)
{
	float difference = Value - MaxHealth;
	MaxHealth = Value;
	AddHealth(difference);
}

UC_StatusComponent::UC_StatusComponent()
{
	
}

void UC_StatusComponent::BeginPlay()
{
	Super::BeginPlay();

	CurHealth = MaxHealth;

}

void UC_StatusComponent::ApplyStatus()
{
	/*MaxHealth = LV1_Health + (Health_IncreaseAmount * Level);
	Attack = LV1_Attack + (Attack_IncreaseAmount * Level);
	Defense = LV1_Defenseh + (Defense_IncreaseAmount * Level);
	Crit = LV1_Crit + (Crit_IncreaseAmount * Level);
	Hit = LV1_Hit + (Hit_IncreaseAmount * Level);*/
}


void UC_StatusComponent::AddHealth(float InAmount)
{
	CurHealth += InAmount;

	CurHealth = FMath::Clamp(CurHealth, 0.0f, MaxHealth);
}




