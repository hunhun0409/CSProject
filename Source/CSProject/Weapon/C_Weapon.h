// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/C_WeaponInterface.h"
#include "GameFramework/Actor.h"
#include "C_Weapon.generated.h"

UCLASS()
class CSPROJECT_API AC_Weapon : public AActor, public IC_WeaponInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UParticleSystemComponent* Trail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UParticleSystemComponent* Effect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
		class UAnimMontage* AttackMontage;

public:
	//¼ÒÄ¹
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Socket")
		FName SocketOnEquipped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Socket")
		FName SocketOnTrailStart;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Socket")
		FName SocketOnTrailEnd;


public:	
	AC_Weapon();

	virtual USkeletalMeshComponent* GetMesh();
protected:
	virtual void BeginPlay() override;


	void BeginAction() override;
	void EndAction() override;

	void Activate() override;
	void Deactivate() override;

	void ApplyDamage() override;

	void ActivateTrail() override;
	void DeactivateTrail() override;

	void ActivateEffect() override;
	void DeactivateEffect() override;



	UFUNCTION()
		virtual void OnNotifyStart(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	UFUNCTION()
		virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
		virtual void OnMontageInterrupted(UAnimMontage* Montage, bool bInterrupted);

	void NotifyCanAttack();

	
protected:
	FTimerHandle AttackTimer;

};
