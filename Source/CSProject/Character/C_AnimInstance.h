// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CSPROJECT_API UC_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	void NativeUpdateAnimation(float const DeltaSeconds) override;

	FORCEINLINE void SetWeaponClass(TSubclassOf<class AC_Weapon> InClass) { WeaponClass = InClass; }

protected:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float Speed;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AC_Weapon> WeaponClass;
};
