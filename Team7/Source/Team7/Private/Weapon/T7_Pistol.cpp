

#include "Weapon/T7_Pistol.h"

AT7_Pistol::AT7_Pistol()
{
    WeaponType = EWeaponType::EWT_Pistol;

    WeaponName = TEXT("Pistol");
    MaxAmmo = 12;  
    Ammo = MaxAmmo;

    UE_LOG(LogTemp, Warning, TEXT("Pistol Created! MaxAmmo: %d"), MaxAmmo);
}

void AT7_Pistol::Fire()
{
    
    Super::Fire();
}
