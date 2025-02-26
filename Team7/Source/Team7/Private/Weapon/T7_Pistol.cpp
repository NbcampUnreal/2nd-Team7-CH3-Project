

#include "Weapon/T7_Pistol.h"

AT7_Pistol::AT7_Pistol()
{
    WeaponType = EWeaponType::EWT_Pistol; 

    // ������ �⺻ ����
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

    SpendRound();  // ź�� ����
    UpdateAmmoHUD();  // UI ����

    // ���� �߻� Ư�� (���� �ӵ��� ����)
    GetWorldTimerManager().SetTimer(TimerHandle_Reload, this, &AT7_Pistol::Fire, 0.2f, false);
}