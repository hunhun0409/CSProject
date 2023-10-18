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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Name")
		FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lv")
		uint8 Level = 1;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float MaxHealth = 1000.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		float CurHealth;

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

	////레벨당 증가량

	//UPROPERTY(EditDefaultsOnly)
	//	float LV1_Health = 10.0f;

	//UPROPERTY(EditDefaultsOnly)
	//	float Health_IncreaseAmount = 10.0f;

	//UPROPERTY(EditDefaultsOnly)
	//	float LV1_Attack = 10.0f;

	//UPROPERTY(EditDefaultsOnly)
	//	float Attack_IncreaseAmount = 10.0f;

	//UPROPERTY(EditDefaultsOnly)
	//	float LV1_Defenseh = 10.0f;

	//UPROPERTY(EditDefaultsOnly)
	//	float Defense_IncreaseAmount = 1.0f;

	//UPROPERTY(EditDefaultsOnly)
	//	float LV1_Crit = 10.0f;

	//UPROPERTY(EditDefaultsOnly)
	//	float Crit_IncreaseAmount = 1.0f;

	//UPROPERTY(EditDefaultsOnly)
	//	float LV1_Hit = 10.0f;

	//UPROPERTY(EditDefaultsOnly)
	//	float Hit_IncreaseAmount = 100.0f;

	

public:
	FORCEINLINE ECharacterRank GetCharacterRank() { return CharacterRank; }
	FORCEINLINE ECharacterType GetCharacterType() { return CharacterType; }
	FORCEINLINE EClassType GetClassType() { return ClassType; }
	FORCEINLINE EMoveType GetEMoveType() { return MoveType; }
	FORCEINLINE EAttackType GetAttackType() { return AttackType; }
	FORCEINLINE float GetMaxHealth() { return MaxHealth; } 
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

	void SetMaxHealth(float Value);
	FORCEINLINE void SetAttack(float Value) {  Attack = Value; }
	FORCEINLINE void SetDefense(float Value) {  Defense = Value; }
	FORCEINLINE void SetCrit(float Value) {  Crit = Value; }
	FORCEINLINE void SetCritDamage(float Value) {  CritDamage = Value; }
	FORCEINLINE void SetHit(float Value) {  Hit = Value; }
	FORCEINLINE void SetAttackRate(float Value) {  AttackRate = Value; }
	FORCEINLINE void SetMaxSightRange(float Value) {  MaxSightRange = Value; }
	FORCEINLINE void SetMaxAttackRange(float Value) {  MaxAttackRange = Value; }
	FORCEINLINE void SetMovementSpeed(float Value) {  MovementSpeed = Value; }

public:	
	UC_StatusComponent();


protected:
	virtual void BeginPlay() override;
public:
	void ApplyStatus();
	void AddHealth(float InAmount);
private:
	
};
