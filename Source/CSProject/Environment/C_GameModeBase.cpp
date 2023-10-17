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

	Datas.CostRegenRatio = CostRegenRatio;

	if(Field)
		Map = Cast<AC_Field>(GetWorld()->SpawnActor(Field));

	LeftBase.CurCost = MaxCost;
	RightBase.CurCost = MaxCost;

	CheckHP();

	for (size_t i = 0; i < 2; i++)
	{
		if(!Map->AccessBaseData((bool)i)->UpdateHP.IsBound())
			Map->AccessBaseData((bool)i)->UpdateHP.BindUFunction(this, "CheckHP");

	}

	
}

void AC_GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	RestoreCost(DeltaTime);
}

void AC_GameModeBase::CheckHP()
{
	LeftBase.CurHP = Map->AccessBaseData(1)->GetHP();
	RightBase.CurHP = Map->AccessBaseData(0)->GetHP();

	Datas.EnemyBaseHP = RightBase.CurHP;
	Datas.PlayerBaseHP = LeftBase.CurHP;

	UIDataUpdated;
}

void AC_GameModeBase::RestoreCost(float DeltaTime)
{

	if (LeftBase.CurCost <= MaxCost)
		LeftBase.CurCost += DeltaTime * CostRegenRatio;
	else
		LeftBase.CurCost = MaxCost;

	if (RightBase.CurCost <= MaxCost)
		RightBase.CurCost += DeltaTime * CostRegenRatio;
	else
		RightBase.CurCost = MaxCost;

	Datas.CurCost = LeftBase.CurCost;
	
	if (Datas.CurCost / 1 >= 1)
		UIDataUpdated;
}

