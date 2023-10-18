// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "C_CharacterInterface.h"
#include "Enum/ECharacterState.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_CSCharacter.generated.h"

enum class ECharacterState :uint8;

UCLASS(ABSTRACT)
class CSPROJECT_API AC_CSCharacter : public ACharacter, public IC_CharacterInterface
{
	GENERATED_BODY()


private:
	//Status
	UPROPERTY(VisibleDefaultsOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		class UC_StatusComponent* Status;
protected:
	UPROPERTY(EditAnywhere, Category = "TeamID", meta = (AllowPrivateAccess = "true"))
		uint8 TeamID;
	UPROPERTY(EditAnywhere, Category = "BTree", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* BehaviorTree;

public:
	AC_CSCharacter();

	FORCEINLINE UC_StatusComponent* GetStatus() { return Status; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }
	FORCEINLINE class UBehaviorTree* GetTree() { return BehaviorTree; }
	FORCEINLINE bool IsDead() { return *CharacterState == ECharacterState::Dead; }

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnConstruction(FTransform const& Transform) override;

	void PrintState();
	//Montage&Notify
	UFUNCTION()
		void CharacterMontageStarted(UAnimMontage* const Montage);
	UFUNCTION()
		virtual void CharacterMontageEnded(UAnimMontage* const Montage = 0, bool bInterrupted = 0);
	UFUNCTION()
		virtual void CharacterMontageBlendingOut(UAnimMontage* const montage = 0, bool bInterrupted = 0);
	
	UFUNCTION()
		virtual void OnNotifyStart(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	UFUNCTION()
		virtual void OnNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

		

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	void Attack() override;
	void SPSkill() override;
	void ULTSkill() override;


private:
	void InitState();
	void InitWeapon();
	void InitSkill();
	void MoveForward();

	virtual void Destroyed() override;

public:
	void RemoveTarget(AActor* Inactor);
public:
	//Weapon
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AC_Weapon> WeaponClass;
	class IC_WeaponInterface* Weapon;

	//PassiveSKill
	UPROPERTY(EditAnywhere, Category = "PasiveSkill")
		TArray<TSubclassOf<class AC_Skill>> PassiveSkillClasses;
	TArray<class IC_SkillInterface*> PasiveSkills;

	//SpecialSkill
	UPROPERTY(EditAnywhere, Category = "SpecialSkill")
		TSubclassOf<class AC_Skill> SpecialSkillClass;
	class IC_SkillInterface* SpecialSkill;

	//UltimateSkill
	UPROPERTY(EditAnywhere, Category = "UltimateSkill")
		TSubclassOf<class AC_Skill> UltimateSkillClass;
	class IC_SkillInterface* UltimateSkill;

	TSharedPtr<ECharacterState> CharacterState;
	TMap<ECharacterState, FString> StateToName;

	AActor* Target;
	TSet<AActor*> Targets;
};
