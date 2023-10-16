// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GameModeBase.h"
#include "Components/BoxComponent.h"

#include "C_BaseSpawner.h"
#include "C_Base.h"

AC_GameModeBase::AC_GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Field = CreateDefaultSubobject<UStaticMeshComponent>("Field");
	SetRootComponent(Field);

	LeftSpawnCollider = CreateDefaultSubobject<UBoxComponent>("LeftSpawnBox");
	LeftSpawnCollider->SetupAttachment(RootComponent);

	RightSpawnCollider = CreateDefaultSubobject<UBoxComponent>("RightSpawnBox");
	RightSpawnCollider->SetupAttachment(RootComponent);


}

void AC_GameModeBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void AC_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

}

void AC_GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
