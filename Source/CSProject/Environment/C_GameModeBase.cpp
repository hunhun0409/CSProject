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
		//Location�� Field�� Collider �������� üũ
		if (Map->GetSpawnCollider(true)->Bounds.GetBox().IsInside(Location))
		{
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(Location);
			auto* Unit = Cast<AC_CSCharacter>(GetWorld()->SpawnActor(LeftTeamSpawnCycle[SlotNum], &SpawnTransform));
			// �� �Ҽ� ����.(���� ����!)
			//�ڽ�Ʈ �޾ƿ���(���ݾ�!) �װ��� ��´�.


			if (LeftTeamSpawnCycle.Num() > 4)
			{
				TSubclassOf<AC_CSCharacter> TempClassData = LeftTeamSpawnCycle[SlotNum];
				LeftTeamSpawnCycle[SlotNum] = LeftTeamSpawnCycle[5];
				LeftTeamSpawnCycle[5] = TempClassData;

				for (int i = 5; i < LeftTeamSpawnCycle.Num() - 1; i++)
				{
					TempClassData = LeftTeamSpawnCycle[i];
					LeftTeamSpawnCycle[i] = LeftTeamSpawnCycle[i + 1];
					LeftTeamSpawnCycle[i + 1] = TempClassData;
				}
			}

			// �ش� ��ȣ�� Texture2D�� Player�� ������ ������ ����.
			// ������ ���� ǥ��? ������ ��ų�������� ����� �ʿ䰡 �ִ�.
			// ������ ������ ������ ���� Material�� GrayScale ����
		}
	}
	else
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		auto* Unit = Cast<AC_CSCharacter>(GetWorld()->SpawnActor(RightTeamSpawnCycle[SlotNum], &SpawnTransform));
		// �� �Ҽ� ����.(���� ����!)
		//�ڽ�Ʈ �޾ƿ���(���ݾ�!) �װ��� ��´�.


		if (RightTeamSpawnCycle.Num() > 4)
		{
			TSubclassOf<AC_CSCharacter> TempClassData = RightTeamSpawnCycle[SlotNum];
			RightTeamSpawnCycle[SlotNum] = RightTeamSpawnCycle[5];
			RightTeamSpawnCycle[5] = TempClassData;

			for (int i = 5; i < RightTeamSpawnCycle.Num() - 1; i++)
			{
				TempClassData = RightTeamSpawnCycle[i];
				RightTeamSpawnCycle[i] = RightTeamSpawnCycle[i + 1];
				RightTeamSpawnCycle[i + 1] = TempClassData;
			}
		}
	}

	//������ Cost ����
	//�ʵ忡 ��ȯ�� ���� �׷��� ����� Ȯ��, �̹� ��ȯ�� ���¸� ���� ������ �ı� 
	// �ش� �׷��� Widget���� ������ ���� �ı��ɶ����� Tint�� Grayscale�� ����.
	// �� ������ FUIData�� �����ϱ�.
	//TeamOrganization���� 1~4 ��° ��ȯ, �ش� ������ 5���� �ٲٰ�, 5 6 \ 6 7 \ 7 8 ����.
	//���� �� �ش� ������ UTexture2D�� ������ �ش� UImage�� �ֱ�
}

void AC_GameModeBase::SetVisiblePlayerSpawnableArea(const bool& IsVisible)
{
	Map->SetVisiblePlayerSpawnArea(IsVisible);
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

	RestoreCost(0.0f);
	CheckHP();

	for (int i = 0; i < LeftTeamOrganization.Num(); i++)
	{
		LeftTeamSpawnCycle.Add(LeftTeamOrganization[i]);
	}
	for (int i = 0; i < RightTeamOrganization.Num(); i++)
	{
		RightTeamSpawnCycle.Add(RightTeamOrganization[i]);
	}

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

