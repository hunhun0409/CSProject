// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "C_DamageHandleInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UC_DamageHandleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CSPROJECT_API IC_DamageHandleInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Attack()	PURE_VIRTUAL(IC_CharacterInterface::Attack, return;)
};