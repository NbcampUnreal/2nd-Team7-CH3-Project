// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/T7_Shotgun.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Character/T7_PlayerCharacter.h"

AT7_Shotgun::AT7_Shotgun()
{
	Damage = 10.0f;

}
void AT7_Shotgun::Fire()
{
	Super::Fire(); // 기본 Fire 기능 실행 (HUD 업데이트, 탄약 감소 등)

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;

	AController* InstigatorController = OwnerPawn->GetController();
	if (!InstigatorController) return;

	// 총구 위치 가져오기
	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName("MuzzleFlash");
	if (!MuzzleFlashSocket) return;

	FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
	FVector MuzzleLocation = SocketTransform.GetLocation();

	UWorld* World = GetWorld();
	if (!World) return;

	// 샷건의 산탄 개수와 퍼짐 정도
	int32 NumPellets = 8;  // 탄알 개수
	float SpreadAngle = 10.0f; // 퍼지는 각도 (도 단위)

	for (int32 i = 0; i < NumPellets; i++)
	{
		// 카메라 방향에서 Spread 적용
		FVector ShootDirection = (HitTarget - MuzzleLocation).GetSafeNormal();
		ShootDirection = FMath::VRandCone(ShootDirection, FMath::DegreesToRadians(SpreadAngle)); // 랜덤 방향 적용

		FVector End = MuzzleLocation + (ShootDirection * 5000.0f); // 사거리 설정

		// 히트 결과
		FHitResult FireHit;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		QueryParams.AddIgnoredActor(GetOwner());

		// LineTrace 실행
		if (World->LineTraceSingleByChannel(FireHit, MuzzleLocation, End, ECC_Visibility, QueryParams))
		{
			if (FireHit.bBlockingHit)
			{
				// 데미지 적용
				AActor* HitActor = FireHit.GetActor();
				if (HitActor && HasAuthority())
				{
					UGameplayStatics::ApplyDamage(HitActor, Damage / NumPellets, InstigatorController, this, UDamageType::StaticClass());
				}

				// 피격 이펙트 추가
				if (ImpactParticles)
				{
					UGameplayStatics::SpawnEmitterAtLocation(World, ImpactParticles, FireHit.ImpactPoint, FireHit.ImpactNormal.Rotation());
				}
			}
		}
	}
}

void AT7_Shotgun::SpendRound()
{
	int32 AmmoUsedPerShot = 1; // 샷건이 한 번 쏠 때 사용하는 탄약 개수 (필요하면 2~3으로 설정 가능)
	if (Ammo >= AmmoUsedPerShot)
	{
		Ammo -= AmmoUsedPerShot;
		UE_LOG(LogTemp, Warning, TEXT("Shotgun Ammo Remaining: %d"), Ammo);
	}
}