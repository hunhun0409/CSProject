// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "C_BTCharacterService.generated.h"

/**
 * 
 */
UCLASS()
class CSPROJECT_API UC_BTCharacterService : public UBTService
{
	GENERATED_BODY()
	

public:

	UC_BTCharacterService();


protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
