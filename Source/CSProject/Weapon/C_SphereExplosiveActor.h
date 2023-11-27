// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_SphereExplosiveActor.generated.h"

UCLASS()
class CSPROJECT_API AC_SphereExplosiveActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AC_SphereExplosiveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly)
		class USphereComponent* Collider;

	UPROPERTY(EditDefaultsOnly)
		bool IsHitBase = false;

};
