// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTTaskUlt.generated.h"

/**
 * 
 */
UCLASS()
class CSPROJECT_API UC_BTTaskUlt : public UBTTaskNode
{
	GENERATED_BODY()
	

public:
	UC_BTTaskUlt();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

public:
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
