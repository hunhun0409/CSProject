// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Base.generated.h"

UCLASS(Abstract)
class CSPROJECT_API AC_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly)
		int MaxHP;
	int CurHP;

	UPROPERTY(EditDefaultsOnly)
		float AttackRange;

	UPROPERTY(EditDefaultsOnly)
		float Damage;

};