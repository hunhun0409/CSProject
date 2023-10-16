// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_Controller.generated.h"

/**
 * 
 */
UCLASS()
class CSPROJECT_API AC_Controller : public APlayerController
{
	GENERATED_BODY()

private:
	void SetupInputComponent() override;

private:
	void BeginLB();
	void EndLB();
	void BeginRB();
	void EndRB();
	void Wheel(const float Value);

};
