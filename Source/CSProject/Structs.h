#pragma once

struct FBasicData
{
	float CurCost;
	float CurHP;
	float MaxHP;
	bool IsCostFull;
	float YPosition;
};

struct FUIData
{
	float CurCost;
	float PlayerBaseHP;
	float EnemyBaseHP;
	float CostRegenRatio;
};