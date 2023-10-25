// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "C_HitResultDisplayer.generated.h"

UCLASS()
class CSPROJECT_API AC_HitResultDisplayer : public AHUD
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_HitResultDisplayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
