#include "Skill/C_Skill.h"


AC_Skill::AC_Skill()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_Skill::BeginPlay()
{
	Super::BeginPlay();
}

void AC_Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AC_Skill::BeginAction()
{
}

void AC_Skill::EndAction()
{
}

void AC_Skill::Activate()
{
	bActivate = true;
}

void AC_Skill::Deactivate()
{
	bActivate = false;
}

