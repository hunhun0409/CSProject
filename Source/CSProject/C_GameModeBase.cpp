// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GameModeBase.h"
#include "Components/BoxComponent.h"
#include "C_Field.h"
#include "C_Base.h"

AC_GameModeBase::AC_GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC_GameModeBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void AC_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if(Field)
		GetWorld()->SpawnActor(Field);

	LeftCost = MaxCost;
	RightCost = MaxCost;
}

void AC_GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	RestoreCost(DeltaTime);
}

void AC_GameModeBase::RestoreCost(float DeltaTime)
{
	if (LeftCost <= MaxCost)
		LeftCost += DeltaTime * CostRegenRatio;
	else
		LeftCost = MaxCost;

	if (RightCost <= MaxCost)
		RightCost += DeltaTime * CostRegenRatio;
	else
		RightCost = MaxCost;
}
