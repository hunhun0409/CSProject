#include "AI/C_CSAIController.h"
#include "Character/C_CSCharacter.h"
#include "Environment/C_Base.h"
#include "perception/aiperceptionComponent.h"
#include "perception/AISenseconfig_sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboardcomponent.h"
#include "Components/C_Behaviorcomponent.h"
#include "Components/C_Statuscomponent.h"
#include "DrawDebugHelpers.h"

#define CreateDefaultSubobjectAuto(Component)\
Component = CreateDefaultSubobject<std::remove_reference<decltype(*Component)>::type>(#Component)

AC_CSAIController::AC_CSAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobjectAuto(Blackboard);
	CreateDefaultSubobjectAuto(Perception);
	CreateDefaultSubobjectAuto(Behavior);

	CreateDefaultSubobjectAuto(Sight);
	
	
	Target = nullptr;
}

void AC_CSAIController::Tick(const float DeltaSecond)
{
	if (bDrawDebug) {
		if (Owner)
		{
			FVector center = Owner->GetActorLocation();
			center.Z += 50;

			DrawDebugCircle(GetWorld(), center, Cast<AC_CSCharacter>(Owner)->GetStatus()->GetMaxAttackRange(), 300, FColor::Red,
				false, -1.0f, 0, 0, FVector::RightVector, FVector::ForwardVector);
		}
	}
}

void AC_CSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Sight->SightRadius = Sight->LoseSightRadius = Cast<AC_CSCharacter>(InPawn)->GetMaxSightRange();
	Sight->PeripheralVisionAngleDegrees = 180.0f;
	Sight->SetMaxAge(0);
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());

	//Sight->SightRadius = Cast<AC_CSCharacter>(Owner)->GetStatus()->GetMaxSightRange();

	Owner = Cast<AC_CSCharacter>(GetPawn());

	SetGenericTeamId(Owner->GetTeamID());

	Perception->OnPerceptionUpdated.AddDynamic(this, &ThisClass::OnPerceptionUpdated);

	UseBlackboard(Owner->GetTree()->BlackboardAsset, Blackboard);

	Behavior->SetBlackboard(Blackboard);

	RunBehaviorTree(Owner->GetTree());

	if (Timer == FTimerHandle())
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::GetClosestActor, 0.2f, true, 0);
	}
}

void AC_CSAIController::OnUnPossess()
{
	Super::OnUnPossess();
	if (Timer != FTimerHandle())
	{
		GetWorld()->GetTimerManager().ClearTimer(Timer);
	}
}

void AC_CSAIController::RemoveTarget(AActor* Inactor)
{
	if (SensedActors.Num())
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
		}
	}
}

void AC_CSAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdateActors)
{
	AC_CSCharacter* OwningPawn = Cast<AC_CSCharacter>(GetPawn());
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Sensed Actor!");

	for (AActor* actor : actors)
	{
		
		if (!actor->IsA(AC_CSCharacter::StaticClass()) && !actor->IsA(AC_Base::StaticClass()))
			continue;
		if (Cast<AC_CSCharacter>(actor)->GetTeamID() == OwningPawn->GetTeamID())
			continue;
		//else if (Cast<AC_Base>(actor)->GetTeamID() == OwningPawn->GetTeamID())
		//	continue;

		if (SensedActors.Contains(actor))
		{
			if (OwningPawn->GetDistanceTo(actor) > 1000)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::SanitizeFloat(OwningPawn->GetDistanceTo(actor)));

				SensedActors.Remove(actor);
			}
		}
		else
		{
			SensedActors.Add(actor);
		}
	}
}

void AC_CSAIController::GetClosestActor()
{
	if (SensedActors.Num())
	{
		AC_CSCharacter* OwningPawn = Cast<AC_CSCharacter>(GetPawn());
		AActor* ClosestActor = nullptr;

		float ClosestDist = OwningPawn->GetStatus()->GetMaxSightRange();
		for (AActor* actor : SensedActors)
		{
			if (actor)
			{
				if (OwningPawn->GetDistanceTo(actor) <= ClosestDist)
				{
					ClosestDist = OwningPawn->GetDistanceTo(actor);
					ClosestActor = actor;
				}
			}
		}
		TargetDist = ClosestDist;
		Target = ClosestActor;
		OwningPawn->Target = Target;
		Blackboard->SetValueAsObject("Target", Target);
	}
}
