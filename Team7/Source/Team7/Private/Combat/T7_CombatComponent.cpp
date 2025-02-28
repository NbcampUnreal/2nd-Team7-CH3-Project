
#include "Combat/T7_CombatComponent.h"
#include "Team7/Public/Character/T7_PlayerCharacter.h"
#include "Weapon/T7_Weapon.h"
#include "PlayerController/T7_PlayerController.h"
#include "HUD/T7_WeaponHud.h"
#include "Team7/Public/System/T7_GameStateBase.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UT7_CombatComponent::UT7_CombatComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
}

void UT7_CombatComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<AT7_PlayerCharacter>(GetOwner());
}


void UT7_CombatComponent::EquipWeapon(AT7_Weapon* WeaponToEquip)
{
	if (Character == nullptr || WeaponToEquip == nullptr) return;

	DropWeapon();  // 기존 무기 버리기

	EquippedWeapon = WeaponToEquip;
	EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);

	const USkeletalMeshSocket* HandSocket = Character->GetMesh()->GetSocketByName(FName("RightHandSocket"));
	if (HandSocket)
	{
		HandSocket->AttachActor(EquippedWeapon, Character->GetMesh());
	}

	EquippedWeapon->SetOwner(Character);
	Character->GetCharacterMovement()->bOrientRotationToMovement = false;
	Character->bUseControllerRotationYaw = true;

	if (AGameStateBase* GameState = UGameplayStatics::GetGameState(GetWorld()))
	{
		if (AT7_GameStateBase* T7_GameStateBase = Cast<AT7_GameStateBase>(GameState))
		{
			T7_GameStateBase->UpdateWeaponInfo(EquippedWeapon->WeaponIcon, EquippedWeapon->WeaponName, EquippedWeapon->GetAmmo(), EquippedWeapon->GetMaxAmmo());
		}
	}
}


void UT7_CombatComponent::DropWeapon()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		EquippedWeapon->SetActorEnableCollision(true);
		EquippedWeapon = nullptr;
	}

	if (AGameStateBase* GameState = UGameplayStatics::GetGameState(GetWorld()))
	{
		if (AT7_GameStateBase* T7_GameStateBase = Cast<AT7_GameStateBase>(GameState))
		{
			T7_GameStateBase->UpdateWeaponInfo(nullptr, TEXT("Knife"), 0, 0);
		}
	}
}

void UT7_CombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    SetHUDCrosshairs(DeltaTime);
}

void UT7_CombatComponent::SetHUDCrosshairs(float DeltaTime)
{
	if (Character == nullptr || Character->Controller == nullptr) return;

	Controller = Controller == nullptr ? Cast<AT7_PlayerController>(Character->Controller) : Controller;
	if (Controller)
	{
		HUD = HUD == nullptr ? Cast<AT7_WeaponHUD>(Controller->GetHUD()) : HUD;
		if (HUD)
		{
			FHUDPackage HUDPackage;
			if (EquippedWeapon)
			{
				HUDPackage.CrosshairsCenter = EquippedWeapon->CrosshairsCenter;
				HUDPackage.CrosshairsLeft = EquippedWeapon->CrosshairsLeft;
				HUDPackage.CrosshairsRight = EquippedWeapon->CrosshairsRight;
				HUDPackage.CrosshairsBottom = EquippedWeapon->CrosshairsBottom;
				HUDPackage.CrosshairsTop = EquippedWeapon->CrosshairsTop;
			}
			else
			{
				HUDPackage.CrosshairsCenter = nullptr;
				HUDPackage.CrosshairsLeft = nullptr;
				HUDPackage.CrosshairsRight = nullptr;
				HUDPackage.CrosshairsBottom = nullptr;
				HUDPackage.CrosshairsTop = nullptr;
			}
			HUD->SetHUDPackage(HUDPackage);
		}
	}
}

