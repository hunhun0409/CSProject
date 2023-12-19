// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interface/C_CharacterInterface.h"
#include "Interface/C_DamageHandleInterface.h"
#include "Enum/ECharacterState.h"
#include "DataTables/StatusData.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_CSCharacter.generated.h"

enum class ECharacterState :uint8;

UCLASS(ABSTRACT)
class CSPROJECT_API AC_CSCharacter : 
	public ACharacter, 
	public IC_CharacterInterface,
	public IC_DamageHandleInterface
{
	GENERATED_BODY()


private:
	//Status
	UPROPERTY(EditDefaultsOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		FName Name;

	UPROPERTY(EditDefaultsOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		uint8 Cost;

	UPROPERTY(EditDefaultsOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float MaxSightRange;
	//Status
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		class UC_StatusComponent* Status;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* StatusUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
		class UTexture2D* CharacterImage;

	UPROPERTY(EditDefaultsOnly, Category = "OnDamaged")
		class UParticleSystem* HitEffect;

	UPROPERTY(EditDefaultsOnly, Category = "OnDamaged")
		TArray<class UAnimMontage*> DieMontage;

	
protected:
	UPROPERTY(EditAnywhere, Category = "TeamID", meta = (AllowPrivateAccess = "true"))
		uint8 TeamID;
	UPROPERTY(EditAnywhere, Category = "BTree", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* BehaviorTree;

public:
	AC_CSCharacter();

	FORCEINLINE uint8 GetCost() { return Cost; }
	FORCEINLINE float GetMaxSightRange() { return MaxSightRange; }
	FORCEINLINE UC_StatusComponent* GetStatus() { return Status; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }
	FORCEINLINE void SetTeamID(uint8 InTeamID) { TeamID = InTeamID; }
	FORCEINLINE class UBehaviorTree* GetTree() { return BehaviorTree; }
	FORCEINLINE ECharacterState GetCharacterState() { return *CharacterState; }
	FORCEINLINE void SetTarget(AActor* Inactor) { Target = Inactor; }

	FORCEINLINE bool IsDead() { return *CharacterState == ECharacterState::Dead; }
	FORCEINLINE UTexture2D* GetCharacterButtonImage() { return CharacterImage; }
	FORCEINLINE FName GetCharacterName() { return Name; }
protected:
	virtual void BeginPlay() override;

	void OnConstruction(FTransform const& Transform) override;

	void PrintState();
	//Montage&Notify
	UFUNCTION()
		virtual void CharacterMontageEnded(UAnimMontage* const Montage = 0, bool bInterrupted = 0);
	UFUNCTION()
		virtual void CharacterMontageBlendingOut(UAnimMontage* const montage = 0, bool bInterrupted = 0);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, Category = "StatusUI")
		float GetSPSkillCooldown();
	UFUNCTION(BlueprintCallable, Category = "StatusUI")
		float GetULTSkillCooldown();

	void SetSPSkillCoolRate(const float& InRate);
	void SetULTSkillCoolRate(const float& InRate);

protected:
	void Attack() override;
	void SPSkill() override;
	void ULTSkill() override;

	void Respawn() override;
	void Die() override;

private:
	void InitState();
	void InitWeapon();
	void InitSkill();
	void MoveForward();

	UFUNCTION()
		virtual void GetDamaged(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	virtual float CalculateDamage(float Damage, AActor* DamageCauser) override;


protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Status")
		void UpdateLifeGauge();
	UFUNCTION(BlueprintImplementableEvent, Category = "Status")
		void UpdateCooldown();
	
public:
	//Weapon
	UPROPERTY(EditAnywhere, Category = "Weapon")
		TSubclassOf<class AC_Weapon> WeaponClass;
	class IC_WeaponInterface* Weapon;

	//PassiveSKill
	UPROPERTY(EditAnywhere, Category = "Skill")
		TArray<TSubclassOf<class AC_Skill>> PassiveSkillClasses;
	TArray<class IC_SkillInterface*> PasiveSkills;

	//SpecialSkill
	UPROPERTY(EditAnywhere, Category = "Skill")
		TSubclassOf<class AC_Skill> SpecialSkillClass;
	class IC_SkillInterface* SpecialSkill = nullptr;

	//UltimateSkill
	UPROPERTY(EditAnywhere, Category = "Skill")
		TSubclassOf<class AC_Skill> UltimateSkillClass;
	class IC_SkillInterface* UltimateSkill = nullptr;

	TSharedPtr<ECharacterState> CharacterState;
	TMap<ECharacterState, FString> StateToName;

	UPROPERTY(BlueprintReadOnly)
		AActor* Target;


	UPROPERTY(EditDefaultsOnly, Category = "Status")
		UDataTable* DataTable;

	TMap<FName, TArray<FStatusData>> StatusMap;

	//��Ÿ ���� �������� true
	bool bCanActivateAttack = true;
	//Ư���� ���� �������� true
	bool bCanActivateSP = false;
	//�ñر� ���� �������� true
	bool bCanActivateULT = false;
	//�ʵ忡 ��ȯ�������� true, �ƴϸ� false
	bool bInBattle = false;

	bool bMove = true;
};
