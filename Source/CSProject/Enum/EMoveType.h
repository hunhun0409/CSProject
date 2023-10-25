#pragma once

UENUM(BlueprintType)
enum class EMoveType : uint8
{
	Ground		UMETA(DisplayName = "Ground"),
	Air			UMETA(DisplayName = "Air"),
	AllAround	UMETA(DisplayName = "AllAround"),
};

