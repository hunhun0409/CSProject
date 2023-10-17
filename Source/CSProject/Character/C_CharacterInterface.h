#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "C_CharacterInterface.generated.h"

UINTERFACE(MinimalAPI)
class UC_CharacterInterface : public UInterface
{
	GENERATED_BODY()
};

class CSPROJECT_API IC_CharacterInterface
{
	GENERATED_BODY()

public:
	virtual void Attack()	PURE_VIRTUAL(IC_CharacterInterface::Attack, return;)
	virtual void SPSkill()	PURE_VIRTUAL(IC_CharacterInterface::SPSkill, return;)
	virtual void ULTSkill()	PURE_VIRTUAL(IC_CharacterInterface::ULTSkill, return;)
};
