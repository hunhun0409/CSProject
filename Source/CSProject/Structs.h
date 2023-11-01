#pragma once
#include "CoreMinimal.h"
#include "Structs.generated.h"

struct FBasicData
{
	float CurCost;
	float CurHP;
	float MaxHP;
	bool IsCostFull = true;
	float YPosition;
	bool IsAutoPlayMode = false;
	int AutoSpawnNum = 0;
	int MaxUnitCount = 0;
	TSet<FName> UnitOnFieldData;
};

USTRUCT()
struct FUIData
{
	GENERATED_BODY()

	float CurCost;
	float PlayerBaseHP;
	float EnemyBaseHP;
	float CostRegenRatio;
	TArray<UTexture2D*> UnitImage;
	TArray<FName> ButtonUnitName;
	TSet<FName> UnitOnFieldData;
};

struct FUnitBattleData
{
	float SPCoolRate;
	float ULTCoolRate;
};