// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/C_AnimInstance.h"

void UC_AnimInstance::NativeUpdateAnimation(float const DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (auto* const PawnOwner = TryGetPawnOwner())
	{
		FVector const Velocity = PawnOwner->GetVelocity();

		Speed = Velocity.Size2D();
	}
}
