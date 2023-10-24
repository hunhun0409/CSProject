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

	LeftBaseData.CurCost = MaxCost;
	RightBaseData.CurCost = MaxCost;

	for (size_t i = 0; i < 2; i++)
	{
		Map->AccessBaseData((bool)i)->UpdateHP.AddUFunction(this, "CheckHP");

		CameraMovablePosY[i] = Map->AccessBaseData((bool)i)->GetActorLocation().Y;
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
	if (AC_Base* LeftBase = Map->AccessBaseData(1))
	{
		LeftBaseData.CurHP = LeftBase->GetHP();
		LeftBaseData.MaxHP = LeftBase->GetMaxHP();
	}
	if (AC_Base* RightBase = Map->AccessBaseData(0))
	{
		RightBaseData.CurHP = RightBase->GetHP();
		RightBaseData.MaxHP = RightBase->GetMaxHP();
	}

	Datas.PlayerBaseHP = LeftBaseData.CurHP / LeftBaseData.MaxHP;
	Datas.EnemyBaseHP = RightBaseData.CurHP / RightBaseData.MaxHP;

	UIDataUpdated.ExecuteIfBound();
}

void AC_GameModeBase::CostReduce(const bool& IsLeft, const int& Cost)
{
	if (IsLeft)
	{
		LeftBaseData.CurCost -= Cost;
		LeftBaseData.IsCostFull = false;
	}
	else
	{
		RightBaseData.CurCost -= Cost;
		RightBaseData.IsCostFull = false;
	}

	UIDataUpdated.ExecuteIfBound();
}

void AC_GameModeBase::RestoreCost(const float& DeltaTime)
{

	if(!RightBaseData.IsCostFull)
		if (RightBaseData.CurCost <= MaxCost)
			RightBaseData.CurCost += DeltaTime * CostRegenRatio;
		else
		{
			RightBaseData.CurCost = MaxCost;
			RightBaseData.IsCostFull = true;
		}

	if (!LeftBaseData.IsCostFull)
	{
		if (LeftBaseData.CurCost <= MaxCost)
			LeftBaseData.CurCost += DeltaTime * CostRegenRatio;
		else
		{
			LeftBaseData.CurCost = MaxCost;
			LeftBaseData.IsCostFull = true;
		}

		Datas.CurCost = LeftBaseData.CurCost;
		
		if (Datas.CurCost - (int)Datas.CurCost < 0.01f )
			UIDataUpdated.ExecuteIfBound();
	}
}

