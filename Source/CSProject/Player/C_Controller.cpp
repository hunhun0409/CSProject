// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Controller.h"
#include "C_ControllerInterface.h"

AC_Controller::AC_Controller()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_Controller::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MouseRBPressed)
	{
		float DeltaX;
		float DeltaY;
		GetInputMouseDelta(DeltaX, DeltaY);
		Cast<IC_ControllerInterface>(GetPawn())->MouseDelta(DeltaX, DeltaY);
	}
}

void AC_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MouseLB", IE_Pressed, this, &ThisClass::BeginLB);
	InputComponent->BindAction("MouseLB", IE_Released, this, &ThisClass::EndLB);

	InputComponent->BindAction("MouseRB", IE_Pressed, this, &ThisClass::BeginRB);
	InputComponent->BindAction("MouseRB", IE_Released, this, &ThisClass::EndRB);

	InputComponent->BindAxis("MouseWheel", this, &ThisClass::Wheel);
	InputComponent->BindAxis("MoveForward", this, &ThisClass::Wheel);
	InputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);

}

void AC_Controller::BeginLB()
{
	Cast<IC_ControllerInterface>(GetPawn())->BeginCharacterSelect();

}

void AC_Controller::EndLB()
{
	Cast<IC_ControllerInterface>(GetPawn())->EndCharacterSelect();
}

void AC_Controller::BeginRB()
{
	MouseRBPressed = true;
}

void AC_Controller::EndRB()
{
	MouseRBPressed = false;
}

void AC_Controller::Wheel(const float Value)
{
	Cast<IC_ControllerInterface>(GetPawn())->Zoom(Value);

}

void AC_Controller::MoveRight(const float Value)
{
	Cast<IC_ControllerInterface>(GetPawn())->KeyBoardCameraMove(Value);

}
