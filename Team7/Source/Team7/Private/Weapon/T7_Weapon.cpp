
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
#include "Team7/Public/System/T7_GameStateBase.h"
#include "DrawDebugHelpers.h"  
#include "particles/ParticleSystemComponent.h"

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
    if (bIsReloading) return;
    if (!CanFire())
    {
        Reload();
        return;
    }

    APlayerController* PlayerController = Cast<APlayerController>(GetOwner()->GetInstigatorController());
    if (!PlayerController) return;

    UWorld* World = GetWorld();
    if (World == nullptr) return;

    OnWeaponFired.Broadcast();

    FVector MuzzleLocation = WeaponMesh->GetSocketLocation(FName("MuzzleSocket"));
    FVector ForwardVector = WeaponMesh->GetSocketRotation(FName("MuzzleSocket")).Vector();
    MuzzleLocation += ForwardVector * 20.0f;  

    FVector CameraLocation;
    FRotator CameraRotation;
    PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

    FVector EndTrace = CameraLocation + (CameraRotation.Vector() * 5000.0f);
    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);
    QueryParams.AddIgnoredActor(GetOwner());

    if (World->LineTraceSingleByChannel(HitResult, CameraLocation, EndTrace, ECC_Visibility, QueryParams))
    {
        EndTrace = HitResult.ImpactPoint;
    }

    FVector FireDirection = (EndTrace - MuzzleLocation).GetSafeNormal();

    DrawDebugLine(World, MuzzleLocation, EndTrace, FColor::Red, false, 2.0f, 0, 2.0f);

    if (ProjectileClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        AT7_Projectile* Projectile = World->SpawnActor<AT7_Projectile>(
            ProjectileClass, MuzzleLocation, FireDirection.Rotation(), SpawnParams);

        if (Projectile)
        {
            

            UE_LOG(LogTemp, Warning, TEXT("Projectile Spawned at: %s"), *MuzzleLocation.ToString());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Projectile Spawn Failed!"));
        }
    }

    SpawnBeamEffect(MuzzleLocation, EndTrace);

    if (FireAnimation && WeaponMesh)
    {
        WeaponMesh->PlayAnimation(FireAnimation, false);
    }

    SpendRound();
    UpdateAmmoHUD();
}

void AT7_Weapon::SpawnBeamEffect(FVector Start, FVector End)
{
    if (!BeamParticles) return; 

    UWorld* World = GetWorld();
    if (!World) return;

    UParticleSystemComponent* Beam = UGameplayStatics::SpawnEmitterAtLocation(World, BeamParticles, Start);
    if (Beam)
    {
        Beam->SetVectorParameter(FName("Target"), End);
    }
}



void AT7_Weapon::SpendRound()
{
    if (Ammo > 0)
    {
        --Ammo;
        
    }
}

void AT7_Weapon::Reload()
{
    if (Ammo >= MaxAmmo)
    {
        
        return;
    }

    if (bIsReloading) return;

    bIsReloading = true;
  

    if (ReloadAnimation && WeaponMesh)
    {
        WeaponMesh->PlayAnimation(ReloadAnimation, false);
    }
    GetWorldTimerManager().SetTimer(TimerHandle_Reload, this, &AT7_Weapon::FinishReload, 1.5f, false);

}



void AT7_Weapon::FinishReload()
{
    if (Ammo < MaxAmmo)  // 이미 최대 탄약이면 변경 안 함
    {
        Ammo = MaxAmmo;
    }

    bIsReloading = false;

    UpdateAmmoHUD();
}

void AT7_Weapon::UpdateAmmoHUD()
{
    AT7_GameStateBase* GameState = GetWorld() ? GetWorld()->GetGameState<AT7_GameStateBase>() : nullptr;
    if (GameState)
    {
        int32 CurrentAmmo = Ammo;
        int32 MaxClipAmmo = MaxAmmo;  


        GameState->UpdateWeaponInfo(WeaponIcon, WeaponName, CurrentAmmo, MaxClipAmmo);
    }
}

void AT7_Weapon::OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AT7_PlayerCharacter* PlayerCharacter = Cast<AT7_PlayerCharacter>(OtherActor);
    if (PlayerCharacter)
    {
        PlayerCharacter->OverlappingWeapon = this;
        PickupWidget->SetVisibility(true);

        //UpdateAmmoHUD();
    }
}

void AT7_Weapon::OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    AT7_PlayerCharacter* PlayerCharacter = Cast<AT7_PlayerCharacter>(OtherActor);
    if (PlayerCharacter && PlayerCharacter->OverlappingWeapon == this)
    {
        PlayerCharacter->OverlappingWeapon = nullptr;
        PickupWidget->SetVisibility(false);

        //AT7_GameStateBase* GameState = GetWorld() ? GetWorld()->GetGameState<AT7_GameStateBase>() : nullptr;
        //if (GameState)
        //{
        //    GameState->UpdateWeaponInfo(nullptr, TEXT(""), 0, 0);  // UI 숨김
        //}
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

