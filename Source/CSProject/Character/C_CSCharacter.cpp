#include "Character/C_CSCharacter.h"
#include "Components/C_StatusComponent.h"

#include "Weapon/C_Weapon.h"
#include "Weapon/C_WeaponInterface.h"

//#include "Skill/C_Skill.h"

#include "Enum/ECharacterState.h"

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

	CharacterState = decltype(CharacterState)(new ECharacterState);
	*CharacterState = ECharacterState::Idle;

	InitWeapon();

	//FTimerHandle Timer;

	//GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::Attack, 1.0f, true, 0);
}

void AC_CSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_CSCharacter::Attack()
{
	Weapon->ActivateAttack();
}

void AC_CSCharacter::SpecialSkill()
{
}

void AC_CSCharacter::UltimateSkill()
{
}

void AC_CSCharacter::InitWeapon()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = SpawnParameters.Instigator = this;
	
	auto* const SpawnedWeapon = GetWorld()->SpawnActor<AC_Weapon>(WeaponClass, SpawnParameters);
	SpawnedWeapon->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FAttachmentTransformRules const Rules(EAttachmentRule::SnapToTarget, true);

	SpawnedWeapon->AttachToComponent(GetMesh(), Rules, SpawnedWeapon->SocketOnEquipped);

	Weapon = SpawnedWeapon;

}

