// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTTaskAttack.generated.h"

/**
 * 
 */
UCLASS()
class CSPROJECT_API UC_BTTaskAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UC_BTTaskAttack();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
