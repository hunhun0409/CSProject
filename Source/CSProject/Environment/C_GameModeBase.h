// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Structs.h"
#include "Interface/C_DamageHandleInterface.h"
#include "C_GameModeBase.generated.h"


/**
 * 
 */

class AC_CSCharacter;
class AC_Field;
class AC_Base;
UCLASS(Abstract)
class CSPROJECT_API AC_GameModeBase : public AGameModeBase, public IC_DamageHandleInterface
{
	GENERATED_BODY()

public:
	AC_GameModeBase();

	AC_Field* GetField() { return Map; }

	UFUNCTION()
		const FUIData& GetUIData() { return Datas; }

	TDelegate<void()> UIDataUpdated;

	TDelegate<void(const float&, const bool&, const bool&, const FVector&)> SpawnDamageHUD;
	
	//TDelegate<void() <- 데미지량 및 유형(회피등을 담은 구조체를 매개변수로)
	//위 델리게이트는 캐릭터에 만들고, 여기선 연결 후 Text Actor 소환 연동

	const FVector2D& GetMaxYPos() { return CameraMovablePosY; }

	UFUNCTION()
		void SpawnCharacter(const FVector& Location, const int& SlotNum, const bool& IsLeftTeam = true);

	UFUNCTION()
		void SetVisiblePlayerSpawnableArea(const bool& IsVisible);

	void UnitDiedDataUpdate(class AC_CSCharacter* DiedUnit, const float& SPCoolRate, const float& ULTCoolRate);

	void SetField(class AC_Field* NewField);

protected:
	virtual void PrintDamage(float FinalDamage, bool bCrit, bool bEvade, FVector ActorLocation) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void CheckHP();

	UFUNCTION(BlueprintCallable)
		void CostReduce(const bool& IsLeft = true, const int& Cost = 0);

	void AutoPlay(const bool& IsLeft);

	TDelegate<void(FVector, int, bool)> AutoSpawning[2];

private:
	void RestoreCost(const float& DeltaTime);

	void InitBaseData();
public:
	
protected:
	UPROPERTY()
		class AC_Field* Map;

	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<class AC_CSCharacter>> LeftTeamOrganization;
	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<class AC_CSCharacter>> RightTeamOrganization;

	UPROPERTY()
		TArray<TSubclassOf<class AC_CSCharacter>> LeftTeamSpawnCycle;
	UPROPERTY()
		TArray<TSubclassOf<class AC_CSCharacter>> RightTeamSpawnCycle;

private:
	float CostRegenRatio = 1.0f;
	float MaxCost = 10.0f;
	FBasicData RightBaseData;
	FBasicData LeftBaseData;
	FUIData Datas;
	FVector2D CameraMovablePosY;
	FVector AIUnitSpawnLocaiton;
	TMap<FName, FUnitBattleData> UnitBattleDatas;

};
