// Copyright Epic Games, Inc. All Rights Reserved.

#include "CSProjectGameMode.h"
#include "CSProjectPlayerController.h"
#include "CSProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACSProjectGameMode::ACSProjectGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ACSProjectPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}