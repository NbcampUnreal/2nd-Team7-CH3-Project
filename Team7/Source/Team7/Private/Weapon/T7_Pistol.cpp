

#include "Weapon/T7_Pistol.h"

AT7_Pistol::AT7_Pistol()
{
    WeaponType = EWeaponType::EWT_Pistol; 

    // 권총의 기본 설정
    WeaponName = TEXT("Pistol");
    MaxAmmo = 12;
    Ammo = MaxAmmo;
}

void AT7_Pistol::Fire()
{
    if (!CanFire())
    {
        UE_LOG(LogTemp, Warning, TEXT("Pistol: No ammo! Reload required."));
        Reload();
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Pistol Fire! Ammo left: %d"), Ammo - 1);

    SpendRound();  // 탄약 감소
    UpdateAmmoHUD();  // UI 갱신

    // 권총 발사 특성 (연사 속도가 빠름)
    GetWorldTimerManager().SetTimer(TimerHandle_Reload, this, &AT7_Pistol::Fire, 0.2f, false);
}