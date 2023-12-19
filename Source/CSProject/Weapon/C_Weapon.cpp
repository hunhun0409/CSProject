#include "Weapon/C_Weapon.h"
#include "Character/C_CSCharacter.h"

#include "Particles/ParticleSystemComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/C_StatusComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Animation/AnimMontage.h"


#define CreateDefaultSubobjectAuto(Component)\
Component = CreateDefaultSubobject<std::remove_reference<decltype(*Component)>::type>(#Component)

AC_Weapon::AC_Weapon()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");

	SetRootComponent(Mesh);

	CreateDefaultSubobjectAuto(Trail);
	Trail->SetupAttachment(Mesh);

	CreateDefaultSubobjectAuto(Effect);
	Effect->SetupAttachment(Mesh);

	

	CreateDefaultSubobjectAuto(AttackMontage);


}

USkeletalMeshComponent* AC_Weapon::GetMesh()
{
	return Mesh;
}

void AC_Weapon::BeginPlay()
{
	Super::BeginPlay();
}

void AC_Weapon::BeginAction()
{
	//공격 애니메이션 실행
	if (!IsValid(GetOwner()))
		return;
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, "BeginAction");
	AC_CSCharacter* const WeaponOwner = Cast<AC_CSCharacter>(GetOwner());

	if (WeaponOwner)
	{
		if (AttackMontage)
		{
			WeaponOwner->GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &ThisClass::OnNotifyStart);
			WeaponOwner->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::OnMontageEnded);


			float attackRate = Cast<AC_CSCharacter>(GetOwner())->GetStatus()->GetAttackRate();

			WeaponOwner->PlayAnimMontage(AttackMontage, attackRate);

			WeaponOwner->bCanActivateAttack = false;
			if (AttackTimer == FTimerHandle())
			{
				GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &ThisClass::NotifyCanAttack, 1 / attackRate, false);
			}
		}
	}
}

void AC_Weapon::EndAction()
{
	//애니메이션 종료
	if (!IsValid(GetOwner()))
		return;

	AC_CSCharacter* WeaponOwner = Cast<AC_CSCharacter>(GetOwner());
	*(WeaponOwner->CharacterState) = ECharacterState::Idle;

	WeaponOwner->GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &ThisClass::OnMontageEnded);
	WeaponOwner->GetMesh()->GetAnimInstance()->OnMontageBlendingOut.RemoveDynamic(this, &ThisClass::OnMontageInterrupted);

	WeaponOwner->GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.RemoveDynamic(this, &ThisClass::OnNotifyStart);	
}

void AC_Weapon::Activate()
{

}

void AC_Weapon::Deactivate()
{
}

void AC_Weapon::ApplyDamage()
{
	//Target에게 데미지 전달
	AC_CSCharacter* const WeaponOwner = Cast<AC_CSCharacter>(GetOwner());
	if (WeaponOwner)
	{
		OnAttackEvent(WeaponOwner->Target);
		float attackRate = WeaponOwner->GetStatus()->GetAttackRate();
		float damage = WeaponOwner->GetStatus()->GetAttack();
		UGameplayStatics::ApplyDamage(WeaponOwner->Target, damage, GetInstigatorController(), this, UDamageType::StaticClass());
	}
}

void AC_Weapon::ActivateTrail()
{
}

void AC_Weapon::DeactivateTrail()
{
}

void AC_Weapon::ActivateEffect()
{
}

void AC_Weapon::DeactivateEffect()
{
}

void AC_Weapon::OnNotifyStart(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName == "ApplyDamage")
	{
		ApplyDamage();
	}
}

void AC_Weapon::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	EndAction();
}

void AC_Weapon::OnMontageInterrupted(UAnimMontage* Montage, bool bInterrupted)
{
	EndAction();
}


void AC_Weapon::NotifyCanAttack()
{

	AC_CSCharacter* const WeaponOwner = Cast<AC_CSCharacter>(GetOwner());

	if (WeaponOwner)
	{
		GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
		WeaponOwner->bCanActivateAttack = true;
	}
}


