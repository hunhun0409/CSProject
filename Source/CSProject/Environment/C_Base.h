// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/C_DamageHandleInterface.h"
#include "Components/C_StatusComponent.h"
#include "C_Base.generated.h"

UCLASS(Abstract)
class CSPROJECT_API AC_Base : public AActor, public IC_DamageHandleInterface
{
	GENERATED_BODY()
		//타워속성
	
public:	
	// Sets default values for this actor's properties
	AC_Base();

	FORCEINLINE UC_StatusComponent* GetStatus() { return Status; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual float CalculateDamage(float Damage, AActor* DamageCauser) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TMulticastDelegate<void()> UpdateHP;
	void SetTeamID(uint8 InTeamID) { TeamID = InTeamID; }

protected:

protected:
	UPROPERTY(EditAnywhere, Category = "TeamID", meta = (AllowPrivateAccess = "true"))
		uint8 TeamID;

	UPROPERTY(EditDefaultsOnly)
		class UAIPerceptionComponent* AIPerception;

	UPROPERTY(EditDefaultsOnly, Category = "Status")
		UDataTable* DataTable;

	TMap<FName, TArray<FStatusData>> StatusMap;

private:
	//Status
	UPROPERTY(EditDefaultsOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		FName Name;
	//Status
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		class UC_StatusComponent* Status;

	UPROPERTY(EditDefaultsOnly, Category = "OnDamaged")
		class UParticleSystem* HitEffect;

};
