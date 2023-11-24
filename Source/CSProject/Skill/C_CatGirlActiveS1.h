// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/C_ActiveSkill.h"
#include "C_CatGirlActiveS1.generated.h"

/**
 * 
 */
UCLASS()
class CSPROJECT_API AC_CatGirlActiveS1 : public AC_ActiveSkill
{
	GENERATED_BODY()
	

public:
	AC_CatGirlActiveS1();

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
	
	/*UFUNCTION()
		virtual void OnNotifyStart(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	UFUNCTION()
		virtual void OnSkillMontageEnded(UAnimMontage* Montage, bool bInterrupted);*/
};
