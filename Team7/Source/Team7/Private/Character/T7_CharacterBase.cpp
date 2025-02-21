#include "Team7/Public/Character/T7_CharacterBase.h"
#include "Combat/T7_CombatComponent.h"
#include "Team7/Public/Combat/T7_CombatComponent.h"
#include "Team7/Public/Weapon/T7_Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"

AT7_CharacterBase::AT7_CharacterBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CombatComponent = CreateDefaultSubobject<UT7_CombatComponent>(TEXT("CombatComponent"));
	GetCharacterMovement()->MaxWalkSpeed = NormalMaxWalkSpeed;
}
