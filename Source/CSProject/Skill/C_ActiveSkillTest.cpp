#include "Skill/C_ActiveSkillTest.h"
#include "Character/C_CSCharacter.h"
#include "Components/C_StatusComponent.h"


void AC_ActiveSkillTest::BeginPlay()
{
}

void AC_ActiveSkillTest::ApplyEffectToPawn(APawn* InPawn)
{
	/*AC_CSCharacter* InOwner = Cast<AC_CSCharacter>(InPawn);
	UC_StatusComponent* Status = InOwner->GetStatus();
	
	Status->AddHealth(5000.0f);*/

}

void AC_ActiveSkillTest::BeginAction()
{
}

void AC_ActiveSkillTest::EndAction()
{
}

void AC_ActiveSkillTest::Activate()
{
	//ApplyEffectToPawn(GetInstigator());
}

void AC_ActiveSkillTest::Deactivate()
{
}

void AC_ActiveSkillTest::RestartCooldown()
{
}

//void AC_ActiveSkillTest::OnNotifyStart(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
//{
//}
//
//void AC_ActiveSkillTest::OnSkillMontageEnded(UAnimMontage* Montage, bool bInterrupted)
//{
//}
