#include "AI/C_BTTaskSP.h"
#include "AI/C_CSAIController.h"
#include "Character/C_CSCHaracter.h"
#include "CHaracter/C_CharacterInterface.h"

UC_BTTaskSP::UC_BTTaskSP()
{
	NodeName = "SP";
	bNotifyTick = true;
}

EBTNodeResult::Type UC_BTTaskSP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AC_CSAIController* Controller = Cast<AC_CSAIController>(OwnerComp.GetOwner());
	AC_CSCharacter* Unit = Cast<AC_CSCharacter>(Controller->GetPawn());

	Cast<IC_CharacterInterface>(Unit)->SPSkill();

	return EBTNodeResult::InProgress;
}

void UC_BTTaskSP::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AC_CSAIController* Controller = Cast<AC_CSAIController>(OwnerComp.GetOwner());
	AC_CSCharacter* Unit = Cast<AC_CSCharacter>(Controller->GetPawn());

	if (Unit->GetCharacterState() == ECharacterState::Idle)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
	}
}
