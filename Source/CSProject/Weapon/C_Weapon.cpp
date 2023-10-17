#include "Weapon/C_Weapon.h"
#include "Character/C_CSCharacter.h"

#include "Particles/ParticleSystemComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/C_StatusComponent.h"


#include "Animation/AnimMontage.h"


#define CreateDefaultSubobjectAuto(Component)\
Component = CreateDefaultSubobject<std::remove_reference<decltype(*Component)>::type>(#Component)

AC_Weapon::AC_Weapon()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	CreateDefaultSubobjectAuto(Trail);
	Trail->SetupAttachment(Mesh);

	CreateDefaultSubobjectAuto(Effect);
	Effect->SetupAttachment(Mesh);

	CreateDefaultSubobjectAuto(AttackMontage);


}

USkeletalMeshComponent* AC_Weapon::GetMesh()
{
	return Mesh;
}

void AC_Weapon::BeginPlay()
{
	Super::BeginPlay();
}

void AC_Weapon::ActivateAttack()
{
	AC_CSCharacter* const WeaponOwner = Cast<AC_CSCharacter>(GetOwner());
	//auto* const WeaponOwner = Cast<AC_CSCharacter>(GetOwner());

	if (WeaponOwner)
	{
		if (AttackMontage)
		{
			float attackRate = Cast<AC_CSCharacter>(GetOwner())->GetStatus()->GetAttackRate();

			WeaponOwner->PlayAnimMontage(AttackMontage, attackRate);
		}
	}
}

void AC_Weapon::DeactivateAttack()
{
}

void AC_Weapon::ActivateTrail()
{
}

void AC_Weapon::DeactivateTrail()
{
}

void AC_Weapon::ActivateEffect()
{
}

void AC_Weapon::DeactivateEffect()
{
}

