// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enum/ECharacterRank.h"
#include "Enum/ECharacterType.h"
#include "Enum/EClassType.h"
#include "Enum/EMoveType.h"
#include "Enum/EAttackType.h"

#include "Components/ActorComponent.h"
#include "C_StatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CSPROJECT_API UC_StatusComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
		ECharacterRank CharacterRank;

	UPROPERTY(EditDefaultsOnly)
		ECharacterType CharacterType;

	UPROPERTY(EditDefaultsOnly)
		EClassType ClassType;

	UPROPERTY(EditDefaultsOnly)
		EMoveType MoveType;

	UPROPERTY(EditDefaultsOnly)
		EAttackType AttackType;

	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 1000.0f;

	UPROPERTY(EditDefaultsOnly)
		float Attack = 100.0f;

	UPROPERTY(EditDefaultsOnly)
		float Defense = 100.0f;

	UPROPERTY(EditDefaultsOnly)
		float Crit = 100.0f;

	UPROPERTY(EditDefaultsOnly)
		float CritDamage = 50.0f;

	UPROPERTY(EditDefaultsOnly)
		float Hit = 100.0f;

	UPROPERTY(EditDefaultsOnly)
		float AttackRate = 1.0f;

	UPROPERTY(EditDefaultsOnly)
		float MaxSightRange = 600.0f;

	UPROPERTY(EditDefaultsOnly)
		float MaxAttackRange = 400.0f;

	UPROPERTY(EditDefaultsOnly)
		float MovementSpeed = 600.0f;

public:
	FORCEINLINE ECharacterRank GetCharacterRank() { return CharacterRank; }
	FORCEINLINE ECharacterType GetCharacterType() { return CharacterType; }
	FORCEINLINE EClassType GetClassType() { return ClassType; }
	FORCEINLINE EMoveType GetEMoveType() { return MoveType; }
	FORCEINLINE EAttackType GetAttackType() { return AttackType; }
	FORCEINLINE float GetCurHealth() { return CurHealth; } 
	FORCEINLINE float GetAttack() { return Attack; }
	FORCEINLINE float GetDefense() { return Defense; }
	FORCEINLINE float GetCrit() { return Crit; }
	FORCEINLINE float GetCritDamage() { return CritDamage; }
	FORCEINLINE float GetHit() { return Hit; }
	FORCEINLINE float GetAttackRate() { return AttackRate; }
	FORCEINLINE float GetMaxSightRange() { return MaxSightRange; }
	FORCEINLINE float GetMaxAttackRange() { return MaxAttackRange; }
	FORCEINLINE float GetMovementSpeed() { return MovementSpeed; }

public:	
	UC_StatusComponent();

	void AddHealth(float InAmount);

protected:
	virtual void BeginPlay() override;
		

private:
	float CurHealth;
};
