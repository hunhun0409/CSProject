// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GameModeBase.h"
#include "Components/BoxComponent.h"
#include "C_Field.h"
#include "C_Base.h"

AC_GameModeBase::AC_GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC_GameModeBase::SpawnCharacter(const FVector& Location, const int& SlotNum)
{
	//Location이 Field의 Collider 내부인지 체크
	//맞으면 Cost 감소
	//필드에 소환된 유닛 그룹을 만들고 확인, 이미 소환된 상태면 같은 유닛을 파괴 
	// 해당 그룹은 Widget으로 정보를 보내 파괴될때까지 Tint와 Grayscale을 설정.
	// 위 정보는 FUIData를 수정하기.
	//TeamOrganization에서 1~4 번째 소환, 해당 유닛을 5번과 바꾸고, 5 6 \ 6 7 \ 7 8 스왑.
	//스왑 후 해당 유닛의 UTexture2D를 가져와 해당 UImage로 넣기
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

