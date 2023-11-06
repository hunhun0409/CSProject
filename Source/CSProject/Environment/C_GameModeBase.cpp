// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GameModeBase.h"
#include "Components/BoxComponent.h"
#include "C_Field.h"
#include "C_Base.h"
#include "Character/C_CSCharacter.h"
#include "Kismet/GameplayStatics.h"

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
			if (SlotNum >= LeftTeamSpawnCycle.Num())
				return;
			
			int UnitCost = LeftTeamSpawnCycle[SlotNum].GetDefaultObject()->GetCost();

			if (LeftBaseData.CurCost >= UnitCost)
			{

				if (LeftBaseData.UnitOnFieldData.Find(LeftTeamSpawnCycle[SlotNum].GetDefaultObject()->GetCharacterName()))
				{
					if (LeftBaseData.IsAutoPlayMode)
						return;
					TArray<AActor*> FoundActors;

					UGameplayStatics::GetAllActorsOfClass(GetWorld(), LeftTeamSpawnCycle[SlotNum], FoundActors);

					for (auto& Character : FoundActors)
					{
						if (auto* Unit = Cast<AC_CSCharacter>(Character))
						{
							if (Unit->GetTeamID() == 0 && !Unit->IsDead())
								if (auto* Interface = Cast<IC_CharacterInterface>(Unit))
									Interface->Respawn();
						}
					}
				}
				CostReduce(true, UnitCost);

				FTransform SpawnTransform;
				SpawnTransform.SetRotation(FRotator(0, 90, 0).Quaternion());
				SpawnTransform.SetLocation(Location);
				auto* Unit = Cast<AC_CSCharacter>(GetWorld()->SpawnActor(LeftTeamSpawnCycle[SlotNum], &SpawnTransform));
				Unit->SetTeamID(0);

				if (auto* Data = UnitBattleDatas.Find(Unit->GetStatus()->GetCharacterName()))
				{
					Unit->SetSPSkillCoolRate(Data->SPCoolRate);
					Unit->SetULTSkillCoolRate(Data->ULTCoolRate);
				}

				Datas.UnitOnFieldData.Emplace(Unit->GetStatus()->GetCharacterName());
				LeftBaseData.UnitOnFieldData.Emplace(Unit->GetStatus()->GetCharacterName());
				
				if (LeftTeamSpawnCycle.Num() > 4)
				{
					LeftTeamSpawnCycle.Swap(SlotNum, 5);

					for (int i = 5; i < LeftTeamSpawnCycle.Num() - 1; i++)
						LeftTeamSpawnCycle.Swap(i, i + 1);

				Datas.UnitImage.EmplaceAt(SlotNum, LeftTeamSpawnCycle[SlotNum].GetDefaultObject()->GetCharacterButtonImage());
				Datas.ButtonUnitName.EmplaceAt(SlotNum, LeftTeamSpawnCycle[SlotNum].GetDefaultObject()->GetStatus()->GetCharacterName());
				}

				UIDataUpdated.ExecuteIfBound();
			}
		}
	}
	else
	{
		if (SlotNum >= RightTeamSpawnCycle.Num())
			return;
		int UnitCost = RightTeamSpawnCycle[SlotNum].GetDefaultObject()->GetCost();

		if (RightBaseData.CurCost >= UnitCost)
		{

			if (RightBaseData.UnitOnFieldData.Find(RightTeamSpawnCycle[SlotNum].GetDefaultObject()->GetCharacterName()))
			{
				if (RightBaseData.IsAutoPlayMode)
					return;

				TArray<AActor*> FoundActors;

				UGameplayStatics::GetAllActorsOfClass(GetWorld(), RightTeamSpawnCycle[SlotNum], FoundActors);

				for (auto& Character : FoundActors)
				{
					if (auto* Unit = Cast<AC_CSCharacter>(Character))
					{
						if (Unit->GetTeamID() == 0 && !Unit->IsDead())
							if (auto* Interface = Cast<IC_CharacterInterface>(Unit))
								Interface->Respawn();
					}
				}
			}
			CostReduce(false, UnitCost);

			FTransform SpawnTransform;
			SpawnTransform.SetRotation(FRotator(0, -90, 0).Quaternion());
			SpawnTransform.SetLocation(Location);
			auto* Unit = Cast<AC_CSCharacter>(GetWorld()->SpawnActor(RightTeamSpawnCycle[SlotNum], &SpawnTransform));
			Unit->SetTeamID(1);

			if (auto* Data = UnitBattleDatas.Find(Unit->GetStatus()->GetCharacterName()))
			{
				Unit->SetSPSkillCoolRate(Data->SPCoolRate);
				Unit->SetULTSkillCoolRate(Data->ULTCoolRate);
			}

			RightBaseData.UnitOnFieldData.Emplace(Unit->GetStatus()->GetCharacterName());

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
	FName DiedUnitName = DiedUnit->GetCharacterName();
	FUnitBattleData NewData;
	NewData.SPCoolRate = SPCoolRate;
	NewData.ULTCoolRate = ULTCoolRate;
	UnitBattleDatas.Emplace(DiedUnitName, NewData);

	if (DiedUnit->GetTeamID() == 0)
	{
		LeftBaseData.UnitOnFieldData.Remove(DiedUnit->GetCharacterName());
	}
	else
	{
		RightBaseData.UnitOnFieldData.Remove(DiedUnit->GetCharacterName());
	}



	if (DiedUnit->GetTeamID() == 0)
	{
		Datas.UnitOnFieldData.Remove(DiedUnitName);
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

	if (Field)
		Map = Cast<AC_Field>(GetWorld()->SpawnActor(Field));
	
	for (size_t i = 0; i < 2; i++)
	{
		Map->AccessBaseData((bool)i)->UpdateHP.AddUFunction(this, "CheckHP");

		CameraMovablePosY[i] = Map->AccessBaseData((bool)i)->GetActorLocation().Y;
		AutoSpawning[i].BindUFunction(Map->AccessBaseData((bool)i), "SpawnCharacter");
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

	InitBaseData();
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
		Datas.CurCost = LeftBaseData.CurCost;
	}
	else
	{
		RightBaseData.CurCost -= Cost;
		RightBaseData.IsCostFull = false;
	}

	UIDataUpdated.ExecuteIfBound();
}

void AC_GameModeBase::AutoPlay(const bool& IsLeft)
{
	if (LeftBaseData.IsAutoPlayMode && IsLeft)
	{
		if (LeftBaseData.AutoSpawnNum <= LeftBaseData.MaxUnitCount)
		{
			AutoSpawning[1].ExecuteIfBound(FVector::ZeroVector,
				LeftBaseData.AutoSpawnNum, true);

			LeftBaseData.AutoSpawnNum++;

			if (LeftBaseData.AutoSpawnNum >= LeftBaseData.MaxUnitCount)
				LeftBaseData.AutoSpawnNum = 0;

		}
	}
	
	if (RightBaseData.IsAutoPlayMode && !IsLeft)
	{
		if (RightBaseData.AutoSpawnNum <= RightBaseData.MaxUnitCount)
		{
			AutoSpawning[0].ExecuteIfBound(FVector::ZeroVector,
				RightBaseData.AutoSpawnNum, false);

			RightBaseData.AutoSpawnNum++;

			if (RightBaseData.AutoSpawnNum >= RightBaseData.MaxUnitCount)
				RightBaseData.AutoSpawnNum = 0;
		}
	}

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
		
		if (Datas.CurCost - (int)Datas.CurCost < 0.01f)
		{
			UIDataUpdated.ExecuteIfBound();
		}
	}

	static float AutoTimer = 0.0f;

	AutoTimer += DeltaTime;

	if (AutoTimer >= 0.1f)
	{
		AutoPlay(false);
		AutoPlay(true);

		AutoTimer = 0.0f;
	}
}

void AC_GameModeBase::InitBaseData()
{
	Datas.CostRegenRatio = CostRegenRatio;

	LeftBaseData.CurCost = MaxCost;
	RightBaseData.CurCost = MaxCost;
	
	Datas.CurCost = LeftBaseData.CurCost;

	LeftBaseData.MaxUnitCount = LeftTeamSpawnCycle.Num();
	RightBaseData.MaxUnitCount = RightTeamSpawnCycle.Num();

	//AI
	Map->AccessBaseData(0)->SetAutoPlay(true);

	LeftBaseData.IsAutoPlayMode = Map->AccessBaseData(1)->GetAutoPlay();
	RightBaseData.IsAutoPlayMode = Map->AccessBaseData(0)->GetAutoPlay();

	RestoreCost(0.0f);
	CheckHP();
}

