#include "Components/C_BehaviorComponent.h"
#include "Character/C_CSCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UC_BehaviorComponent::UC_BehaviorComponent()
{
}

bool UC_BehaviorComponent::IsType(EBehaviorType InType)
{
	return GetType() == InType;
}

void UC_BehaviorComponent::ChangeType(EBehaviorType InType)
{
	Blackboard->SetValueAsEnum(BehaviorKey, (uint8)InType);
}

AActor* UC_BehaviorComponent::GetTarget()
{
	return Cast<AActor>(Blackboard->GetValueAsObject(TargetKey));
}

EBehaviorType UC_BehaviorComponent::GetType()
{
	return (EBehaviorType)Blackboard->GetValueAsEnum(BehaviorKey);
}




