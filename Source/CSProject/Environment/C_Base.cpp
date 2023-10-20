// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Base.h"
#include "Perception/AIPerceptionComponent.h"

// Sets default values
AC_Base::AC_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");

}

// Called when the game starts or when spawned
void AC_Base::BeginPlay()
{
	Super::BeginPlay();
	
	CurHP = MaxHP;

}

// Called every frame
void AC_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Base::DamagedHP(const int& InDamage)
{
	CurHP -= InDamage;

	UpdateHP.Broadcast();

}

