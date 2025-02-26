#include "Team7/Public/Character/T7_CharacterBase.h"
#include "Team7/Public/Combat/T7_CombatComponent.h"
#include "Team7/Public/Weapon/T7_Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"

AT7_CharacterBase::AT7_CharacterBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CombatComponent = CreateDefaultSubobject<UT7_CombatComponent>(TEXT("CombatComponent"));
	GetCharacterMovement()->MaxWalkSpeed = NormalMaxWalkSpeed;
}

float AT7_CharacterBase::GetCurrentHP() const
{
	return CurrentHP;
}

float AT7_CharacterBase::GetMaxHP() const
{
	return MaxHP;
}

void AT7_CharacterBase::EquipWeapon(AT7_Weapon* Weapon)
{
	UE_LOG(LogTemp, Warning, TEXT("EquipWeapon() 호출됨!"));
	CurrentWeapon = Weapon;
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
