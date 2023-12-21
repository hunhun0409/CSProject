// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/C_ActiveSkill.h"
#include "C_SwordManSP.generated.h"

/**
 * 
 */
UCLASS()
class CSPROJECT_API AC_SwordManSP : public AC_ActiveSkill
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

protected:
	void ApplyEffectToPawn(APawn* InPawn) override;
	void BeginAction() override;
	void EndAction() override;
	void Activate() override;
	void Deactivate() override;

	void StartCooldown() override;
	void RestartCooldown() override;


private:
	UPROPERTY(EditDefaultsOnly)
		float IncreaseAttackSpeedRate = 0.5f;
	UPROPERTY(EditDefaultsOnly)
		float IncreaseAttackDamageRate = 1.0f;
	UPROPERTY(EditDefaultsOnly)
		float SkillDuration = 12.0f;

	FTimerHandle Timer;
	/*UFUNCTION()
		virtual void OnNotifyStart(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	UFUNCTION()
		virtual void OnSkillMontageEnded(UAnimMontage* Montage, bool bInterrupted);*/
};
