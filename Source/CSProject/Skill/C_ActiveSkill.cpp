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

}

void AC_ActiveSkill::ApplyEffectToPawn(APawn* InPawn)
{
}

void AC_ActiveSkill::BeginAction()
{
	//Skill �ִϸ��̼� ���
	AC_CSCharacter* const SkillOwner = Cast<AC_CSCharacter>(GetOwner());

	if (SkillOwner)
	{
		if (SkillMontage)
		{
			Cast<AC_CSCharacter>(GetOwner())->GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &ThisClass::OnNotifyStart);
			Cast<AC_CSCharacter>(GetOwner())->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::OnSkillMontageEnded);

			float attackRate = Cast<AC_CSCharacter>(GetOwner())->GetStatus()->GetAttackRate();

			SkillOwner->PlayAnimMontage(SkillMontage, attackRate);
		}
	}
}

void AC_ActiveSkill::EndAction()
{
	//Skill �ִϸ��̼� ������ ������ �۾�
	Cast<AC_CSCharacter>(GetOwner())->GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &ThisClass::OnSkillMontageEnded);

}

void AC_ActiveSkill::Activate()
{
	//��ų�� �߻�Ǵ� ����
	Cast<AC_CSCharacter>(GetOwner())->GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.RemoveDynamic(this, &ThisClass::OnNotifyStart);

	RestartCooldown();
	//�̿�
	//ȿ��
}

void AC_ActiveSkill::Deactivate()
{
	
}

void AC_ActiveSkill::RestartCooldown()
{
	CurCooldown = 0;
	//�̿�
	//���忡 �������θ� Ȯ���ϰ� �������������� ���� ���� �ؾ���
	FTimerHandle Timer;
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
