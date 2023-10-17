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


protected:
	void ApplyEffectToPawn(APawn* InPawn) override;
	void BeginAction() override;
	void EndAction() override;
	void Activate() override;
	void Deactivate() override;

	void RestartCooldown() override;
	FORCEINLINE void AddCooldown() { CurCooldown += AddInterval; }

private:
	float CurCooldown = 0;
	float AddInterval = 0.1f;
};
