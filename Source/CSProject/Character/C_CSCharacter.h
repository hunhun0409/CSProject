// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_CSCharacter.generated.h"

UCLASS(ABSTRACT)
class CSPROJECT_API AC_CSCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	//Status
	UPROPERTY(VisibleDefaultsOnly, Category = "Status")
		class UC_StatusComponent* Status;


public:
	// Sets default values for this character's properties
	AC_CSCharacter();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void InitWeapon();


public:
	//Weapon
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class AC_Weapon>> WeaponClasses;
	class IC_WeaponInterface* Weapon;
	TArray<decltype(Weapon)> Weapons;
};
