// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/C_Skill.h"
#include "C_PassiveSkill.generated.h"

/**
 * 
 */
UCLASS()
class CSPROJECT_API AC_PassiveSkill : public AC_Skill
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	void ApplyEffectToPawn(APawn* InPawn) override;
protected:
	UPROPERTY(EditDefaultsOnly, Category = "HP")
		bool bChangeHP;
	UPROPERTY(EditDefaultsOnly, Category = "HP")
		float HP;
	UPROPERTY(EditDefaultsOnly, Category = "HP")
		float HP_IncreaseRate;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		bool bChangeAttack;
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		float Attack;
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		float Attack_IncreaseRate;

	UPROPERTY(EditDefaultsOnly, Category = "Defense")
		bool bChangeDefense;
	UPROPERTY(EditDefaultsOnly, Category = "Defense")
		float Defense;
	UPROPERTY(EditDefaultsOnly, Category = "Defense")
		float Defense_IncreaseRate;

	UPROPERTY(EditDefaultsOnly, Category = "Crit")
		bool bChangeCrit;
	UPROPERTY(EditDefaultsOnly, Category = "Crit")
		float Crit;
	UPROPERTY(EditDefaultsOnly, Category = "Crit")
		float Crit_IncreaseRate;

	UPROPERTY(EditDefaultsOnly, Category = "Crit Damage")
		bool bChangeCrit_Damage;
	UPROPERTY(EditDefaultsOnly, Category = "Crit Damage")
		float Crit_Damage;
	UPROPERTY(EditDefaultsOnly, Category = "Crit Damage")
		float Crit_Damage_IncreaseRate;

	UPROPERTY(EditDefaultsOnly, Category = "Hit")
		bool bChangeHit;
	UPROPERTY(EditDefaultsOnly, Category = "Hit")
		float Hit;
	UPROPERTY(EditDefaultsOnly, Category = "Hit")
		float Hit_IncreaseRate;

	UPROPERTY(EditDefaultsOnly, Category = "AttackRate")
		bool bChangeAttackRate;
	UPROPERTY(EditDefaultsOnly, Category = "AttackRate")
		float AttackRate;
	UPROPERTY(EditDefaultsOnly, Category = "AttackRate")
		float AttackRate_IncreaseRate;

	UPROPERTY(EditDefaultsOnly, Category = "MaxSightRange")
		bool bChangeMaxSightRange;
	UPROPERTY(EditDefaultsOnly, Category = "MaxSightRange")
		float MaxSightRange;
	UPROPERTY(EditDefaultsOnly, Category = "MaxSightRange")
		float MaxSightRange_IncreaseRate;

	UPROPERTY(EditDefaultsOnly, Category = "MaxAttackRange")
		bool bChangeMaxAttackRange;
	UPROPERTY(EditDefaultsOnly, Category = "MaxAttackRange")
		float MaxAttackRange;
	UPROPERTY(EditDefaultsOnly, Category = "MaxAttackRange")
		float MaxAttackRange_IncreaseRate;

	UPROPERTY(EditDefaultsOnly, Category = "MovementSpeed")
		bool bChangeMovementSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "MovementSpeed")
		float MovementSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "MovementSpeed")
		float MovementSpeed_IncreaseRate;
};
