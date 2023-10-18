#include "Character/C_CSCharacter.h"
#include "Components/C_StatusComponent.h"

#include "Weapon/C_Weapon.h"
#include "Weapon/C_WeaponInterface.h"

#include "Environment/C_Base.h"

#include "AI/C_CSAIController.h"

#include "Skill/C_Skill.h"
#include "Skill/C_PassiveSkill.h"
#include "Skill/C_ActiveSkill.h"
#include "Skill/C_SkillInterface.h"

#include "Components/C_StatusComponent.h"

#include "Enum/ECharacterState.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/GameplayStatics.h"

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

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::Attack, 1 / Status->GetAttackRate(), true, 0);

	GetMesh()->GetAnimInstance()->OnMontageStarted.AddDynamic(this, &ThisClass::CharacterMontageStarted);
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::CharacterMontageEnded);
	GetMesh()->GetAnimInstance()->OnMontageBlendingOut.AddDynamic(this, &ThisClass::CharacterMontageBlendingOut);
	
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &ThisClass::OnNotifyStart);
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyEnd.AddDynamic(this, &ThisClass::OnNotifyEnd);
}

void AC_CSCharacter::OnConstruction(FTransform const& Transform)
{
	Super::OnConstruction(Transform);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88.5f));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0).Quaternion());
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

	//PrintState();
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
		{ECharacterState::Dead, TEXT("Dead")},
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
	if (PassiveSkillClasses.Num() != 0)
	{
		for (auto& PassiveSkillClass : PassiveSkillClasses)
		{
			auto* const SpawnedPasiveSkill = GetWorld()->SpawnActor<AC_Skill>(PassiveSkillClass, SpawnParameters);
			SpawnedPasiveSkill->AttachToComponent(GetMesh(), Rules);
			PasiveSkills.AddUnique(SpawnedPasiveSkill);
		}
	}
	
	//special
	if (SpecialSkillClass != nullptr)
	{
		auto* const SpawnedSPSkill = GetWorld()->SpawnActor<AC_Skill>(SpecialSkillClass, SpawnParameters);
		SpawnedSPSkill->AttachToComponent(GetMesh(), Rules);
		SpecialSkill = SpawnedSPSkill;
	}
	//ultimate
	if (UltimateSkillClass != nullptr)
	{
		auto* const SpawnedUltSkill = GetWorld()->SpawnActor<AC_Skill>(UltimateSkillClass, SpawnParameters);
		SpawnedUltSkill->AttachToComponent(GetMesh(), Rules);
		UltimateSkill = SpawnedUltSkill;
	}
}

void AC_CSCharacter::MoveForward()
{
	//walk Forward
	FVector const Direction = FRotator(0, GetControlRotation().Yaw, 0).Quaternion().GetForwardVector();
	AddMovementInput(Direction);
}

void AC_CSCharacter::Destroyed()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), FoundActors);


	//Todo

	//상대 함선에게 죽음을 알림 : 미완성
	//TArray<AC_Base*> AllBase;
	//for (AActor* actor : FoundActors)
	//{
	//	if (actor == this)
	//		continue;
	//	AC_Base* Base = Cast<AC_Base>(actor);
	//	if (Base)
	//	{
	//		AllBase.Add(Base);
	//	}
	//}

	//for (AC_Base* Base : AllBase)
	//{
	//	if (Base->GetTeamID() == TeamID)
	//		continue;
	//	if (Base->IsValidLowLevel())
	//	{
	//		Base->RemoveTarget(this);
	//	}
	//}



	//전장에 있는 캐릭터들에게 죽음을 알림
	TArray<AC_CSCharacter*> AllCharacters;
	for (AActor* actor : FoundActors)
	{
		if (actor == this)
			continue;
		AC_CSCharacter* Character = Cast<AC_CSCharacter>(actor);
		if (Character)
		{
			AllCharacters.Add(Character);
		}
	}

	for (AC_CSCharacter* character : AllCharacters)
	{
		if (character->GetTeamID() == TeamID)
			continue;
		if (character->IsValidLowLevel())
		{
			character->RemoveTarget(this);
		}
	}
}

void AC_CSCharacter::RemoveTarget(AActor* Inactor)
{
	if (Targets.Contains(Inactor))
	{
		Targets.Remove(Inactor);
		if (Target == Inactor)
			Target = nullptr;

		Cast<AC_CSAIController>(GetController())->RemoveTarget(Inactor);
	}
}

