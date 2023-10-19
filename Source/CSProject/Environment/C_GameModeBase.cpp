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

	if (Field)
		Map = Cast<AC_Field>(GetWorld()->SpawnActor(Field));

	LeftBase.CurCost = MaxCost;
	RightBase.CurCost = MaxCost;

	for (size_t i = 0; i < 2; i++)
	{
		if (!Map->AccessBaseData((bool)i)->UpdateHP.IsBound())
			Map->AccessBaseData((bool)i)->UpdateHP.BindUFunction(this, "CheckHP");

	}

	RestoreCost(0.0f);
	CheckHP();


	
}

void AC_GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	RestoreCost(DeltaTime);
}

void AC_GameModeBase::CheckHP()
{
	LeftBase.CurHP = Map->AccessBaseData(1)->GetHP();
	LeftBase.MaxHP = Map->AccessBaseData(1)->GetMaxHP();
	RightBase.CurHP = Map->AccessBaseData(0)->GetHP();
	RightBase.MaxHP = Map->AccessBaseData(0)->GetMaxHP();

	Datas.PlayerBaseHP = LeftBase.CurHP / LeftBase.MaxHP;
	Datas.EnemyBaseHP = RightBase.CurHP / RightBase.MaxHP;

	UIDataUpdated.ExecuteIfBound();
}

void AC_GameModeBase::CostReduce(const bool& IsLeft, const int& Cost)
{
	if (IsLeft)
	{
		LeftBase.CurCost -= Cost;
		LeftBase.IsCostFull = false;
	}
	else
	{
		RightBase.CurCost -= Cost;
		RightBase.IsCostFull = false;
	}

	UIDataUpdated.ExecuteIfBound();
}

void AC_GameModeBase::RestoreCost(const float& DeltaTime)
{

	if(!RightBase.IsCostFull)
		if (RightBase.CurCost <= MaxCost)
			RightBase.CurCost += DeltaTime * CostRegenRatio;
		else
		{
			RightBase.CurCost = MaxCost;
			RightBase.IsCostFull = true;
		}

	if (!LeftBase.IsCostFull)
	{
		if (LeftBase.CurCost <= MaxCost)
			LeftBase.CurCost += DeltaTime * CostRegenRatio;
		else
		{
			LeftBase.CurCost = MaxCost;
			LeftBase.IsCostFull = true;
		}

		Datas.CurCost = LeftBase.CurCost;
		
		if (Datas.CurCost - (int)Datas.CurCost < 0.01f )
			UIDataUpdated.ExecuteIfBound();
	}
}

