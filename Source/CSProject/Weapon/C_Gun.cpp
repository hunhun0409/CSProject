#include "Weapon/C_Gun.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "Character/C_CSCharacter.h"
#include "Components/C_StatusComponent.h"

#include "Kismet/GameplayStatics.h"

#define CreateDefaultSubobjectAuto(Component)\
Component = CreateDefaultSubobject<std::remove_reference<decltype(*Component)>::type>(#Component)

AC_Gun::AC_Gun()
{
	CreateDefaultSubobjectAuto(MuzzleFlash);
	MuzzleFlash->SetAutoActivate(false);

	CreateDefaultSubobjectAuto(GunshotSound);
	GunshotSound->SetAutoActivate(false);
}

void AC_Gun::OnConstruction(FTransform const& Transform)
{
	FAttachmentTransformRules const Rules(EAttachmentRule::SnapToTarget, true);

	MuzzleFlash->AttachToComponent(Mesh, Rules, MuzzleSocket);
	GunshotSound->AttachToComponent(Mesh, Rules, MuzzleSocket);

}

void AC_Gun::BeginPlay()
{
	Super::BeginPlay();

	
}

void AC_Gun::ActivateAttack()
{
	if (!IsValid(GetOwner()))
		return;
	Super::ActivateAttack();

	AC_CSCharacter* const WeaponOwner = Cast<AC_CSCharacter>(GetOwner());
	if (WeaponOwner)
	{
		float attackRate = WeaponOwner->GetStatus()->GetAttackRate();
		float damage = WeaponOwner->GetStatus()->GetAttack();
		UGameplayStatics::ApplyDamage(WeaponOwner->Target, damage, GetInstigatorController(), this, UDamageType::StaticClass());

		WeaponOwner->bCanActivateAttack = false;
		if (AttackTimer == FTimerHandle())
		{
			GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &ThisClass::NotifyCanAttack, 1 / attackRate, false);
		}
	}
	ActivateEffect();
}

void AC_Gun::DeactivateAttack()
{
}

void AC_Gun::ActivateTrail()
{
}

void AC_Gun::DeactivateTrail()
{
}

void AC_Gun::ActivateEffect()
{
	MuzzleFlash->Activate(true);
	GunshotSound->Play();
}

void AC_Gun::DeactivateEffect()
{
}
