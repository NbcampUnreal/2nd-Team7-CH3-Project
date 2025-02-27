// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/T7_Shotgun.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/T7_ShotgunProjectile.h"
#include "Character/T7_PlayerCharacter.h"

AT7_Shotgun::AT7_Shotgun()
{
    WeaponType = EWeaponType::EWT_Shotgun;

    WeaponName = TEXT("Shotgun");
	Damage = 10.0f;

}
void AT7_Shotgun::Fire()
{
    if (!ShotgunProjectileClass) return; // Projectile 클래스가 없으면 발사 X

    Super::Fire(); // 기본 Fire 기능 실행 (HUD 업데이트, 탄약 감소 등)

    APawn* OwnerPawn = Cast<APawn>(GetOwner());
    if (!OwnerPawn) return;

    AController* InstigatorController = OwnerPawn->GetController();
    if (!InstigatorController) return;

    const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName("MuzzleFlash");
    if (!MuzzleFlashSocket) return;

    FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
    FVector MuzzleLocation = SocketTransform.GetLocation();
    FRotator MuzzleRotation = SocketTransform.Rotator();

    UWorld* World = GetWorld();
    if (!World) return;

    int32 NumPellets = 8;  // 탄알 개수
    float SpreadAngle = 10.0f; // 퍼지는 각도 (도 단위)

    for (int32 i = 0; i < NumPellets; i++)
    {
        // 랜덤한 퍼짐 적용
        FRotator RandomSpread = MuzzleRotation + FRotator(
            FMath::RandRange(-SpreadAngle, SpreadAngle),
            FMath::RandRange(-SpreadAngle, SpreadAngle),
            0.0f
        );

        FVector ShootDirection = RandomSpread.Vector();
        FVector End = MuzzleLocation + (ShootDirection * 5000.0f); // 사거리 설정

        DrawDebugLine(World, MuzzleLocation, End, FColor::Red, false, 1.0f, 0, 1.0f);

        // 탄환 생성
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = OwnerPawn;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

        AT7_ShotgunProjectile* Projectile = World->SpawnActor<AT7_ShotgunProjectile>(
            ShotgunProjectileClass, MuzzleLocation, ShootDirection.Rotation(), SpawnParams);

        if (Projectile)
        {
            Projectile->SetOwner(this);
        }
    }
}

/*void AT7_Shotgun::SpendRound()
{
	int32 AmmoUsedPerShot = 1; // 샷건이 한 번 쏠 때 사용하는 탄약 개수 (필요하면 2~3으로 설정 가능)
	if (Ammo >= AmmoUsedPerShot)
	{
		Ammo -= AmmoUsedPerShot;
		UE_LOG(LogTemp, Warning, TEXT("Shotgun Ammo Remaining: %d"), Ammo);
	}
}*/