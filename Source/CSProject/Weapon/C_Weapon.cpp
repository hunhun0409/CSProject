#include "Weapon/C_Weapon.h"
#include "Character/C_CSCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"
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

void AC_Weapon::PlayAttackMontage()
{
	auto* const WeaponOwner = Cast<AC_CSCharacter>(GetOwner());
	if (WeaponOwner)
	{
		if (AttackMontage)
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::Red, TEXT("PlayAttackMontage"));
			WeaponOwner->PlayAnimMontage(AttackMontage, 1.0f);
		}
	}
}

USkeletalMeshComponent* AC_Weapon::GetMesh()
{
	return Mesh;
}

void AC_Weapon::BeginPlay()
{
	Super::BeginPlay();

	//FTimerHandle Timer;

	//GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::PlayAttackMontage, 1.0f, true, 0);
	
}

void AC_Weapon::ActivateAttack()
{
	auto* const WeaponOwner = Cast<AC_CSCharacter>(GetOwner());
	

	if (WeaponOwner)
	{
		
		if (AttackMontage)
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::Red, TEXT("AC_Weapon Attack!"));
			WeaponOwner->PlayAnimMontage(AttackMontage);
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

