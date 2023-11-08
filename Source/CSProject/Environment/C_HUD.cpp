// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/C_HUD.h"
#include "Engine/Canvas.h"
#include "Slate/SceneViewport.h"

AC_HUD::AC_HUD()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_HUD::AddDamageText(const float& FinalDamage, const bool& bCrit, const bool& bEvade, const FVector2D ScreenPosition)
{
	FText Text;
	FLinearColor Color;

	if (bCrit)
	{
		Text = FText::FromString("Critical! " + FString::FromInt((int)FinalDamage));
		Color = FLinearColor::Yellow;
	}
	if (bEvade)
	{
		Text = FText::FromString("Miss! " + FString::FromInt((int)FinalDamage));
		Color = FLinearColor::Blue;
	}
	else
	{
		Text = FText::FromString("Hit! " + FString::FromInt((int)FinalDamage));
		Color = FLinearColor::Red;
	}

	FDamageTextInfo NewText(ScreenPosition, Text, 3.0f, Color);



	DamageTexts.Add(NewText);
}


void AC_HUD::DrawHUD()
{
	Super::DrawHUD();

	if (!Canvas)
		return;

	//FVector2D ViewportSize;
	//GEngine->GameViewport->GetViewportSize(ViewportSize);

	for (int32 i = 0; i < DamageTexts.Num(); ++i)
	{
		FDamageTextInfo& DamageText = DamageTexts[i];

		//FVector2D ScreenPosition = DamageText.ScreenPosition * ViewportSize;

		FCanvasTextItem TextItem(DamageText.ScreenPosition, DamageText.Text, GEngine->GetSmallFont(), DamageText.Color);
		TextItem.EnableShadow(FLinearColor::Black);
		Canvas->DrawItem(TextItem);

		DamageText.DisplayDuration -= GetWorld()->GetDeltaSeconds();

		if (DamageText.DisplayDuration <= 0)
		{
			DamageTexts.RemoveAt(i);
			i--;
		}
	}
}
