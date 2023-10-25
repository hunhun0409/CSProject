// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/C_DamageHandleInterface.h"
#include "C_Base.generated.h"

UCLASS(Abstract)
class CSPROJECT_API AC_Base : public AActor, public IC_DamageHandleInterface
{
	GENERATED_BODY()
		//Ÿ���Ӽ�
	
public:	
	// Sets default values for this actor's properties
	AC_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float CalculateDamage(float Damage, AActor* DamageCauser) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TMulticastDelegate<void()> UpdateHP;

	const float& GetHP() { return CurHP; }
	const float& GetMaxHP() { return MaxHP; }

protected:
	UFUNCTION(BlueprintCallable)
		void DamagedHP(const int& InDamage);

protected:
	UPROPERTY(EditDefaultsOnly)
		float MaxHP;
	float CurHP;

	UPROPERTY(EditDefaultsOnly)
		float AttackRange;

	UPROPERTY(EditDefaultsOnly)
		float Damage;

	UPROPERTY(EditDefaultsOnly)
		class UAIPerceptionComponent* AIPerception;
};
