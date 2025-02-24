#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T7_Weapon.generated.h"

// �ѱ� �߻� ��������Ʈ
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFired);

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Initial UMETA(DisplayName = "Initial State"),
	EWS_Equipped UMETA(DisplayName = "Equipped"),
	EWS_Dropped UMETA(DisplayName = "Dropped"),

	EWS_Max UMETA(DisplayName = "DefaultMax"),

};
UCLASS()
class TEAM7_API AT7_Weapon : public AActor
{
	GENERATED_BODY()

public:

	AT7_Weapon();
	virtual void Tick(float DeltaTime) override;

	// �ѱ� �߻�
	UFUNCTION(BlueprintCallable)
	void Fire();

	void SetWeaponState(EWeaponState NewState);

	// �ݱ� UI����
	void SetPickupWidgetVisibility(bool bVisible);

protected:

	virtual void BeginPlay() override;


private:

	//����
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	//�浹 ����(���� ȹ��)
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class USphereComponent* PickupTrigger;

	// ���� ����
	UPROPERTY(EditAnywhere, Category = "Weapon")
	EWeaponState WeaponState;

	// ���� �ݱ� UI
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class UWidgetComponent* PickupWidget;

	// źȯ
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AT7_Projectile> ProjectileClass;

	

	// �߻� �ִϸ��̼� 
	UPROPERTY(EditAnywhere, Category = "Weapon")
	class UAnimationAsset* FireAnimation;


	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnWeaponFired OnWeaponFired;

	UFUNCTION()
	void OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:

};