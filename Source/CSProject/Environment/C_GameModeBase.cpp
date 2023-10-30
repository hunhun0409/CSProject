// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GameModeBase.h"
#include "Components/BoxComponent.h"
#include "C_Field.h"
#include "C_Base.h"
#include "Character/C_CSCharacter.h"

AC_GameModeBase::AC_GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC_GameModeBase::SpawnCharacter(const FVector& Location, const int& SlotNum, const bool& IsLeftTeam)
{
	if (IsLeftTeam)
	{

		if (Map->GetSpawnCollider(true)->Bounds.GetBox().IsInside(Location))
		{
			if (!LeftTeamSpawnCycle[SlotNum])
				return;
			
			int UnitCost = LeftTeamSpawnCycle[SlotNum].GetDefaultObject()->GetStatus()->GetCost();

			if (LeftBaseData.CurCost >= UnitCost)
			{
				CostReduce(true, UnitCost);

				FTransform SpawnTransform;
				SpawnTransform.SetLocation(Location);
				auto* Unit = Cast<AC_CSCharacter>(GetWorld()->SpawnActor(LeftTeamSpawnCycle[SlotNum], &SpawnTransform));
				Unit->SetTeamID(0);

				if (auto* Data = UnitBattleDatas.Find(Unit->GetStatus()->GetCharacterName()))
				{
					Unit->SetSPSkillCoolRate(Data->SPCoolRate);
					Unit->SetULTSkillCoolRate(Data->ULTCoolRate);
				}

				Datas.UnitOnFieldData.Emplace(Unit->GetStatus()->GetCharacterName(), true);

				if (LeftTeamSpawnCycle.Num() > 4)
				{
					LeftTeamSpawnCycle.Swap(SlotNum, 5);

					for (int i = 5; i < LeftTeamSpawnCycle.Num() - 1; i++)
						LeftTeamSpawnCycle.Swap(i, i + 1);
				}
				Datas.UnitImage.EmplaceAt(SlotNum, LeftTeamSpawnCycle[SlotNum].GetDefaultObject()->GetCharacterButtonImage());
				Datas.ButtonUnitName.EmplaceAt(SlotNum, LeftTeamSpawnCycle[SlotNum].GetDefaultObject()->GetStatus()->GetCharacterName());
				UIDataUpdated.ExecuteIfBound();
			}
		}
	}
	else
	{
		if (!RightTeamSpawnCycle[SlotNum])
			return;
		int UnitCost = RightTeamSpawnCycle[SlotNum].GetDefaultObject()->GetStatus()->GetCost();

		if (RightBaseData.CurCost >= UnitCost)
		{
			CostReduce(false, UnitCost);

			FTransform SpawnTransform;
			SpawnTransform.SetLocation(Location);
			auto* Unit = Cast<AC_CSCharacter>(GetWorld()->SpawnActor(RightTeamSpawnCycle[SlotNum], &SpawnTransform));
			Unit->SetTeamID(1);

			if (auto* Data = UnitBattleDatas.Find(Unit->GetStatus()->GetCharacterName()))
			{
				Unit->SetSPSkillCoolRate(Data->SPCoolRate);
				Unit->SetULTSkillCoolRate(Data->ULTCoolRate);
			}

			if (RightTeamSpawnCycle.Num() > 4)
			{
				RightTeamSpawnCycle.Swap(SlotNum, 5);

				for (int i = 5; i < RightTeamSpawnCycle.Num() - 1; i++)
					RightTeamSpawnCycle.Swap(i, i + 1);
			}
		}
	}
}

void AC_GameModeBase::SetVisiblePlayerSpawnableArea(const bool& IsVisible)
{
	Map->SetVisiblePlayerSpawnArea(IsVisible);
}

void AC_GameModeBase::UnitDiedDataUpdate(AC_CSCharacter* DiedUnit, const float& SPCoolRate, const float& ULTCoolRate)
{
	FName DiedUnitName = DiedUnit->GetStatus()->GetCharacterName();
	FUnitBattleData NewData;
	NewData.SPCoolRate = SPCoolRate;
	NewData.ULTCoolRate = ULTCoolRate;
	UnitBattleDatas.Emplace(DiedUnitName, NewData);

	if (DiedUnit->GetTeamID() == 0)
	{
		Datas.UnitOnFieldData.Emplace(DiedUnitName, false);
		UIDataUpdated.ExecuteIfBound();
	}
}

void AC_GameModeBase::PrintDamage(float FinalDamage, bool bCrit, bool bEvade, FVector ActorLocation)
{
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

	for (int i = 0; i < LeftTeamOrganization.Num(); i++)
	{
		LeftTeamSpawnCycle.Add(LeftTeamOrganization[i]);

		if (i < 4)
		{
			Datas.UnitImage.Emplace(LeftTeamSpawnCycle[i].GetDefaultObject()->GetCharacterButtonImage());
			Datas.ButtonUnitName.Emplace(LeftTeamSpawnCycle[i].GetDefaultObject()->GetCharacterName());
		}
	}
	for (int i = 0; i < RightTeamOrganization.Num(); i++)
	{
		RightTeamSpawnCycle.Add(RightTeamOrganization[i]);
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
		LeftBaseData.CurHP = LeftBase->GetStatus()->GetCurHealth();
		LeftBaseData.MaxHP = LeftBase->GetStatus()->GetMaxHealth();
	}
	if (AC_Base* RightBase = Map->AccessBaseData(0))
	{
		RightBaseData.CurHP = RightBase->GetStatus()->GetCurHealth();
		RightBaseData.MaxHP = RightBase->GetStatus()->GetMaxHealth();
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

