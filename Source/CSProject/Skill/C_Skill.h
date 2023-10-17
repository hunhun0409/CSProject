#pragma once

#include "C_SkillInterface.h"

#include "Enum/ESkillType.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Skill.generated.h"

UCLASS()
class CSPROJECT_API AC_Skill : public AActor, public IC_SkillInterface
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(EditDefaultsOnly)
		ESkillType SkillType;
	

public:	
	AC_Skill();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	void BeginAction() override;
	void EndAction() override;
	void Activate() override;
	void Deactivate() override;
protected:
	bool bActivate = false;
};
