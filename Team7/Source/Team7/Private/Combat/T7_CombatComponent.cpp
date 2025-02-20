
#include "Combat/T7_CombatComponent.h"
#include "Team7/Public/Character/T7_PlayerCharacter.h"
#include "Weapon/T7_Weapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UT7_CombatComponent::UT7_CombatComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}


void UT7_CombatComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<AT7_PlayerCharacter>(GetOwner());
}


void UT7_CombatComponent::EquipWeapon(AT7_Weapon* WeaponToEquip)
{
    if (Character == nullptr || WeaponToEquip == nullptr) return;

    // 기존 무기 버리기
    DropWeapon();

    EquippedWeapon = WeaponToEquip;
    EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);

    const USkeletalMeshSocket* HandSocket = Character->GetMesh()->GetSocketByName(FName("RightHandSocket"));
    if (HandSocket)
    {
        HandSocket->AttachActor(EquippedWeapon, Character->GetMesh());
    }

    // 무기 소유자 설정
    EquippedWeapon->SetOwner(Character);
    Character->GetCharacterMovement()->bOrientRotationToMovement = false;
    Character->bUseControllerRotationYaw = true;
    Character->SetCurrentWeapon(EquippedWeapon);  
}


void UT7_CombatComponent::DropWeapon()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		EquippedWeapon->SetActorEnableCollision(true);
		EquippedWeapon = nullptr;
	}
}