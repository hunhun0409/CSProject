// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "C_ControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UC_ControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CSPROJECT_API IC_ControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void BeginCameraMove() PURE_VIRTUAL(IC_ControllerInterface::BeginCameraMove, return;)
	virtual void EndCameraMove() PURE_VIRTUAL(IC_ControllerInterface::EndCameraMove, return;)
	virtual void BeginCharacterSelect() PURE_VIRTUAL(IC_ControllerInterface::BeginCharacterSelect, return;)
	virtual void EndCharacterSelect() PURE_VIRTUAL(IC_ControllerInterface::EndCharacterSelect, return;)
	virtual void Zoom(const float Value) PURE_VIRTUAL(IC_ControllerInterface::Zoom, return;)
	virtual void KeyBoardCameraMove(const float Value) PURE_VIRTUAL(IC_ControllerInterface::KeyBoardCameraMove, return;)



};
