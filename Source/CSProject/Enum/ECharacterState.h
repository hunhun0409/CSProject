#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle			UMETA(DisplayName = "Idle"),
	Attacking		UMETA(DisplayName = "Attacking"),
	Skilling		UMETA(DisplayName = "Skilling"),
	Died			UMETA(DisplayName = "Died"),
};

