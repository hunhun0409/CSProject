// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "C_SkillInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UC_SkillInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CSPROJECT_API IC_SkillInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void ApplyEffectToPawn(APawn* InPawn) PURE_VIRTUAL(IC_SkillInterface::ApplyEffectToPawn, return;)
		virtual void BeginAction() PURE_VIRTUAL(IC_SkillInterface::BeginAction, return;)
		virtual void EndAction() PURE_VIRTUAL(IC_SkillInterface::EndAction, return;)
		virtual void Activate() PURE_VIRTUAL(IC_SkillInterface::Activate, return;)
		virtual void Deactivate() PURE_VIRTUAL(IC_SkillInterface::Deactivate, return;)



		virtual void RestartCooldown() PURE_VIRTUAL(IC_SkillInterface::RestartCooldown, return;)

		virtual bool CanActivate() PURE_VIRTUAL(IC_SkillInterface::CanActivate, return false;)
		virtual float GetSkillCoolDown() PURE_VIRTUAL(IC_SkillInterface::GetSkillCoolDown, return 0.0f;)
};
