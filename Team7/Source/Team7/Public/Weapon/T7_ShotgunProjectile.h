
#pragma once

#include "CoreMinimal.h"
#include "Weapon/T7_Projectile.h"
#include "T7_ShotgunProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TEAM7_API AT7_ShotgunProjectile : public AT7_Projectile
{
	GENERATED_BODY()
public:
    AT7_ShotgunProjectile();

protected:
    virtual void BeginPlay() override;

private:


    virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

    // 샷건 탄환이 개별적으로 데미지를 가질 수 있도록 설정
    UPROPERTY(EditAnywhere, Category = "Shotgun")
    float ShotgunPelletDamage = 10.0f;
};
