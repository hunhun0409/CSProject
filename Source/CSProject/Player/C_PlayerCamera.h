// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C_ControllerInterface.h"
#include "Structs.h"
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

	TDelegate<FUIData()> GetUIData;
	TDelegate<void(FVector, int, bool)> SpawnOrder;
	TDelegate<void(bool)> ShowAreaOrder;

protected:
	UFUNCTION()
		void UpdateUIData();
	UFUNCTION()
		void Spawn(int SlotNum);
	UFUNCTION()
		void Preview(int SlotNum);
	UFUNCTION()
		void CancelSelect();
	UFUNCTION()
		void SpawnDamageHUD(const float& FinalDamage, const bool& bCrit, const bool& bEvade, const FVector& ActorLocation);

protected:
	virtual void Zoom(const float& Value) override;
	virtual void KeyBoardCameraMove(const float& Value) override;
	virtual void MouseDelta(const FVector2D& MouseDelta) override;
	virtual void MousePos(const FVector2D& MousePos) override;
	virtual void MouseLBPressing(const bool& IsPressing) override;
	virtual void MouseRBPressing(const bool& IsPressing) override;
	virtual void KeyNumPress(const int& KeyNum) override;

private:

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

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UC_UserWidget> UIWidgetClass;
	UPROPERTY()
		class UC_UserWidget* UIWidget;

private:
	FUIData Datas;

	FVector2D CameraMovableY;
	float CameraMovement;
	float ZoomTime = 0.0f;
	float ZoomRatio = 1.0f;

	bool ControlCamera = false;

	FVector SpawnLocation;
	int SelectedSlot;
	bool CalculatePreviewLoc = false;;

};
