#include "Team7/Public/Character/T7_CharacterBase.h"
#include "Team7/Public/Combat/T7_CombatComponent.h"
#include "Team7/Public/Weapon/T7_Weapon.h"
#include "Team7/public/System/T7_GameStateBase.h"
#include "Team7/Public/Character/T7_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AT7_CharacterBase::AT7_CharacterBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CombatComponent = CreateDefaultSubobject<UT7_CombatComponent>(TEXT("CombatComponent"));
	GetCharacterMovement()->MaxWalkSpeed = NormalMaxWalkSpeed;
}

float AT7_CharacterBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	const float FinalDamage = ActualDamage * (1.0f - DamageReduction);
	CurrentHP = FMath::Clamp(CurrentHP - FinalDamage, 0.0f, MaxHP);
	if (FMath::IsNearlyZero(CurrentHP))
	{
		Dead();
	}
	return FinalDamage;
}

void AT7_CharacterBase::EquipWeapon(AT7_Weapon* Weapon)
{
    if (Weapon == nullptr || CombatComponent == nullptr) return;

    UE_LOG(LogTemp, Warning, TEXT("EquipWeapon() 호출됨! 장착 무기: %s"), *Weapon->GetName());

    CombatComponent->EquipWeapon(Weapon);  
    CurrentWeapon = Weapon;

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        AT7_GameStateBase* GameState = PC->GetWorld()->GetGameState<AT7_GameStateBase>();
        if (GameState)
        {
            GameState->UpdateWeaponInfo(
                Weapon->WeaponIcon,  // 무기 아이콘
                Weapon->WeaponName,  // 무기 이름
                Weapon->GetAmmo(),   // 현재 탄약
                Weapon->GetMaxAmmo() // 최대 탄약
            );
        }
    }
}

void AT7_CharacterBase::FireWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("FireWeapon() 호출됨!"));

	if (CurrentWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("현재 무기 있음 -> 무기 발사"));
		CurrentWeapon->Fire();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("현재 무기 없음!"));
	}
}

void AT7_CharacterBase::Dead()
{
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);

	// 각자 함수 받아서 이후 로직 처리
		// Enemy는 특정 시간 지나서 시체 사라지게
		// Player는 죽으면 GameOver 처리
}
