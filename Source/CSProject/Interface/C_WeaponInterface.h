#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "C_WeaponInterface.generated.h"

UINTERFACE(MinimalAPI)
class UC_WeaponInterface : public UInterface
{
	GENERATED_BODY()
};

class CSPROJECT_API IC_WeaponInterface
{
	GENERATED_BODY()
public:
	virtual void BeginAction()	PURE_VIRTUAL(IC_WeaponInterface::BeginAction, return;)
	virtual void EndAction()	PURE_VIRTUAL(IC_WeaponInterface::EndAction, return;)
	virtual void Activate() PURE_VIRTUAL(IC_SkillInterface::Activate, return;)
	virtual void Deactivate() PURE_VIRTUAL(IC_SkillInterface::Deactivate, return;)
	
	virtual void ApplyDamage() PURE_VIRTUAL(IC_SkillInterface::ApplyDamage, return;)
	virtual void ActivateTrail() PURE_VIRTUAL(IWeaponInterface::ActivateTrail, return;)
	virtual void DeactivateTrail() PURE_VIRTUAL(IWeaponInterface::DeactivateTrail, return;)
	virtual void ActivateEffect() PURE_VIRTUAL(IWeaponInterface::ActivateEffect, return;)
	virtual void DeactivateEffect() PURE_VIRTUAL(IWeaponInterface::DeactivateEffect, return;)
};
