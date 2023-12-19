// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SphereExplosiveActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Environment/C_Base_V2.h"
#include "Character/C_CSCharacter.h"

// Sets default values
AC_SphereExplosiveActor::AC_SphereExplosiveActor()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	SetRootComponent(Collider);

}

// Called when the game starts or when spawned
void AC_SphereExplosiveActor::BeginPlay()
{
	Super::BeginPlay();
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AC_SphereExplosiveActor::OnBeginOverlap);
}

void AC_SphereExplosiveActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void AC_SphereExplosiveActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*if (auto* Target = Cast<AC_CSCharacter>(OtherActor))
	{

	}
	else if (IsHitBase)
	{
		if (auto* Target = Cast<AC_Base_V2>(OtherActor))
		{

		}
	}*/
}

// Called every frame
void AC_SphereExplosiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
