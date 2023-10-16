#pragma once

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	Ground_Attack		UMETA(DisplayName = "Ground_Attack"),
	Air_Attack			UMETA(DisplayName = "Air_Attack"),
	AllAround_Attack	UMETA(DisplayName = "AllAround_Attack")
};

