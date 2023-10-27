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
UCLASS(Abstract)
class CSPROJECT_API AC_GameModeBase : public AGameModeBase, public IC_DamageHandleInterface
{
	GENERATED_BODY()

public:
	AC_GameModeBase();

	const AC_Field* GetField() { return Map; }

	UFUNCTION()
		const FUIData& GetUIData() { return Datas; }

	TDelegate<void()> UIDataUpdated;
	
	//TDelegate<void() <- �������� �� ����(ȸ�ǵ��� ���� ����ü�� �Ű�������)
	//�� ��������Ʈ�� ĳ���Ϳ� �����, ���⼱ ���� �� Text Actor ��ȯ ����

	const FVector2D& GetMaxYPos() { return CameraMovablePosY; }

	UFUNCTION()
		void SpawnCharacter(const FVector& Location, const int& SlotNum, const bool& IsLeftTeam = true);

	UFUNCTION()
		void SetVisiblePlayerSpawnableArea(const bool& IsVisible);

	void UnitDiedDataUpdate(class AC_CSCharacter* DiedUnit, const float& SPCoolRate, const float& ULTCoolRate);

protected:
	virtual void PrintDamage(float FinalDamage, bool bCrit, bool bEvade, FVector ActorLocation) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void CheckHP();

	UFUNCTION(BlueprintCallable)
		void CostReduce(const bool& IsLeft = true, const int& Cost = 0);

private:
	void RestoreCost(const float& DeltaTime);

public:

protected:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AC_Field> Field;

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
