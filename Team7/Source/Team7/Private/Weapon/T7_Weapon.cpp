
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

    // 초기 상태 설정
    WeaponState = EWeaponState::EWS_Initial;

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
}


void AT7_Weapon::OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AT7_PlayerCharacter* PlayerCharacter = Cast<AT7_PlayerCharacter>(OtherActor);
    if (PlayerCharacter)
    {
        PlayerCharacter->OverlappingWeapon = this;
        PickupWidget->SetVisibility(true);  // UI 표시
    }
}

void AT7_Weapon::OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    AT7_PlayerCharacter* PlayerCharacter = Cast<AT7_PlayerCharacter>(OtherActor);
    if (PlayerCharacter && PlayerCharacter->OverlappingWeapon == this)
    {
        PlayerCharacter->OverlappingWeapon = nullptr;  // 줍기 해제
        PickupWidget->SetVisibility(false);  // UI 숨김
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