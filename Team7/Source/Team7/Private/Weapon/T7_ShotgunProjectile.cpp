#include "Weapon/T7_ShotgunProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AT7_ShotgunProjectile::AT7_ShotgunProjectile()
{
    // 부모 클래스의 기본 설정 유지
    PrimaryActorTick.bCanEverTick = false;

    // 데미지 설정
    ShotgunPelletDamage = 10.0f;

    // 충돌 이벤트 바인딩
    CollisionBox->OnComponentHit.AddDynamic(this, &AT7_ShotgunProjectile::OnHit);

    // 짧은 탄환 수명 (샷건 탄환은 빠르게 사라짐)
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

    Destroy(); // 탄환이 맞으면 사라짐
}
