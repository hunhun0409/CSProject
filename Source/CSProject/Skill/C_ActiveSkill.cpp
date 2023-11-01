// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/C_ActiveSkill.h"
#include "Character/C_CSCharacter.h"

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
	if (Timer == FTimerHandle())
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::AddCooldown, AddInterval, true, AddInterval);
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

			Cast<AC_CSCharacter>(GetOwner())->GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &ThisClass::OnNotifyStart);
			Cast<AC_CSCharacter>(GetOwner())->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::OnSkillMontageEnded);

			float attackRate = Cast<AC_CSCharacter>(GetOwner())->GetStatus()->GetAttackRate();

			SkillOwner->PlayAnimMontage(SkillMontage, attackRate);
		}
	}
}

void AC_ActiveSkill::EndAction()
{
	//Skill 애니메이션 끝날때 시행할 작업
	Cast<AC_CSCharacter>(GetOwner())->GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &ThisClass::OnSkillMontageEnded);

}

void AC_ActiveSkill::Activate()
{
	//스킬이 발사되는 순간
	Cast<AC_CSCharacter>(GetOwner())->GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.RemoveDynamic(this, &ThisClass::OnNotifyStart);

	
	//미완
	//효과
}

void AC_ActiveSkill::Deactivate()
{
	
}

void AC_ActiveSkill::RestartCooldown()
{
	CurCooldown = 0;
	//미완
	//전장에 스폰여부를 확인하고 스폰돼있을때만 쿨이 돌게 해야함
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
	return MaxCooldown / CurCooldown;
}
