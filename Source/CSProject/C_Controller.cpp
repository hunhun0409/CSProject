// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Controller.h"
#include "C_ControllerInterface.h"

void AC_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MouseLB", IE_Pressed, this, &ThisClass::BeginLB);
	InputComponent->BindAction("MouseLB", IE_Released, this, &ThisClass::EndLB);

	InputComponent->BindAction("MouseRB", IE_Pressed, this, &ThisClass::BeginRB);
	InputComponent->BindAction("MouseRB", IE_Released, this, &ThisClass::EndRB);

	InputComponent->BindAxis("MouseWheel", this, &ThisClass::Wheel);

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
	Cast<IC_ControllerInterface>(GetPawn())->BeginCameraMove();

}

void AC_Controller::EndRB()
{
	Cast<IC_ControllerInterface>(GetPawn())->EndCameraMove();
	
}

void AC_Controller::Wheel(const float Value)
{
	Cast<IC_ControllerInterface>(GetPawn())->Zoom(Value);

}
