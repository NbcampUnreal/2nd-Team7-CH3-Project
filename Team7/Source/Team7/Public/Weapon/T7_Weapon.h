
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T7_Weapon.generated.h"

// 총기 발사 델리게이트
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
	
	UFUNCTION(BlueprintCallable)
	void Fire();

	void SetWeaponState(EWeaponState NewState);

	void SetPickupWidgetVisibility(bool bVisible);
protected:

	virtual void BeginPlay() override;

	
private:

	//무기
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	//충돌 감지(무기 획득)
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class USphereComponent* PickupTrigger;

	// 현재 무기
	UPROPERTY(EditAnywhere, Category = "Weapon")
	EWeaponState WeaponState;

	// 무기 줍기 UI
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class UWidgetComponent* PickupWidget;

	// 탄환
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AT7_Projectile> ProjectileClass;

	// 발사 사운드 
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	USoundBase* FireSound;

	// 발사 애니메이션 
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UAnimMontage* FireAnimation;

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
