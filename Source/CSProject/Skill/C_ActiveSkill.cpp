// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/C_ActiveSkill.h"
#include "Character/C_CSCharacter.h"
#include "Enum/ECharacterState.h"

#include "Particles/ParticleSystemComponent.h"

#include "Components/C_StatusComponent.h"

#include "Animation/AnimMontage.h"

#define CreateDefaultSubobjectAuto(Component)\
Component = CreateDefaultSubobject<std::remove_reference<decltype(*Component)>::type>(#Component)

AC_ActiveSkill::AC_ActiveSkill()
{
	CreateDefaultSubobjectAuto(SkillMontage);

	
}
void AC_ActiveSkill::BeginPlay()
{
	Super::BeginPlay();

	
}

void AC_ActiveSkill::ApplyEffectToPawn(APawn* InPawn)
{
}

void AC_ActiveSkill::BeginAction()
{
	//Skill 애니메이션 재생
	AC_CSCharacter* const SkillOwner = Cast<AC_CSCharacter>(GetOwner());

	if (SkillOwner)
	{
		if (SkillMontage)
		{

			RestartCooldown();

			SkillOwner->GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &ThisClass::OnNotifyStart);
			SkillOwner->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::OnSkillMontageEnded);

			float attackRate = Cast<AC_CSCharacter>(GetOwner())->GetStatus()->GetAttackRate();

			SkillOwner->PlayAnimMontage(SkillMontage, attackRate);
		}
	}
}

void AC_ActiveSkill::EndAction()
{
	//Skill 애니메이션 끝날때 시행할 작업
	if (!IsValid(GetOwner()))
		return;
	AC_CSCharacter* SkillOwner = Cast<AC_CSCharacter>(GetOwner());
	*(SkillOwner->CharacterState) = ECharacterState::Idle;
	Cast<AC_CSCharacter>(GetOwner())->GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &ThisClass::OnSkillMontageEnded);

}

void AC_ActiveSkill::Activate()
{
	//스킬이 발사되는 순간
	if (!IsValid(GetOwner()))
		return;
	AC_CSCharacter* SkillOwner = Cast<AC_CSCharacter>(GetOwner());
	//*(SkillOwner->CharacterState) = ECharacterState::Idle;

	SkillOwner->GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.RemoveDynamic(this, &ThisClass::OnNotifyStart);
}

void AC_ActiveSkill::Deactivate()
{
	
}

void AC_ActiveSkill::StartCooldown()
{
	if (Timer == FTimerHandle())
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::AddCooldown, AddInterval, true, AddInterval);
}

void AC_ActiveSkill::RestartCooldown()
{
	CurCooldown = 0;
	if (SkillType == ESkillType::Special)
	{
		if (IsValid(GetInstigator()))
			Cast<AC_CSCharacter>(GetInstigator())->bCanActivateSP = false;
	}
		
	if (SkillType == ESkillType::Ultimate)
	{
		if (IsValid(GetInstigator()))
			Cast<AC_CSCharacter>(GetInstigator())->bCanActivateULT = false;
	}
	if (Timer == FTimerHandle())
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::AddCooldown, AddInterval, true, AddInterval);
}

void AC_ActiveSkill::OnNotifyStart(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Activate();
}

void AC_ActiveSkill::OnSkillMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	EndAction();
}


void AC_ActiveSkill::AddCooldown()
{
	CurCooldown += AddInterval;
	CurCooldown = FMath::Clamp(CurCooldown, 0.0f, MaxCooldown);

	if (CurCooldown == MaxCooldown)
	{
		if (SkillType == ESkillType::Special)
		{
			if(IsValid(GetInstigator()))
				Cast<AC_CSCharacter>(GetInstigator())->bCanActivateSP = true;
		}

			
		if (SkillType == ESkillType::Ultimate)
		{
			if (IsValid(GetInstigator()))
				Cast<AC_CSCharacter>(GetInstigator())->bCanActivateULT = true;
		}
			

		if (Timer != FTimerHandle())
			GetWorld()->GetTimerManager().ClearTimer(Timer);
	}
}

bool AC_ActiveSkill::CanActivate()
{
	return CurCooldown == MaxCooldown;
}

float AC_ActiveSkill::GetSkillCoolDown()
{
	return CurCooldown / MaxCooldown;
}
