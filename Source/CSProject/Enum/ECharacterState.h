#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle			UMETA(DisplayName = "Idle"),
	Attacking		UMETA(DisplayName = "Attacking"),
	SP_Skilling		UMETA(DisplayName = "SP_Skilling"),
	ULT_Skilling		UMETA(DisplayName = "ULT_Skilling"),
	Died			UMETA(DisplayName = "Died"),
};

