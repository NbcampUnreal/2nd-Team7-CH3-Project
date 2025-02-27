
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

    // ���� źȯ�� ���������� �������� ���� �� �ֵ��� ����
    UPROPERTY(EditAnywhere, Category = "Shotgun")
    float ShotgunPelletDamage = 10.0f;
};
