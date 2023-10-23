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
	virtual void Zoom(const float& Value) PURE_VIRTUAL(IC_ControllerInterface::Zoom, return;)
	virtual void KeyBoardCameraMove(const float& Value) PURE_VIRTUAL(IC_ControllerInterface::KeyBoardCameraMove, return;)
	virtual void MouseDelta(const FVector2D& MouseDelta) PURE_VIRTUAL(IC_ControllerInterface::MouseDelta, return;)
	virtual void MousePos(const FVector2D& MousePos) PURE_VIRTUAL(IC_ControllerInterface::MousePos, return;)
	virtual void MouseLBPressing(const bool& IsPressing) PURE_VIRTUAL(IC_ControllerInterface::MouseLBPressing, return;)
	virtual void MouseRBPressing(const bool& IsPressing) PURE_VIRTUAL(IC_ControllerInterface::MouseRBPressing, return;)
	virtual void KeyNumPress(const int& KeyNum) PURE_VIRTUAL(IC_ControllerInterface::KeyNumPress, return;)



};
