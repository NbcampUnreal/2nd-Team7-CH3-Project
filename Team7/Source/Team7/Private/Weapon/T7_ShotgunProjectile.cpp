#include "Weapon/T7_ShotgunProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AT7_ShotgunProjectile::AT7_ShotgunProjectile()
{
    // �θ� Ŭ������ �⺻ ���� ����
    PrimaryActorTick.bCanEverTick = false;

    // ������ ����
    ShotgunPelletDamage = 10.0f;

    // �浹 �̺�Ʈ ���ε�
    //CollisionBox->OnComponentHit.AddDynamic(this, &AT7_ShotgunProjectile::OnHit);

    // ª�� źȯ ���� (���� źȯ�� ������ �����)
    SetLifeSpan(1.5f);
}

void AT7_ShotgunProjectile::BeginPlay()
{
    Super::BeginPlay();
}

void AT7_ShotgunProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor == nullptr || OtherActor == this) return;

    UGameplayStatics::ApplyDamage(OtherActor, ShotgunPelletDamage, GetInstigatorController(), this, UDamageType::StaticClass());

    Destroy();
}
