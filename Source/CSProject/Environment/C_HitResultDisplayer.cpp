// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/C_HitResultDisplayer.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AC_HitResultDisplayer::AC_HitResultDisplayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Text = CreateDefaultSubobject<UTextRenderComponent>("Text");

	SetRootComponent(Text);


}

// Called when the game starts or when spawned
void AC_HitResultDisplayer::BeginPlay()
{
	Super::BeginPlay();
	Text->SetText(TextToDisplay);
	//SetActorRotation(FRotator(0, -90, 0));
	SetLifeSpan(5.0f);

}

//void AC_HitResultDisplayer::OnConstruction(const FTransform& Transform)
//{
//	Super::OnConstruction(Transform);
//
//	Text->SetText(TextToDisplay);
//
//}

// Called every frame
void AC_HitResultDisplayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_HitResultDisplayer::SetDamageText(float FinalDamage, bool bCrit, bool bEvade)
{
	if (bCrit)
	{
		TextToDisplay = "Critical! " + FString::FromInt((int)FinalDamage);
		Text->SetTextRenderColor(FColor::Yellow);
	}
	else if (bEvade)
	{
		TextToDisplay = "Miss! " + FString::FromInt((int)FinalDamage);
		Text->SetTextRenderColor(FColor::Blue);
	}
	else
	{
		TextToDisplay = "Hit!" + FString::FromInt((int)FinalDamage);
		Text->SetTextRenderColor(FColor::Red);
	}
}

