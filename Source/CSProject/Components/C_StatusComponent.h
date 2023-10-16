// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_StatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CSPROJECT_API UC_StatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UC_StatusComponent();

protected:
	virtual void BeginPlay() override;
		
};
