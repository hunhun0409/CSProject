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

void UC_StatusComponent::AddHealth(float InAmount)
{
	CurHealth += InAmount;

	CurHealth = FMath::Clamp(CurHealth, 0.0f, MaxHealth);
}

void UC_StatusComponent::BeginPlay()
{
	Super::BeginPlay();

	CurHealth = MaxHealth;

}
