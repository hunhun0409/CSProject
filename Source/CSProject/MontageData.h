#pragma once

#include "CoreMinimal.h"
#include "Enum/ECharacterState.h"
#include "Engine/DataTable.h"
#include "MontageData.generated.h"

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) ECharacterState CharacterState;
	UPROPERTY(EditAnywhere) int32 Key;
	UPROPERTY(EditAnywhere) class UAnimMontage* Montage;
	UPROPERTY(EditAnywhere) float PlayRate = 1.0f;
	UPROPERTY(EditAnywhere) FName Section;
};