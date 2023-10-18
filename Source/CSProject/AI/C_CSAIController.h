// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_CSAIController.generated.h"

/**
 * 
 */
UCLASS()
class CSPROJECT_API AC_CSAIController : public AAIController
{
	GENERATED_BODY()
	

private:

	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception;
	UPROPERTY(VisibleDefaultsOnly)
		class UC_BehaviorComponent* Behavior;

public:
	AC_CSAIController();

	virtual void Tick(const float DeltaSecond) override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	void RemoveTarget(AActor* Inactor);

	class UC_BehaviorComponent* GetBehavior() { return Behavior; }
	class UBlackboardComponent* GetBlackboard() { return Blackboard; }

	FORCEINLINE float GetTargetDist() { return ClosestDist; }

private:
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdateActors);

	AActor* GetClosestActor();

private:

	class AC_CSCharacter* Owner;
	class UAISenseConfig_Sight* Sight;

	TSet<AActor*> SensedActors;
	class AActor* Target;
	float ClosestDist;

	

};
