#include "AI/C_CSAIController.h"
#include "Character/C_CSCharacter.h"
#include "Environment/C_Base_V2.h"
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
	AC_CSCharacter* OwningPawn = Cast<AC_CSCharacter>(GetPawn());
	if (OwningPawn->GetTeamID() == 0)
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Magenta, FString::SanitizeFloat(SensedActors.Num()));
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
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::GetClosestActor, 0.1f, true, 0);
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
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Remove Target!!!!!!!!!!!!!!!");
	if (SensedActors.Num())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Num != 0");
		if (SensedActors.Contains(Inactor))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Contains Actor");
			uint8 removenum = SensedActors.Remove(Inactor);
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, FString::SanitizeFloat(removenum));
			if (Target == Inactor)
			{
				Target = nullptr;
				Cast<AC_CSCharacter>(GetPawn())->SetTarget(nullptr);
				Blackboard->SetValueAsObject("Target", nullptr);
				TargetDist = 9999.0f;
			}
		}
	}
}

void AC_CSAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdateActors)
{
	AC_CSCharacter* OwningPawn = Cast<AC_CSCharacter>(GetPawn());
	if (OwningPawn)
	{
		TArray<AActor*> actors;
		Perception->GetCurrentlyPerceivedActors(nullptr, actors);

		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Sensed Actor!");

		for (AActor* actor : actors)
		{
			if (!actor->IsA(AC_CSCharacter::StaticClass()) && !actor->IsA(AC_Base_V2::StaticClass()))
				continue;
			if (Cast<AC_CSCharacter>(actor))
			{
				if (Cast<AC_CSCharacter>(actor)->GetTeamID() == OwningPawn->GetTeamID() || Cast<AC_CSCharacter>(actor)->IsDead())
					continue;
			}
			if (Cast<AC_Base_V2>(actor))
			{
				if (Cast<AC_Base_V2>(actor)->GetTeamID() == OwningPawn->GetTeamID())
					continue;
			}

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

}

void AC_CSAIController::GetClosestActor()
{
	AC_CSCharacter* OwningPawn = Cast<AC_CSCharacter>(GetPawn());
	if (OwningPawn)
	{
		if (SensedActors.Num())
		{
			
			AActor* ClosestActor = nullptr;

			float ClosestDist = OwningPawn->GetStatus()->GetMaxSightRange() + 300;
			for (AActor* actor : SensedActors)
			{
				if (actor && OwningPawn)
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
}
