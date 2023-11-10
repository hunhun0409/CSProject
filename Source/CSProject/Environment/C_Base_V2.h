// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interface/C_DamageHandleInterface.h"
#include "Components/C_StatusComponent.h"
#include "C_Base_V2.generated.h"

UCLASS(Abstract)
class CSPROJECT_API AC_Base_V2 : public APawn, public IC_DamageHandleInterface
{
	GENERATED_BODY()

public:
	FORCEINLINE UC_StatusComponent* GetStatus() { return Status; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }

	TDelegate<void(FVector, int, bool)> Spawn;
	// �÷��̾� �����ؼ� true -> �÷��̾� ��Ʈ�ѷ����� ����(��ȯ ����), false ->�ڵ� ��ȯ
	UFUNCTION()
		void SpawnCharacter(const FVector& Location, const int& SlotNum, const bool& IsLeftTeam);

public:
	// Sets default values for this pawn's properties
	AC_Base_V2();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Tick(float DeltaTime) override;

	virtual float CalculateDamage(float Damage, AActor* DamageCauser) override;

	UFUNCTION()
		virtual void GetDamaged(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);


public:	
	TMulticastDelegate<void()> UpdateHP;
	void SetTeamID(uint8 InTeamID);

	const bool& GetAutoPlay() { return IsAutoSpawning; }
	void SetAutoPlay(const bool& IsAuto) { IsAutoSpawning = IsAuto; }

protected:
	UPROPERTY(EditAnywhere, Category = "TeamID")
		uint8 TeamID;

	UPROPERTY(EditDefaultsOnly)
		class UAIPerceptionComponent* AIPerception;

	UPROPERTY(EditDefaultsOnly, Category = "Status")
		UDataTable* DataTable;

	TMap<FName, TArray<FStatusData>> StatusMap;

private:bool IsAutoSpawning = false;
	   FVector AutoSpawnLocation;

	   //Status
	   UPROPERTY(EditDefaultsOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		   FName Name;
	   //Status
	   UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		   class UC_StatusComponent* Status;

	   UPROPERTY(EditDefaultsOnly, Category = "OnDamaged")
		   class UParticleSystem* HitEffect;
};
