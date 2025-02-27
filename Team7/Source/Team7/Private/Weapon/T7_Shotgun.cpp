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
	Super::Fire(); // �⺻ Fire ��� ���� (HUD ������Ʈ, ź�� ���� ��)

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;

	AController* InstigatorController = OwnerPawn->GetController();
	if (!InstigatorController) return;

	// �ѱ� ��ġ ��������
	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName("MuzzleFlash");
	if (!MuzzleFlashSocket) return;

	FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
	FVector MuzzleLocation = SocketTransform.GetLocation();

	UWorld* World = GetWorld();
	if (!World) return;

	// ������ ��ź ������ ���� ����
	int32 NumPellets = 8;  // ź�� ����
	float SpreadAngle = 10.0f; // ������ ���� (�� ����)

	for (int32 i = 0; i < NumPellets; i++)
	{
		// ī�޶� ���⿡�� Spread ����
		FVector ShootDirection = (HitTarget - MuzzleLocation).GetSafeNormal();
		ShootDirection = FMath::VRandCone(ShootDirection, FMath::DegreesToRadians(SpreadAngle)); // ���� ���� ����

		FVector End = MuzzleLocation + (ShootDirection * 5000.0f); // ��Ÿ� ����

		// ��Ʈ ���
		FHitResult FireHit;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		QueryParams.AddIgnoredActor(GetOwner());

		// LineTrace ����
		if (World->LineTraceSingleByChannel(FireHit, MuzzleLocation, End, ECC_Visibility, QueryParams))
		{
			if (FireHit.bBlockingHit)
			{
				// ������ ����
				AActor* HitActor = FireHit.GetActor();
				if (HitActor && HasAuthority())
				{
					UGameplayStatics::ApplyDamage(HitActor, Damage / NumPellets, InstigatorController, this, UDamageType::StaticClass());
				}

				// �ǰ� ����Ʈ �߰�
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
	int32 AmmoUsedPerShot = 1; // ������ �� �� �� �� ����ϴ� ź�� ���� (�ʿ��ϸ� 2~3���� ���� ����)
	if (Ammo >= AmmoUsedPerShot)
	{
		Ammo -= AmmoUsedPerShot;
		UE_LOG(LogTemp, Warning, TEXT("Shotgun Ammo Remaining: %d"), Ammo);
	}
}