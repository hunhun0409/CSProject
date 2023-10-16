// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/C_CSCharacter.h"

// Sets default values
AC_CSCharacter::AC_CSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_CSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_CSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_CSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

