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
		float IncreaseAttackRate = 0.5f;
	/*UFUNCTION()
		virtual void OnNotifyStart(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	UFUNCTION()
		virtual void OnSkillMontageEnded(UAnimMontage* Montage, bool bInterrupted);*/
};
