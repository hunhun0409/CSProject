#include "AI/C_BTTaskMove.h"
#include "AI/C_CSAIController.h"
#include "Character/C_CSCHaracter.h"

UC_BTTaskMove::UC_BTTaskMove()
{
	NodeName = "Move";
}

EBTNodeResult::Type UC_BTTaskMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AC_CSAIController* Controller = Cast<AC_CSAIController>(OwnerComp.GetOwner());
	AC_CSCharacter* Unit = Cast<AC_CSCharacter>(Controller->GetPawn());

	Unit->bMove = true;

	return EBTNodeResult::Succeeded;
}

