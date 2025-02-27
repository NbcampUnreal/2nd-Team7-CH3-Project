

#include "Weapon/T7_Rifle.h"

AT7_Rifle::AT7_Rifle()
{

	WeaponType = EWeaponType::EWT_AssaultRifle;

	WeaponName = TEXT("Rifle");
	MaxAmmo = 30;
	Ammo = MaxAmmo;

	UE_LOG(LogTemp, Warning, TEXT("Rifle Created! MaxAmmo: %d"), MaxAmmo);
}

void AT7_Rifle::Fire()
{
	Super::Fire();

}