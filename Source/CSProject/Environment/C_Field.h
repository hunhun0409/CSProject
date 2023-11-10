// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Field.generated.h"

class AC_Base_V2;
UCLASS(Abstract)
class CSPROJECT_API AC_Field : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Field();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AC_Base_V2* AccessBaseData(const bool& isLeftBase);

	void SetVisiblePlayerSpawnArea(const bool& IsVisible);
	class UBoxComponent* GetSpawnCollider(const bool& IsLeft);

protected:
	UFUNCTION()
		void UpdateSpawnCollider();

protected:
	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* Field;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AC_Base_V2> LeftBaseType;
	UPROPERTY()
		class AC_Base_V2* LeftBase;
	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* LeftSpawnCollider;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AC_Base_V2> RightBaseType;
	UPROPERTY()
		class AC_Base_V2* RightBase;
	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* RightSpawnCollider;

private:
	FVector2D ColliderScaleYOffset;



};
