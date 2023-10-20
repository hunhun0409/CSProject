// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTTaskMove.generated.h"

/**
 * 
 */
UCLASS()
class CSPROJECT_API UC_BTTaskMove : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UC_BTTaskMove();
	
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
