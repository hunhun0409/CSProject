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
	LeftBase = Cast<AC_Base>(GetWorld()->SpawnActor(LeftBaseType, &LBTransform));
	LeftBase->UpdateHP.AddUFunction(this, "UpdateSpawnCollider");
	ColliderScaleYOffset.X = LeftSpawnCollider->GetRelativeScale3D().Y;

	FTransform RBTransform = GetActorTransform();
	RBTransform.SetLocation(RBTransform.GetLocation() + RightSpawnCollider->GetComponentLocation());
	RightBase = Cast<AC_Base>(GetWorld()->SpawnActor(RightBaseType, &RBTransform));
	RightBase->UpdateHP.AddUFunction(this, "UpdateSpawnCollider");
	ColliderScaleYOffset.Y = RightSpawnCollider->GetRelativeScale3D().Y;

	UpdateSpawnCollider();
}

// Called every frame
void AC_Field::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AC_Base* AC_Field::AccessBaseData(bool isLeftBase)
{
	if (isLeftBase)
		return LeftBase;
	else
		return RightBase;
}

void AC_Field::UpdateSpawnCollider()
{
	FVector LeftColliderOffset = LeftSpawnCollider->GetRelativeScale3D();
	LeftColliderOffset.Y = (1 + (1 - RightBase->GetHP() / RightBase->GetMaxHP())) * ColliderScaleYOffset.X;

	LeftSpawnCollider->SetRelativeScale3D(LeftColliderOffset);
	LeftSpawnCollider->SetWorldLocation(FVector(0, LeftBase->GetActorLocation().Y + LeftSpawnCollider->GetScaledBoxExtent().Y, 0));
	
	FVector RightColliderOffset = RightSpawnCollider->GetRelativeScale3D();
	RightColliderOffset.Y = (1 + (1 - LeftBase->GetHP() / LeftBase->GetMaxHP())) * ColliderScaleYOffset.Y;

	RightSpawnCollider->SetRelativeScale3D(RightColliderOffset);
	RightSpawnCollider->SetWorldLocation(FVector(0, RightBase->GetActorLocation().Y - RightSpawnCollider->GetScaledBoxExtent().Y, 0));

}

