// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "C_HUD.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDamageTextInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
		FVector2D ScreenPosition;

	UPROPERTY()
		FText Text;

	UPROPERTY()
		float DisplayDuration;

	UPROPERTY()
		FLinearColor Color;

	FVector CameraOffset;

	FDamageTextInfo() {}

	FDamageTextInfo(FVector2D Position, FText InText, float Duration, FLinearColor InColor)
		: ScreenPosition(Position), Text(InText), DisplayDuration(Duration), Color(InColor)
	{}
};

UCLASS()
class CSPROJECT_API AC_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AC_HUD();

	void Tick(float DeltaSeconds) override;

	UFUNCTION()
		void AddDamageText(const float& FinalDamage, const bool& bCrit, const bool& bEvade, const FVector2D ScreenPosition);
	UFUNCTION()
		void SetCameraPos(FVector InPos) { CameraPos = InPos; }
	//�÷��̾� ī�޶� ������ �� ���ؼ�
	//First pos - next pos��ŭ ScreenPosition�� ���ϱ�.
	//Delegate�� ActorLocation �ް�, AddDamgeText ����.

protected:
	void DrawHUD() override;

private:
	TArray<FDamageTextInfo> DamageTexts;
	FVector2D TextMoveOffset;
	FVector CameraPos;
};
