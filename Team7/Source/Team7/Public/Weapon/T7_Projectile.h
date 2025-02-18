#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T7_Projectile.generated.h"

UCLASS()
class TEAM7_API AT7_Projectile : public AActor
{
	GENERATED_BODY()

public:
	AT7_Projectile();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	// 탄환 충돌 감지 박스
	UPROPERTY(EditAnywhere, Category = "Components")
	class UBoxComponent* CollisionBox;

	// 탄환 이동 컴포넌트
	UPROPERTY(EditAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement;

	// 충돌 시 실행될 함수
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
