// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Controller.h"
#include "C_ControllerInterface.h"

AC_Controller::AC_Controller()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = false;

}

void AC_Controller::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MouseRBPressed)
	{
		FVector2D MouseDelta;
		GetInputMouseDelta(MouseDelta.X, MouseDelta.Y);
		Cast<IC_ControllerInterface>(GetPawn())->MouseDelta(MouseDelta);
	}
	{
		FVector2D MousePos;
		GetMousePosition(MousePos.X, MousePos.Y);
		Cast<IC_ControllerInterface>(GetPawn())->MousePos(MousePos);
	}
	
}

void AC_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MouseLB", IE_Pressed, this, &ThisClass::BeginLB);
	InputComponent->BindAction("MouseLB", IE_Released, this, &ThisClass::EndLB);

	InputComponent->BindAction("MouseRB", IE_Pressed, this, &ThisClass::BeginRB);
	InputComponent->BindAction("MouseRB", IE_Released, this, &ThisClass::EndRB);

	InputComponent->BindAction("Key1", IE_Pressed, this, &ThisClass::Key1B);
	InputComponent->BindAction("Key2", IE_Pressed, this, &ThisClass::Key2B);
	InputComponent->BindAction("Key3", IE_Pressed, this, &ThisClass::Key3B);
	InputComponent->BindAction("Key4", IE_Pressed, this, &ThisClass::Key4B);


	InputComponent->BindAxis("MouseWheel", this, &ThisClass::Wheel);
	InputComponent->BindAxis("MoveForward", this, &ThisClass::Wheel);
	InputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);

}

void AC_Controller::BeginLB()
{
	Cast<IC_ControllerInterface>(GetPawn())->MouseLBPressing(true);
}

void AC_Controller::EndLB()
{
	Cast<IC_ControllerInterface>(GetPawn())->MouseLBPressing(false);
}

void AC_Controller::BeginRB()
{
	MouseRBPressed = true;
	Cast<IC_ControllerInterface>(GetPawn())->MouseRBPressing(true);
}

void AC_Controller::EndRB()
{
	MouseRBPressed = false;
	Cast<IC_ControllerInterface>(GetPawn())->MouseRBPressing(false);
}

void AC_Controller::Key1B()
{
	Cast<IC_ControllerInterface>(GetPawn())->KeyNumPress(0);

}

void AC_Controller::Key2B()
{
	Cast<IC_ControllerInterface>(GetPawn())->KeyNumPress(1);

}

void AC_Controller::Key3B()
{
	Cast<IC_ControllerInterface>(GetPawn())->KeyNumPress(2);

}

void AC_Controller::Key4B()
{
	Cast<IC_ControllerInterface>(GetPawn())->KeyNumPress(3);

}

void AC_Controller::Wheel(const float Value)
{
	Cast<IC_ControllerInterface>(GetPawn())->Zoom(Value);

}

void AC_Controller::MoveRight(const float Value)
{
	Cast<IC_ControllerInterface>(GetPawn())->KeyBoardCameraMove(Value);

}
