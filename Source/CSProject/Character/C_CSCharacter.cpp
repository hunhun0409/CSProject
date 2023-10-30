#include "Character/C_CSCharacter.h"
#include "Character/C_AnimInstance.h"

#include "Components/C_StatusComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

#include "Weapon/C_Weapon.h"


#include "Environment/C_Base.h"
#include "Environment/C_GameModeBase.h"

#include "Interface/C_DamageHandleInterface.h"
#include "Interface/C_WeaponInterface.h"
#include "Interface/C_SkillInterface.h"

#include "AI/C_CSAIController.h"

#include "Skill/C_Skill.h"
#include "Skill/C_PassiveSkill.h"
#include "Skill/C_ActiveSkill.h"

#include "Engine/Texture2D.h" 

#include "Particles/ParticleSystem.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameModeBase.h"

#include "Animation/AnimMontage.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#define CreateDefaultSubobjectAuto(Component)\
Component = CreateDefaultSubobject<std::remove_reference<decltype(*Component)>::type>(#Component)


AC_CSCharacter::AC_CSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobjectAuto(Status);

	CreateDefaultSubobjectAuto(HitEffect);

	CreateDefaultSubobjectAuto(StatusUI);

	CreateDefaultSubobjectAuto(CharacterImage);



	StatusUI->SetWidgetSpace(EWidgetSpace::Screen);
	StatusUI->SetDrawAtDesiredSize(true);

	StatusUI->SetupAttachment(RootComponent);
	

	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCapsuleComponent()->SetCollisionObjectType(ECC_Pawn);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

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
			Status->ApplyStatus(Data[0]);
		}
	}
}

void AC_CSCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*if (DataTable != nullptr)
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
	}*/

	InitState();
	InitWeapon();
	InitSkill();

	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::CharacterMontageEnded);
	GetMesh()->GetAnimInstance()->OnMontageBlendingOut.AddDynamic(this, &ThisClass::CharacterMontageBlendingOut);
	OnTakeAnyDamage.AddDynamic(this, &ThisClass::GetDamaged);
}

void AC_CSCharacter::OnConstruction(FTransform const& Transform)
{
	Super::OnConstruction(Transform);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88.5f));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0).Quaternion());
}

void AC_CSCharacter::PrintState()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, *StateToName.Find(*CharacterState));

	//FString MyBoolString = bMove ? TEXT("true") : TEXT("false");
	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, MyBoolString);
}


void AC_CSCharacter::CharacterMontageEnded(UAnimMontage* const Montage, bool bInterrupted)
{
	if (bInterrupted)
	{
	}
	else
	{
		*CharacterState = ECharacterState::Idle;
	}
}

void AC_CSCharacter::CharacterMontageBlendingOut(UAnimMontage* const montage, bool bInterrupted)
{
}

void AC_CSCharacter::Tick(float DeltaTime)
{
	if (IsDead())
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, "IsDead!");
		return;
	}
		
	Super::Tick(DeltaTime);
	PrintState();
	if(bMove)
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, "bMove == true!");


	if(bMove && *CharacterState == ECharacterState::Idle)
		MoveForward();
}

void AC_CSCharacter::SetSPSkillCoolRate(const float& InRate)
{
	if (SpecialSkill)
		SpecialSkill->SetSkillCoolDown(InRate);
}

void AC_CSCharacter::SetULTSkillCoolRate(const float& InRate)
{
	if (UltimateSkill)
		UltimateSkill->SetSkillCoolDown(InRate);
}

void AC_CSCharacter::Attack()
{
	if (IsDead())
		return;
	if (bCanActivateAttack)
	{
		FRotator rot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
		SetActorRotation(rot.Quaternion(), ETeleportType::TeleportPhysics);

		*CharacterState = ECharacterState::Attacking;

		Weapon->ActivateAttack();
	}
}

void AC_CSCharacter::SPSkill()
{
	if (IsDead())
		return;
	if (bCanActivateSP)
	{
		*CharacterState = ECharacterState::SP_Skilling;

		SpecialSkill->BeginAction();
	}
}

void AC_CSCharacter::ULTSkill()
{
	if (IsDead())
		return;
	if (bCanActivateULT)
	{
		*CharacterState = ECharacterState::ULT_Skilling;

		UltimateSkill->BeginAction();
	}
}

void AC_CSCharacter::Die()
{
	*CharacterState = ECharacterState::Dead;
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), FoundActors);

	Cast<AActor>(Weapon)->Destroy();
	StatusUI->SetVisibility(false);

	auto* GameMode = Cast<AC_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	float SPCoolRate = 0.0f;
	float ULTCoolRate = 0.0f;
	if (SpecialSkill)
	{
		//0~1사이값 반환, 0.5면 50% 찼다는 뜻
		SPCoolRate = SpecialSkill->GetSkillCoolDown();
	}
	if (UltimateSkill)
	{
		ULTCoolRate = UltimateSkill->GetSkillCoolDown();
	}

	GameMode->UnitDiedDataUpdate(this, SPCoolRate, ULTCoolRate);

	//Todo
	//상대 함선에게 죽음을 알림 : 미완성
	//TArray<AC_Base*> AllBase;
	//for (AActor* actor : FoundActors)
	//{
	//	if (actor == this)
	//		continue;
	//	AC_Base* Base = Cast<AC_Base>(actor);
	//	if (Base)
	//	{
	//		AllBase.Add(Base);
	//	}
	//}

	//for (AC_Base* Base : AllBase)
	//{
	//	//아군이면 패스
	//	if (Base->GetTeamID() == TeamID)
	//		continue;
	//	//IsValid
	//	if (IsValid(Base))
	//	{
	//		Cast<AC_CSAIController>(character->GetController())->RemoveTarget(this);
	//	}
	//}





	//전장에 있는 캐릭터들에게 죽음을 알림
	TArray<AC_CSCharacter*> AllCharacters;
	for (AActor* actor : FoundActors)
	{
		if (actor == this)
			continue;
		AC_CSCharacter* Character = Cast<AC_CSCharacter>(actor);
		if (Character)
		{
			AllCharacters.Add(Character);
		}
	}

	for (AC_CSCharacter* character : AllCharacters)
	{
		//아군이면 패스
		if (character->GetTeamID() == TeamID)
			continue;
		//IsValid
		if (IsValid(character))
		{
			Cast<AC_CSAIController>(character->GetController())->RemoveTarget(this);
		}
	}



	uint8 i = UKismetMathLibrary::RandomIntegerInRange(0, DieMontage.Num() - 1);
	PlayAnimMontage(DieMontage[i]);
	SetLifeSpan(3.0f);
}

void AC_CSCharacter::InitState()
{
	GetCharacterMovement()->MaxWalkSpeed = Status->GetMovementSpeed();

	CharacterState = decltype(CharacterState)(new ECharacterState);
	*CharacterState = ECharacterState::Idle;
	StateToName = {
		{ECharacterState::Idle, TEXT("Idle")},
		{ECharacterState::Attacking, TEXT("Attacking")},
		{ECharacterState::SP_Skilling, TEXT("SP_Skilling")},
		{ECharacterState::ULT_Skilling, TEXT("ULT_Skilling")},
		{ECharacterState::Dead, TEXT("Dead")},
	};
}

void AC_CSCharacter::InitWeapon()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = SpawnParameters.Instigator = this;
	
	auto* const SpawnedWeapon = GetWorld()->SpawnActor<AC_Weapon>(WeaponClass, SpawnParameters);
	//SpawnedWeapon->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FAttachmentTransformRules const Rules(EAttachmentRule::SnapToTarget, true);

	SpawnedWeapon->AttachToComponent(GetMesh(), Rules, SpawnedWeapon->SocketOnEquipped);

	Cast<UC_AnimInstance>(GetMesh()->GetAnimInstance())->SetWeaponClass(WeaponClass);
	Weapon = SpawnedWeapon;

}
void AC_CSCharacter::InitSkill()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = SpawnParameters.Instigator = this;
	FAttachmentTransformRules const Rules(EAttachmentRule::SnapToTarget, true);

	//pasive
	if (PassiveSkillClasses.Num() != 0)
	{
		for (auto& PassiveSkillClass : PassiveSkillClasses)
		{
			auto* const SpawnedPasiveSkill = GetWorld()->SpawnActor<AC_Skill>(PassiveSkillClass, SpawnParameters);
			SpawnedPasiveSkill->AttachToComponent(GetMesh(), Rules);
			PasiveSkills.AddUnique(SpawnedPasiveSkill);
		}
	}
	
	//special
	if (SpecialSkillClass != nullptr)
	{
		auto* const SpawnedSPSkill = GetWorld()->SpawnActor<AC_Skill>(SpecialSkillClass, SpawnParameters);
		SpawnedSPSkill->AttachToComponent(GetMesh(), Rules);
		SpecialSkill = SpawnedSPSkill;


	}
	//ultimate
	if (UltimateSkillClass != nullptr)
	{
		auto* const SpawnedUltSkill = GetWorld()->SpawnActor<AC_Skill>(UltimateSkillClass, SpawnParameters);
		SpawnedUltSkill->AttachToComponent(GetMesh(), Rules);
		UltimateSkill = SpawnedUltSkill;
	}
}

void AC_CSCharacter::MoveForward()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, "WalkForward!!");

	//walk Forward
	FVector Direction;
	switch(TeamID)
	{
	case 0:
		//SetActorRelativeRotation(FRotator(0, 1, 0).Quaternion());
		Direction = FVector(0, 1, 0);
		break;
	case 1:
		//SetActorRelativeRotation(FRotator(0, -1, 0).Quaternion());
		Direction = FVector(0, -1, 0);
		break;
	}
	AddMovementInput(Direction);
}

void AC_CSCharacter::GetDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	float FinalDamage = CalculateDamage(Damage, DamageCauser);
	Status->AddHealth(-FinalDamage);
	FVector Location = GetActorLocation() + FVector(0, 0, 60);
	FRotator Rotation = GetActorRotation() + FRotator(-60, 0, 0);
	FVector Scale = FVector(0.5f, 0.5f, 0.5f);
	const FTransform Transform = FTransform(Rotation, Location, Scale);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Transform);

	UpdateLifeGauge();
	if (Status->GetCurHealth() <= 0)
	{
		Die();
	}
}
float AC_CSCharacter::CalculateDamage(float Damage, AActor* DamageCauser)
{
	//감소률 계산할 변수들
	float DefenseReduceRate = 1;
	float ClassTypeDamageReduceRate = 1;
	float EvadeReduceRate = 1;
	float CritDamageAmplitudeRate = 1;

	//가해자 정보
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
	else if (MyDamageCauser->IsA<AC_Base>())
	{
		CauserClass = Cast<AC_Base>(MyDamageCauser)->GetStatus()->GetClassType();
		CauserHit = Cast<AC_Base>(MyDamageCauser)->GetStatus()->GetHit();
		CauserCrit = Cast<AC_Base>(MyDamageCauser)->GetStatus()->GetCrit();
		CauserCritDamage = Cast<AC_Base>(MyDamageCauser)->GetStatus()->GetCritDamage();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Wrong DamageCauserType!");
		return 0;
	}

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
		bCrit = false;
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
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	Cast<IC_DamageHandleInterface>(GameMode)->PrintDamage(FinalDamage, bCrit, bEvade, GetActorLocation());
	

	return FinalDamage;

}
