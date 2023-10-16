// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Field.h"
#include "Components/BoxComponent.h"
#include "C_Base.h"

// Sets default values
AC_Field::AC_Field()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Field = CreateDefaultSubobject<UStaticMeshComponent>("Field");
	SetRootComponent(Field);

	LeftSpawnCollider = CreateDefaultSubobject<UBoxComponent>("LeftSpawnCol");
	LeftSpawnCollider->SetupAttachment(RootComponent);

	RightSpawnCollider = CreateDefaultSubobject<UBoxComponent>("RightSpawnCol");
	RightSpawnCollider->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AC_Field::BeginPlay()
{
	Super::BeginPlay();
	FTransform LBTransform = GetActorTransform();
	LBTransform.SetLocation(LBTransform.GetLocation() + LeftSpawnCollider->GetComponentLocation());
	GetWorld()->SpawnActor(LeftBase, &LBTransform);

	FTransform RBTransform = GetActorTransform();
	RBTransform.SetLocation(RBTransform.GetLocation() + LeftSpawnCollider->GetComponentLocation());
	GetWorld()->SpawnActor(RightBase, &RBTransform);
}

// Called every frame
void AC_Field::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
