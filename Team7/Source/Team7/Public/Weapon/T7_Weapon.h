#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T7_Weapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFired);

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
    EWS_Initial UMETA(DisplayName = "Initial State"),
    EWS_Equipped UMETA(DisplayName = "Equipped"),
    EWS_Dropped UMETA(DisplayName = "Dropped"),
    EWS_Max UMETA(DisplayName = "DefaultMax"),
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    EWT_AssaultRifle UMETA(DisplayName = "Assault Rifle"),
    EWT_Pistol UMETA(DisplayName = "Pistol"),
    EWT_Shotgun UMETA(DisplayName = "Shotgun"),
    EWT_Sniper UMETA(DisplayName = "Sniper"),
    EWT_Max UMETA(DisplayName = "DefaultMax"),
};

UCLASS()
class TEAM7_API AT7_Weapon : public AActor
{
    GENERATED_BODY()

public:
    AT7_Weapon();
    virtual void Tick(float DeltaTime) override;

    FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

    UFUNCTION(BlueprintCallable)
    virtual void Fire();

    UPROPERTY(EditAnywhere, Category = "Crosshairs")
    class UTexture2D* CrosshairsCenter;

    UPROPERTY(EditAnywhere, Category = "Crosshairs")
    UTexture2D* CrosshairsLeft;

    UPROPERTY(EditAnywhere, Category = "Crosshairs")
    UTexture2D* CrosshairsRight;

    UPROPERTY(EditAnywhere, Category = "Crosshairs")
    UTexture2D* CrosshairsTop;

    UPROPERTY(EditAnywhere, Category = "Crosshairs")
    UTexture2D* CrosshairsBottom;

    UPROPERTY(EditAnywhere, Category = "Weapon Info")
    FString WeaponName;  // 무기 이름

    UPROPERTY(EditAnywhere, Category = "Weapon Info")
    UTexture2D* WeaponIcon;  // 무기 아이콘 이미지

    UPROPERTY(EditAnywhere, Category = "Weapon Ammo")
    int32 MaxAmmo;

    UPROPERTY(EditAnywhere, Category = "Weapon Ammo")
    int32 Ammo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float Damage = 20.0f;  // 기본 데미지 값

    float GetDamage() const { return Damage; } 

    FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }

    

protected:
    virtual void BeginPlay() override;
    FTimerHandle TimerHandle_Reload;

    // 무기 타입 추가
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    EWeaponType WeaponType;

    UPROPERTY(EditAnywhere)
    class UParticleSystem* BeamParticles;

    void SpawnBeamEffect(FVector Start, FVector End);
private:
    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    class USphereComponent* PickupTrigger;

    UPROPERTY(EditAnywhere, Category = "Weapon")
    EWeaponState WeaponState;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    TSubclassOf<class AT7_Projectile> ProjectileClass;

    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    class UWidgetComponent* PickupWidget;

    UPROPERTY(EditAnywhere, Category = "Weapon")
    class UAnimationAsset* FireAnimation;

    UPROPERTY(EditAnywhere, Category = "Weapon")
    class UAnimationAsset* ReloadAnimation;

    bool bIsReloading = false;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
    FOnWeaponFired OnWeaponFired;

    UFUNCTION()
    void OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
    int32 GetAmmo() const { return Ammo; }
    int32 GetMaxAmmo() const { return MaxAmmo; }
    bool CanFire() const { return Ammo > 0; }

    void UpdateAmmoHUD();
    void SetWeaponState(EWeaponState NewState);

    void SetPickupWidgetVisibility(bool bVisible);

    void Reload();

    void SpendRound();

    void FinishReload();
};
