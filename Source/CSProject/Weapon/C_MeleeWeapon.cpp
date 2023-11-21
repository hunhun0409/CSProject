#include "Weapon/C_MeleeWeapon.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "Character/C_CSCharacter.h"
#include "Components/C_StatusComponent.h"

#include "Kismet/GameplayStatics.h"

#define CreateDefaultSubobjectAuto(Component)\
Component = CreateDefaultSubobject<std::remove_reference<decltype(*Component)>::type>(#Component)

AC_MeleeWeapon::AC_MeleeWeapon()
{

	CreateDefaultSubobjectAuto(SwingSound);
	SwingSound->SetAutoActivate(false);
}

void AC_MeleeWeapon::OnConstruction(FTransform const& Transform)
{
	FAttachmentTransformRules const Rules(EAttachmentRule::SnapToTarget, true);
}

void AC_MeleeWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void AC_MeleeWeapon::BeginAction()
{
	if (!IsValid(GetOwner()))
		return;
	Super::BeginAction();
	ActivateEffect();

}

void AC_MeleeWeapon::EndAction()
{
	Super::EndAction();
}

void AC_MeleeWeapon::ActivateTrail()
{
}

void AC_MeleeWeapon::DeactivateTrail()
{
}

void AC_MeleeWeapon::ActivateEffect()
{
	Super::ActivateEffect();
	//HitParticle->Activate(true);
	SwingSound->Play();
}

void AC_MeleeWeapon::DeactivateEffect()
{
}
