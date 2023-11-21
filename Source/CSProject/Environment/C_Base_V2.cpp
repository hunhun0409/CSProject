
#include "Environment/C_Base_V2.h"
#include "Perception/AIPerceptionComponent.h"
#include "Enum/EClassType.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Character/C_CSCharacter.h"
#include "Components/C_StatusComponent.h"
#include "Particles/ParticleSystem.h"
#include "C_GameModeBase.h"

AC_Base_V2::AC_Base_V2()
{
	PrimaryActorTick.bCanEverTick = true;

	//AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");
	Status = CreateDefaultSubobject<UC_StatusComponent>("Status");

	HitEffect = CreateDefaultSubobject<UParticleSystem>("ParticleSystem");

}

void AC_Base_V2::BeginPlay()
{
	Super::BeginPlay();
	
	if (DataTable && !Name.IsNone())
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
			Status->ApplyStatus(Data[0]); // ����
		}
	}

	if (auto* GameMode = Cast<AC_GameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		Spawn.BindUFunction(GameMode, "SpawnCharacter");
	}

	OnTakeAnyDamage.AddDynamic(this, &ThisClass::GetDamaged);

}

void AC_Base_V2::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AC_Base_V2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AC_Base_V2::CalculateDamage(float Damage, AActor* DamageCauser)
{
	//���ҷ� ����� ������
	float DefenseReduceRate = 1;
	float ClassTypeDamageReduceRate = 1;
	float EvadeReduceRate = 1;
	float CritDamageAmplitudeRate = 1;

	//������ ����
	auto* MyDamageCauser = DamageCauser->GetInstigator();
	EClassType CauserClass;
	float CauserHit;
	float CauserCrit;
	float CauserCritDamage;

	if (MyDamageCauser->IsA<AC_CSCharacter>())
	{
		CauserClass = Cast<AC_CSCharacter>(MyDamageCauser)->GetStatus()->GetClassType();
		CauserHit = Cast<AC_CSCharacter>(MyDamageCauser)->GetStatus()->GetHit();
		CauserCrit = Cast<AC_CSCharacter>(MyDamageCauser)->GetStatus()->GetCrit();
		CauserCritDamage = Cast<AC_CSCharacter>(MyDamageCauser)->GetStatus()->GetCritDamage();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Wrong DamageCauserType!");
		return 0;
	}

	//������ ����
	float Defense = Status->GetDefense();
	float Eva = Status->GetEva();
	EClassType MyClass = Status->GetClassType();

	//ȸ�� ġ�� bool ����
	bool bEvade;
	bool bCrit;

	//��� ���� ����
	DefenseReduceRate = (1 - (Defense / (1000 + Defense)));

	//�� ���� ����
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
	//ȸ�� ����
	float EvadeRate = (Eva - CauserHit) / ((Eva - CauserHit) + 800);
	float randFloat = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
	bEvade = EvadeRate >= randFloat;
	if (bEvade)
	{
		EvadeReduceRate = 0.9 - (CauserHit / (CauserHit + 1500));
		bCrit = false;
	}
	else//ġ�� ����
	{
		float CritRate = CauserCrit / (CauserCrit + 1000);
		float randomFloat = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
		bCrit = CritRate >= randomFloat;
		if (bCrit)//ġ���
		{
			CritDamageAmplitudeRate = 1 + (CauserCritDamage / 100);
		}
	}

	//��� ������ ȸ�� ������ ������ ġ������ ����
	float FinalAdjustment = DefenseReduceRate * ClassTypeDamageReduceRate *
		EvadeReduceRate * CritDamageAmplitudeRate;

	//���� �ּҼ�ġ�� 0.2
	FinalAdjustment = FMath::Clamp(FinalAdjustment, 0.2f, 5.0f);

	//-5~5���� ���� ����
	float RandomAdjust = UKismetMathLibrary::RandomFloatInRange(0.95f, 1.05f);
	float FinalDamage = Damage * FinalAdjustment * RandomAdjust;



	//GameModeBase::PrintDamage
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	Cast<IC_DamageHandleInterface>(GameMode)->PrintDamage(FinalDamage, bCrit, bEvade, GetActorLocation());


	return FinalDamage;
}

void AC_Base_V2::GetDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	float FinalDamage = CalculateDamage(Damage, DamageCauser);
	Status->AddHealth(-FinalDamage);
	FVector Location = GetActorLocation() + FVector(0, 0, 60);
	FRotator Rotation = GetActorRotation() + FRotator(-60, 0, 0);
	FVector Scale = FVector(0.5f, 0.5f, 0.5f);
	const FTransform Transform = FTransform(Rotation, Location, Scale);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Transform);

}

void AC_Base_V2::SpawnCharacter(const FVector& Location, const int& SlotNum, const bool& IsLeftTeam)
{
	if (IsAutoSpawning)
	{
		Spawn.ExecuteIfBound(AutoSpawnLocation, SlotNum, IsLeftTeam);
	}
	else
	{
		Spawn.ExecuteIfBound(Location, SlotNum, IsLeftTeam);
	}
}

void AC_Base_V2::SetTeamID(uint8 InTeamID)
{
	TeamID = InTeamID;
	if (TeamID == 0)
	{
		AutoSpawnLocation = GetActorTransform().GetTranslation() + GetActorForwardVector() * 2;
	}
	else
	{
		AutoSpawnLocation = GetActorLocation() - GetActorForwardVector() * 2;

		IsAutoSpawning = true;
	}
}


