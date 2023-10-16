// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BaseSpawner.h"
#include "C_Base.h"

// Sets default values
AC_BaseSpawner::AC_BaseSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseVisualSite = CreateDefaultSubobject<UStaticMeshComponent>("BaseVisualSite");
	SetRootComponent(BaseVisualSite);
}

void AC_BaseSpawner::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

// Called when the game starts or when spawned
void AC_BaseSpawner::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void AC_BaseSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_BaseSpawner::SpawnBase()
{
	if (BaseType)
	{
		FTransform SpawnTransform = GetActorTransform();
		Base = Cast<AC_Base>(GetWorld()->SpawnActor(BaseType, &SpawnTransform));
		

	}
}

AC_Base* AC_BaseSpawner::GetBase()
{
	if(Base != nullptr)
		return Base;
	else
	{
		SpawnBase();
		return Base;
	}
}

