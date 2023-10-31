#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_BehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Move		UMETA(DisplayName = "Move"),
	Trace		UMETA(DisplayName = "Trace"),
	Attack		UMETA(DisplayName = "Attack"),
	SPSkill		UMETA(DisplayName = "SPSkill"),
	ULTSkill	UMETA(DisplayName = "ULTSkill"),
	Dead		UMETA(DisplayName = "Dead")
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CSPROJECT_API UC_BehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
		FName BehaviorKey = "Behavior";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
		FName TargetKey = "Target";

public:
	UC_BehaviorComponent();

	UFUNCTION(BlueprintPure)
		bool IsType(EBehaviorType InType);

	void ChangeType(EBehaviorType InType);

	AActor* GetTarget();

	void SetBlackboard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

protected:
	EBehaviorType GetType();


private:
	class UBlackboardComponent* Blackboard;
};
