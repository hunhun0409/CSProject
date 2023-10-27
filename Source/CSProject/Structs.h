#pragma once
#include "CoreMinimal.h"
#include "Structs.generated.h"

struct FBasicData
{
	float CurCost;
	float CurHP;
	float MaxHP;
	bool IsCostFull;
	float YPosition;
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
	TMap<FName, bool> UnitOnFieldData;

};

struct FUnitBattleData
{
	float SPCoolRate;
	float ULTCoolRate;
};