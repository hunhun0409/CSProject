#include "Skill/C_ActiveSkillTest.h"
#include "Character/C_CSCharacter.h"
#include "Components/C_StatusComponent.h"


void AC_ActiveSkillTest::BeginPlay()
{
	Super::BeginPlay();
}

void AC_ActiveSkillTest::ApplyEffectToPawn(APawn* InPawn)
{
	Super::ApplyEffectToPawn(InPawn);
	AC_CSCharacter* InOwner = Cast<AC_CSCharacter>(InPawn);
	UC_StatusComponent* Status = InOwner->GetStatus();
	
	Status->AddHealth(50000.0f);
}

void AC_ActiveSkillTest::BeginAction()
{
	Super::BeginAction();
}

void AC_ActiveSkillTest::EndAction()
{
	Super::EndAction();
}

void AC_ActiveSkillTest::Activate()
{
	Super::Activate();
	ApplyEffectToPawn(GetInstigator());
}

void AC_ActiveSkillTest::Deactivate()
{
	Super::Deactivate();
}

void AC_ActiveSkillTest::RestartCooldown()
{
	Super::RestartCooldown();
}

//void AC_ActiveSkillTest::OnNotifyStart(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
//{
//}
//
//void AC_ActiveSkillTest::OnSkillMontageEnded(UAnimMontage* Montage, bool bInterrupted)
//{
//}
