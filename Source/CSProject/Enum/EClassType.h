#pragma once

UENUM(BlueprintType)
enum class EClassType : uint8
{
	Defender		UMETA(DisplayName = "Defender"),
	Striker			UMETA(DisplayName = "Striker"),
	Ranger			UMETA(DisplayName = "Ranger"),
	Sniper			UMETA(DisplayName = "Sniper"),
	Supporter		UMETA(DisplayName = "Supporter"),
	Tower			UMETA(DisplayName = "Tower"),
	Seige			UMETA(DisplayName = "Seige"),
};