#pragma once

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	None		UMETA(DisplayName = "None"),
	Passive		UMETA(DisplayName = "Passive"),
	Special		UMETA(DisplayName = "Special"),
	Ultimate	UMETA(DisplayName = "Ultimate"),
	Leader		UMETA(DisplayName = "Leader")
};