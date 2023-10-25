#pragma once

#include "CoreMinimal.h"

#include "Enum/ECharacterRank.h"
#include "Enum/ECharacterType.h"
#include "Enum/EClassType.h"
#include "Enum/EMoveType.h"
#include "Enum/EAttackType.h"

#include "Engine/DataTable.h"
#include "StatusData.generated.h"

USTRUCT(BlueprintType)
struct FStatusData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) FName Name;
	UPROPERTY(EditAnywhere) uint8 Cost;
	UPROPERTY(EditAnywhere) ECharacterRank CharacterRank;
	UPROPERTY(EditAnywhere) ECharacterType CharacterType;
	UPROPERTY(EditAnywhere) EClassType ClassType;
	UPROPERTY(EditAnywhere) EMoveType MoveType;
	UPROPERTY(EditAnywhere) EAttackType AttackType;
	UPROPERTY(EditAnywhere) float Health;
	UPROPERTY(EditAnywhere) float Attack;
	UPROPERTY(EditAnywhere) float Defense;
	UPROPERTY(EditAnywhere) float Critk;
	UPROPERTY(EditAnywhere) float CritDamage;
	UPROPERTY(EditAnywhere) float Hit;
	UPROPERTY(EditAnywhere) float Eva;
	UPROPERTY(EditAnywhere) float AttackRate;
	UPROPERTY(EditAnywhere) float MaxSightRange;
	UPROPERTY(EditAnywhere) float MaxAttackRange;
	UPROPERTY(EditAnywhere) float MovementSpeed;
};
