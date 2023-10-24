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

public:
	AC_Controller();

protected:
	void OnConstruction(const FTransform& Transform) override;

	void BeginPlay() override;

	void Tick(const float DeltaTime) override;


	UFUNCTION()
		const FHitResult CurserOnGroundHitResult();

private:
	void SetupInputComponent() override;

private:
	void BeginLB();
	void EndLB();
	void BeginRB();
	void EndRB();
	void Key1B();
	void Key2B();
	void Key3B();
	void Key4B();


	void Wheel(const float Value);
	void MoveRight(const float Value);

private:
	bool MouseRBPressed = false;
};
