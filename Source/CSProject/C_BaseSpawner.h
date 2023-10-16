// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_BaseSpawner.generated.h"

class AC_Base;
UCLASS()
class CSPROJECT_API AC_BaseSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_BaseSpawner();

protected:
	virtual void OnConstruction(const FTransform &Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnBase();

	AC_Base* GetBase();

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AC_Base> BaseType;

	UPROPERTY(EditDefaultsOnly)
		class AC_Base* Base;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* BaseVisualSite;

};
