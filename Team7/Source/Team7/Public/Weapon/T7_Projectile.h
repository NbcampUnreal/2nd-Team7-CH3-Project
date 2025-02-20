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
	// źȯ �浹 ���� �ڽ�
	UPROPERTY(EditAnywhere, Category = "Components")
	class UBoxComponent* CollisionBox;

	// źȯ �̵� ������Ʈ
	UPROPERTY(EditAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement;

	// �浹 �� ����� �Լ�
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
