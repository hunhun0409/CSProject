#include "Character/C_CSCharacter.h"
#include "Components/C_StatusComponent.h"
#include "Weapon/C_Weapon.h"
#include "Weapon/C_WeaponInterface.h"
//#include "Skill/C_Skill.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Components/StaticMeshComponent.h"

#define CreateDefaultSubobjectAuto(Component)\
Component = CreateDefaultSubobject<std::remove_reference<decltype(*Component)>::type>(#Component)

AC_CSCharacter::AC_CSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobjectAuto(Status);
	

}

void AC_CSCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = Status->GetMovementSpeed();

	
	
}

void AC_CSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_CSCharacter::InitWeapon()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = SpawnParameters.Instigator = this;
	
	for (auto& WeaponClass : WeaponClasses)
	{
		auto* const SpawnedWeapon = GetWorld()->SpawnActor<AC_Weapon>(WeaponClass, SpawnParameters);
		SpawnedWeapon->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		FAttachmentTransformRules const Rules(EAttachmentRule::SnapToTarget, true);

		Weapons.Add(SpawnedWeapon);

		SpawnedWeapon->AttachToComponent(GetMesh(), Rules, SpawnedWeapon->SocketOnUnequipped);
	}

	

}

