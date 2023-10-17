#include "Character/C_CSCharacter.h"
#include "Components/C_StatusComponent.h"

#include "Weapon/C_Weapon.h"
#include "Weapon/C_WeaponInterface.h"

#include "Skill/C_Skill.h"
#include "Skill/C_PassiveSkill.h"
#include "Skill/C_ActiveSkill.h"
#include "Skill/C_SkillInterface.h"

#include "Components/C_StatusComponent.h"

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

	InitState();
	InitWeapon();
	InitSkill();

	//FTimerHandle Timer;
	//GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::Attack, 1 / Status->GetAttackRate(), true, 0);

	GetMesh()->GetAnimInstance()->OnMontageStarted.AddDynamic(this, &ThisClass::CharacterMontageStarted);
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::CharacterMontageEnded);
	GetMesh()->GetAnimInstance()->OnMontageBlendingOut.AddDynamic(this, &ThisClass::CharacterMontageBlendingOut);
	
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &ThisClass::OnNotifyStart);
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyEnd.AddDynamic(this, &ThisClass::OnNotifyEnd);
}

void AC_CSCharacter::PrintState()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, *StateToName.Find(*CharacterState));
}

void AC_CSCharacter::CharacterMontageStarted(UAnimMontage* const Montage)
{
}

void AC_CSCharacter::CharacterMontageEnded(UAnimMontage* const Montage, bool bInterrupted)
{
	if (bInterrupted)
	{

	}
	else
	{
		*CharacterState = ECharacterState::Idle;
	}
}

void AC_CSCharacter::CharacterMontageBlendingOut(UAnimMontage* const montage, bool bInterrupted)
{
}

void AC_CSCharacter::OnNotifyStart(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
}

void AC_CSCharacter::OnNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
}

void AC_CSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PrintState();
	//MoveForward();
}

void AC_CSCharacter::Attack()
{
	*CharacterState = ECharacterState::Attacking;

	Weapon->ActivateAttack();
}

void AC_CSCharacter::SPSkill()
{
	*CharacterState = ECharacterState::SP_Skilling;

	SpecialSkill->BeginAction();
}

void AC_CSCharacter::ULTSkill()
{
	*CharacterState = ECharacterState::ULT_Skilling;

	UltimateSkill->BeginAction();
}

void AC_CSCharacter::InitState()
{
	GetCharacterMovement()->MaxWalkSpeed = Status->GetMovementSpeed();

	CharacterState = decltype(CharacterState)(new ECharacterState);
	*CharacterState = ECharacterState::Idle;
	StateToName = {
		{ECharacterState::Idle, TEXT("Idle")},
		{ECharacterState::Attacking, TEXT("Attacking")},
		{ECharacterState::SP_Skilling, TEXT("SP_Skilling")},
		{ECharacterState::ULT_Skilling, TEXT("ULT_Skilling")},
		{ECharacterState::Died, TEXT("Died")},
	};
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
void AC_CSCharacter::InitSkill()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = SpawnParameters.Instigator = this;
	FAttachmentTransformRules const Rules(EAttachmentRule::SnapToTarget, true);

	//pasive
	for (auto& PassiveSkillClass : PassiveSkillClasses)
	{
		auto* const SpawnedPasiveSkill = GetWorld()->SpawnActor<AC_PassiveSkill>(PassiveSkillClass, SpawnParameters);
		SpawnedPasiveSkill->AttachToComponent(GetMesh(), Rules);
		PasiveSkills.AddUnique(SpawnedPasiveSkill);
	}

	//special
	auto* const SpawnedSPSkill = GetWorld()->SpawnActor<AC_ActiveSkill>(SpecialSkillClass, SpawnParameters);
	SpawnedSPSkill->AttachToComponent(GetMesh(), Rules);
	SpecialSkill = SpawnedSPSkill;

	//ultimate
	auto* const SpawnedUltSkill = GetWorld()->SpawnActor<AC_ActiveSkill>(UltimateSkillClass, SpawnParameters);
	SpawnedUltSkill->AttachToComponent(GetMesh(), Rules);
	UltimateSkill = SpawnedUltSkill;

}

void AC_CSCharacter::MoveForward()
{
	//walk Forward
	FVector const Direction = FRotator(0, GetControlRotation().Yaw, 0).Quaternion().GetForwardVector();
	AddMovementInput(Direction);
}

