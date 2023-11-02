#include "AI/C_BTTaskAttack.h"
#include "AI/C_CSAIController.h"
#include "Character/C_CSCHaracter.h"
#include "Interface/C_CharacterInterface.h"

UC_BTTaskAttack::UC_BTTaskAttack()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UC_BTTaskAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	

	AC_CSAIController* Controller = Cast<AC_CSAIController>(OwnerComp.GetOwner());
	AC_CSCharacter* Unit = Cast<AC_CSCharacter>(Controller->GetPawn());

	Unit->bMove = false;
	Cast<IC_CharacterInterface>(Unit)->Attack();

	return EBTNodeResult::Succeeded;
}


