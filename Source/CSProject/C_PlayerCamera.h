// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C_ControllerInterface.h"
#include "C_PlayerCamera.generated.h"

UCLASS(Abstract)
class CSPROJECT_API AC_PlayerCamera : public APawn, public IC_ControllerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AC_PlayerCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginCameraMove() override;
	virtual void EndCameraMove() override;
	virtual void BeginCharacterSelect() override;
	virtual void EndCharacterSelect() override;
	virtual void Zoom(const float Value) override;

protected:
	UPROPERTY(EditDefaultsOnly)
		class USpringArmComponent* SpringArm;
	float NewSocketOffsetZ;

	UPROPERTY(EditDefaultsOnly)
		class UCameraComponent* Camera;
	float NewFieldOfView;

	UPROPERTY(EditDefaultsOnly)
		class UFloatingPawnMovement* Movement;

	UPROPERTY(EditDefaultsOnly)
		class UCurveVector* ZoomCurve;

private:
	float CameraMovement;

	float ZoomTime = 0.0f;

	float ZoomRatio = 1.0f;
	bool ControlCamera = false;

};
