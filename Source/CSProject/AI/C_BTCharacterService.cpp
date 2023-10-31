#include "AI/C_BTCharacterService.h"
#include "AI/C_CSAIController.h"
#include "Character/C_CSCharacter.h"
#include "Enum/ECharacterState.h"
#include "Components/C_StatusComponent.h"
#include "Components/C_BehaviorComponent.h"


UC_BTCharacterService::UC_BTCharacterService()
{
	NodeName = "CS_Character";
}

void UC_BTCharacterService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AC_CSAIController* controller = Cast<AC_CSAIController>(OwnerComp.GetOwner());
	UC_BehaviorComponent* behavior = controller->GetBehavior();

	AC_CSCharacter* unit = Cast<AC_CSCharacter>(controller->GetPawn());
	AActor* target = behavior->GetTarget();


	if (unit->IsDead())
	{
		unit->bMove = false;
		behavior->ChangeType(EBehaviorType::Dead);
		return;
	}
	if (!IsValid(target))
	{
		behavior->ChangeType(EBehaviorType::Move);
		return;
	}

	if (IsValid(target))
	{
		unit->bMove = false;
		float distance = controller->GetTargetDist();
		float attackRange = unit->GetStatus()->GetMaxAttackRange();
		if (distance <= attackRange)
		{

			if (unit->bCanActivateULT)
			{
				behavior->ChangeType(EBehaviorType::ULTSkill);
				return;
			}
			if (unit->bCanActivateSP)
			{
				behavior->ChangeType(EBehaviorType::SPSkill);
				return;
			}
			behavior->ChangeType(EBehaviorType::Attack);
			return;
		}
		else
		{
			behavior->ChangeType(EBehaviorType::Trace);
			return;
		}
	}
}
