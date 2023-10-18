#include "AI/C_CSAIController.h"
#include "Character/C_CSCharacter.h"
#include "perception/aiperceptionComponent.h"
#include "perception/AISenseconfig_sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboardcomponent.h"
#include "Components/C_Behaviorcomponent.h"
#include "Components/C_Statuscomponent.h"

#define CreateDefaultSubobjectAuto(Component)\
Component = CreateDefaultSubobject<std::remove_reference<decltype(*Component)>::type>(#Component)

AC_CSAIController::AC_CSAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobjectAuto(Blackboard);
	CreateDefaultSubobjectAuto(Perception);
	CreateDefaultSubobjectAuto(Behavior);

	CreateDefaultSubobjectAuto(Sight);
	//Sight->SightRadius = Cast<AC_CSCharacter>(Owner)->GetStatus()->GetMaxSightRange();
	Sight->SightRadius = Sight->LoseSightRadius = 600;
	Sight->PeripheralVisionAngleDegrees = 180.0f;
	Sight->SetMaxAge(0);
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;

	Perception->ConfigureSense(*Sight);

	Perception->SetDominantSense(*Sight->GetSenseImplementation());

	Target = nullptr;
	ClosestDist = BIG_NUMBER;
}

void AC_CSAIController::Tick(const float DeltaSecond)
{
	if (SensedActors.Num())
	{
		Target = GetClosestActor();
		Cast<AC_CSCharacter>(GetPawn())->Target = Target;
		Blackboard->SetValueAsObject("Target", Target);
	}
}

void AC_CSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Owner = Cast<AC_CSCharacter>(GetPawn());

	SetGenericTeamId(Owner->GetTeamID());

	Perception->OnPerceptionUpdated.AddDynamic(this, &ThisClass::OnPerceptionUpdated);

	UseBlackboard(Owner->GetTree()->BlackboardAsset, Blackboard);

	Behavior->SetBlackboard(Blackboard);

	RunBehaviorTree(Owner->GetTree());
}

void AC_CSAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AC_CSAIController::RemoveTarget(AActor* Inactor)
{
	if (SensedActors.Contains(Inactor))
	{
		SensedActors.Remove(Inactor);
		if (Target == Inactor)
		{
			Target = nullptr;
			Cast<AC_CSCharacter>(GetPawn())->Target = nullptr;
			Blackboard->SetValueAsObject("Target", nullptr);
		}
		if (SensedActors.Num() == 0)
			ClosestDist = BIG_NUMBER;
	}
}

void AC_CSAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdateActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);
	if (actors.Num() == 0)
		return;

	for (AActor* actor : actors)
	{
		if (SensedActors.Contains(actor))
		{
			if (Target == actor)
			{
				Target = nullptr;
				Cast<AC_CSCharacter>(GetPawn())->Target = nullptr;
				Blackboard->SetValueAsObject("Target", nullptr);
			}
			SensedActors.Remove(actor);
			if (SensedActors.Num() == 0)
				ClosestDist = BIG_NUMBER;
		}
		else
		{
			if (IsValid(actor) && Cast<AC_CSCharacter>(actor)->IsDead() != true)
			{
				SensedActors.Add(actor);
			}
		}
	}
}

AActor* AC_CSAIController::GetClosestActor()
{
	APawn* OwningPawn = GetPawn();
	AActor* ClosestActor = nullptr;
	for (AActor* actor : SensedActors)
	{
		if (OwningPawn->GetDistanceTo(actor) < ClosestDist)
		{
			ClosestDist = OwningPawn->GetDistanceTo(actor);
			ClosestActor = actor;
		}
	}
	return ClosestActor;
}
