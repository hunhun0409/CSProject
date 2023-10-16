#include "Weapon/C_Weapon.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"


#define CreateDefaultSubobjectAuto(Component)\
Component = CreateDefaultSubobject<std::remove_reference<decltype(*Component)>::type>(#Component)

AC_Weapon::AC_Weapon()
{
	CreateDefaultSubobjectAuto(Mesh);
	SetRootComponent(Mesh);

	CreateDefaultSubobjectAuto(Trail);
	Trail->SetupAttachment(Mesh);

	CreateDefaultSubobjectAuto(Effect);
	Effect->SetupAttachment(Mesh);

}

UStaticMeshComponent* AC_Weapon::GetMesh()
{
	return nullptr;
}

void AC_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_Weapon::ActivateAttack()
{
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

