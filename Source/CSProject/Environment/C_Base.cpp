// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Base.h"
#include "Perception/AIPerceptionComponent.h"
#include "Enum/EClassType.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Character/C_CSCharacter.h"

// Sets default values
AC_Base::AC_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");

}

// Called when the game starts or when spawned
void AC_Base::BeginPlay()
{
	Super::BeginPlay();
	
	if (DataTable != nullptr)
	{
		TArray<FStatusData const*> Rows;
		DataTable->GetAllRows("", Rows);

		TArray<FStatusData> Value;
		for (auto& Row : Rows)
		{
			if (Row->Name == Name)
			{
				Value.Add(*Row);
			}
		}
		StatusMap.Add(Name, Value);


		TArray<FStatusData> Data = StatusMap[Name];
		if (Data.Num())
		{
			Status->ApplyStatus(Data[0]);
		}
	}

	
}

float AC_Base::CalculateDamage(float Damage, AActor* DamageCauser)
{
	//감소률 계산할 변수들
	float DefenseReduceRate = 1;
	float ClassTypeDamageReduceRate = 1;
	float EvadeReduceRate = 1;
	float CritDamageAmplitudeRate = 1;

	//가해자 정보
	auto* MyDamageCauser = DamageCauser->GetInstigator();
	EClassType CauserClass = Cast<AC_CSCharacter>(MyDamageCauser)->GetStatus()->GetClassType();
	float CauserHit = Cast<AC_CSCharacter>(MyDamageCauser)->GetStatus()->GetHit();
	float CauserCrit = Cast<AC_CSCharacter>(MyDamageCauser)->GetStatus()->GetCrit();
	float CauserCritDamage = Cast<AC_CSCharacter>(MyDamageCauser)->GetStatus()->GetCritDamage();

	//피해자 정보
	float Defense = Status->GetDefense();
	float Eva = Status->GetEva();
	EClassType MyClass = Status->GetClassType();

	//회피 치명 bool 변수
	bool bEvade;
	bool bCrit;

	//방어 감소 적용
	DefenseReduceRate = (1 - (Defense / (1000 + Defense)));

	//상성 피해 적용
	switch (CauserClass)
	{
	case EClassType::Defender:
		switch (MyClass)
		{
		case EClassType::Ranger:
			ClassTypeDamageReduceRate = 0.7;
			break;
		case EClassType::Sniper:
			ClassTypeDamageReduceRate = 1.3;
			break;
		default:
			ClassTypeDamageReduceRate = 1;
			break;
		}
		break;
	case EClassType::Striker:
		switch (MyClass)
		{
		case EClassType::Sniper:
			ClassTypeDamageReduceRate = 0.7;
			break;
		case EClassType::Ranger:
			ClassTypeDamageReduceRate = 1.3;
			break;
		default:
			ClassTypeDamageReduceRate = 1;
			break;
		}
		break;
	case EClassType::Ranger:
		switch (MyClass)
		{
		case EClassType::Striker:
			ClassTypeDamageReduceRate = 0.7;
			break;
		case EClassType::Defender:
			ClassTypeDamageReduceRate = 1.3;
			break;
		default:
			ClassTypeDamageReduceRate = 1;
			break;
		}
		break;
	case EClassType::Sniper:
		switch (MyClass)
		{
		case EClassType::Defender:
			ClassTypeDamageReduceRate = 0.7;
			break;
		case EClassType::Striker:
			ClassTypeDamageReduceRate = 1.3;
			break;
		default:
			ClassTypeDamageReduceRate = 1;
			break;
		}
		break;
	default:
		ClassTypeDamageReduceRate = 1;
	}
	//회피 적용
	float EvadeRate = (Eva - CauserHit) / ((Eva - CauserHit) + 800);
	float randFloat = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
	bEvade = EvadeRate >= randFloat;
	if (bEvade)
	{
		EvadeReduceRate = 0.9 - (CauserHit / (CauserHit + 1500));
	}
	else//치명 여부
	{
		float CritRate = CauserCrit / (CauserCrit + 1000);
		float randomFloat = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
		bCrit = CritRate >= randomFloat;
		if (bCrit)//치명시
		{
			CritDamageAmplitudeRate = 1 + (CauserCritDamage / 100);
		}
	}

	//방어 감소율 회피 감소율 상성피해 치명피해 적용
	float FinalAdjustment = DefenseReduceRate * ClassTypeDamageReduceRate *
		EvadeReduceRate * CritDamageAmplitudeRate;

	//감소 최소수치는 0.2
	FinalAdjustment = FMath::Clamp(FinalAdjustment, 0.2f, 5.0f);

	//-5~5프로 랜덤 편차
	float RandomAdjust = UKismetMathLibrary::RandomFloatInRange(0.95f, 1.05f);
	float FinalDamage = Damage * FinalAdjustment * RandomAdjust;

	//GameModeBase::PrintDamage
	//AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	//Cast<IC_DamageHandleInterface>(GameMode)->PrintDamage(FinalDamage, bCrit, bEvade, GetActorLocation());

	return FinalDamage;
}

// Called every frame
void AC_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
