
#include "Weapon/T7_Weapon.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Weapon/T7_Projectile.h"
#include "Camera/PlayerCameraManager.h"
#include "Animation/AnimationAsset.h"
#include "Team7/Public/Character/T7_PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"

AT7_Weapon::AT7_Weapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    SetRootComponent(WeaponMesh);

    WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
    WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    PickupTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("PickupTrigger"));
    PickupTrigger->SetupAttachment(RootComponent);
    PickupTrigger->SetSphereRadius(100.0f);
    PickupTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    PickupTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
    PickupTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    PickupTrigger->OnComponentBeginOverlap.AddDynamic(this, &AT7_Weapon::OnWeaponOverlap);
    PickupTrigger->OnComponentEndOverlap.AddDynamic(this, &AT7_Weapon::OnWeaponEndOverlap);

    PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
    PickupWidget->SetupAttachment(RootComponent);

    // �ʱ� ���� ����
    WeaponState = EWeaponState::EWS_Initial;
    MaxAmmo = 30; 
    Ammo = MaxAmmo;

    UE_LOG(LogTemp, Warning, TEXT("Weapon Spawned! Ammo: %d"), Ammo);
}

void AT7_Weapon::BeginPlay()
{
    Super::BeginPlay();

    PickupWidget->SetVisibility(false);

}

void AT7_Weapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AT7_Weapon::Fire()
{
    if (GetOwner() == nullptr) return;

    if (bIsReloading)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot fire while reloading!"));
        return;
    }

    if (!CanFire())
    {
        UE_LOG(LogTemp, Warning, TEXT("Out of Ammo! Reloading..."));
        Reload();  // �ڵ� ������ ����
        return;
    }

    APlayerController* PlayerController = Cast<APlayerController>(GetOwner()->GetInstigatorController());
    if (PlayerController == nullptr) return;

    UWorld* World = GetWorld();
    if (World == nullptr) return;

    OnWeaponFired.Broadcast();

    FVector MuzzleLocation;
    if (WeaponMesh->DoesSocketExist(FName("MuzzleSocket")))
    {
        MuzzleLocation = WeaponMesh->GetSocketLocation(FName("MuzzleSocket"));
    }
    else
    {
        MuzzleLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
    }

    FRotator MuzzleRotation = PlayerController->PlayerCameraManager->GetCameraRotation();

    if (ProjectileClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

        World->SpawnActor<AT7_Projectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
    }

    if (FireAnimation && WeaponMesh)
    {
        WeaponMesh->PlayAnimation(FireAnimation, false);
    }

    SpendRound();  
}



void AT7_Weapon::SpendRound()
{
    if (Ammo > 0)
    {
        --Ammo;
        UE_LOG(LogTemp, Warning, TEXT("Ammo Remaining: %d"), Ammo); 
    }
}

void AT7_Weapon::Reload()
{
    if (Ammo >= MaxAmmo)
    {
        UE_LOG(LogTemp, Warning, TEXT("Ammo is Full! No need to reload."));
        return;
    }

    if (bIsReloading) return;

    bIsReloading = true;
    UE_LOG(LogTemp, Warning, TEXT("Reloading... Timer Started"));

    GetWorldTimerManager().SetTimer(TimerHandle_Reload, this, &AT7_Weapon::FinishReload, 1.5f, false);

    UE_LOG(LogTemp, Warning, TEXT("Timer Successfully Set!"));
}



void AT7_Weapon::FinishReload()
{
    Ammo = MaxAmmo; 
    bIsReloading = false;
    UE_LOG(LogTemp, Warning, TEXT("Reloaded! Ammo: %d"), Ammo);
}


void AT7_Weapon::OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AT7_PlayerCharacter* PlayerCharacter = Cast<AT7_PlayerCharacter>(OtherActor);
    if (PlayerCharacter)
    {
        PlayerCharacter->OverlappingWeapon = this;
        PickupWidget->SetVisibility(true);  
        UE_LOG(LogTemp, Warning, TEXT("Weapon Overlap Detected: %s"), *GetName());
    



        PickupWidget->SetVisibility(true);  // UI ǥ��
    }
}

void AT7_Weapon::OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    AT7_PlayerCharacter* PlayerCharacter = Cast<AT7_PlayerCharacter>(OtherActor);
    if (PlayerCharacter && PlayerCharacter->OverlappingWeapon == this)
    {
        PlayerCharacter->OverlappingWeapon = nullptr;  // �ݱ� ����
        PickupWidget->SetVisibility(false);  // UI ����
    }
}

void AT7_Weapon::SetWeaponState(EWeaponState NewState)
{
    WeaponState = NewState;
}

void AT7_Weapon::SetPickupWidgetVisibility(bool bVisible)
{
    if (PickupWidget)
    {
        PickupWidget->SetVisibility(bVisible);
    }
}