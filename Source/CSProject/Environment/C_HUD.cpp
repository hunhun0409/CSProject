// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/C_HUD.h"
#include "Engine/Canvas.h"
#include "Slate/SceneViewport.h"
#include "Kismet/KismetMathLibrary.h"

AC_HUD::AC_HUD()
{
	PrimaryActorTick.bCanEverTick = true;

	TextMoveOffset = { 0.0f, -0.4f };
}

void AC_HUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AC_HUD::AddDamageText(const float& FinalDamage, const bool& bCrit, const bool& bEvade, const FVector2D ScreenPosition)
{
	FText Text;
	FLinearColor Color;

	if (bCrit)
	{
		Text = FText::FromString("Critical!\n" + FString::FromInt((int)FinalDamage));
		Color = FLinearColor::Yellow;
	}
	if (bEvade)
	{
		Text = FText::FromString("Miss!\n" + FString::FromInt((int)FinalDamage));
		Color = FLinearColor::Blue;
	}
	else
	{
		Text = FText::FromString("Hit!\n" + FString::FromInt((int)FinalDamage));
		Color = FLinearColor::Red;
	}

	FVector2D NewPosition = ScreenPosition + FVector2D(UKismetMathLibrary::RandomIntegerInRange(-10, 10), UKismetMathLibrary::RandomIntegerInRange(-30, 20));

	FDamageTextInfo NewText(NewPosition, Text, 3.0f, Color);

	NewText.CameraOffset = CameraPos;

	DamageTexts.Add(NewText);
}


void AC_HUD::DrawHUD()
{
	Super::DrawHUD();

	if (!Canvas)
		return;

	for (int32 i = 0; i < DamageTexts.Num(); ++i)
	{
		FDamageTextInfo& DamageText = DamageTexts[i];

		FVector2D TextPosition = DamageText.ScreenPosition + FVector2D((DamageText.CameraOffset.Y - CameraPos.Y), 0);

		FCanvasTextItem TextItem(TextPosition, DamageText.Text, GEngine->GetSmallFont(), DamageText.Color);
		TextItem.EnableShadow(FLinearColor::Black);
		Canvas->DrawItem(TextItem);

		DamageText.DisplayDuration -= GetWorld()->GetDeltaSeconds();
		DamageText.ScreenPosition += TextMoveOffset;
		if (DamageText.DisplayDuration <= 0)
		{
			DamageTexts.RemoveAt(i);
			i--;
		}
	}
}
