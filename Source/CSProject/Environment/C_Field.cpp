// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Field.h"
#include "Components/BoxComponent.h"
#include "C_Base.h"
#include "C_GameModeBase.h"

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
	LeftBase->SetTeamID(0);

	FTransform RBTransform = GetActorTransform();
	RBTransform.SetLocation(RBTransform.GetLocation() + RightSpawnCollider->GetComponentLocation());
	RBTransform.SetScale3D(FVector(3, 3, 3));
	RightBase = Cast<AC_Base>(GetWorld()->SpawnActor(RightBaseType, &RBTransform));
	RightBase->UpdateHP.AddUFunction(this, "UpdateSpawnCollider");
	ColliderScaleYOffset.Y = RightSpawnCollider->GetRelativeScale3D().Y;
	RightBase->SetTeamID(1);

	UpdateSpawnCollider();

	if (auto* GameMode = Cast<AC_GameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->SetField(this);
	}
}

// Called every frame
void AC_Field::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AC_Base* AC_Field::AccessBaseData(const bool& isLeftBase)
{
	if (isLeftBase)
		return LeftBase;
	else
		return RightBase;
}

void AC_Field::SetVisiblePlayerSpawnArea(const bool& IsVisible)
{
	LeftSpawnCollider->SetHiddenInGame(!IsVisible);
}

UBoxComponent* AC_Field::GetSpawnCollider(const bool& IsLeft)
{
	if (IsLeft)
		return LeftSpawnCollider;
	else
		return RightSpawnCollider;
}

void AC_Field::UpdateSpawnCollider()
{
	FVector LeftColliderOffset = LeftSpawnCollider->GetRelativeScale3D();
	LeftColliderOffset.Y = (1 + (1 - RightBase->GetStatus()->GetCurHealth() / RightBase->GetStatus()->GetMaxHealth())) * ColliderScaleYOffset.X;

	LeftSpawnCollider->SetRelativeScale3D(LeftColliderOffset);
	LeftSpawnCollider->SetWorldLocation(FVector(0, LeftBase->GetActorLocation().Y + LeftSpawnCollider->GetScaledBoxExtent().Y, 0));
	
	FVector RightColliderOffset = RightSpawnCollider->GetRelativeScale3D();
	RightColliderOffset.Y = (1 + (1 - LeftBase->GetStatus()->GetCurHealth() / LeftBase->GetStatus()->GetMaxHealth())) * ColliderScaleYOffset.Y;

	RightSpawnCollider->SetRelativeScale3D(RightColliderOffset);
	RightSpawnCollider->SetWorldLocation(FVector(0, RightBase->GetActorLocation().Y - RightSpawnCollider->GetScaledBoxExtent().Y, 0));

}

