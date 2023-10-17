// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "C_CharacterInterface.h"

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

public:
	AC_CSCharacter();

	FORCEINLINE UC_StatusComponent* GetStatus() { return Status; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void Attack() override;
	virtual void SpecialSkill() override;
	virtual void UltimateSkill() override;


private:
	void InitWeapon();


public:
	//Weapon
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AC_Weapon> WeaponClass;
	class IC_WeaponInterface* Weapon;

	

	TSharedPtr<ECharacterState> CharacterState;
};
