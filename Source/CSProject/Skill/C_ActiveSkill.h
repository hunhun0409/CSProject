// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/C_Skill.h"
#include "C_ActiveSkill.generated.h"

/**
 * 
 */
UCLASS()
class CSPROJECT_API AC_ActiveSkill : public AC_Skill
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
		float MaxCooldown;
	UPROPERTY(EditDefaultsOnly)
		float DamageCoefficience;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Montage")
		class UAnimMontage* SkillMontage;

public:
	AC_ActiveSkill();

protected:
	virtual void BeginPlay() override;

protected:
	void ApplyEffectToPawn(APawn* InPawn) override;
	void BeginAction() override;
	void EndAction() override;
	void Activate() override;
	void Deactivate() override;

	void RestartCooldown() override;

	UFUNCTION()
		virtual void OnNotifyStart(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	UFUNCTION()
		virtual void OnSkillMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AddCooldown();

public:
	bool CanActivate() override; 
	float GetSkillCoolDown() override; 

private:
	float CurCooldown = 0;
	float AddInterval = 0.1f;

	FTimerHandle Timer;
};
