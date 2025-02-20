#include "Animation/T7_CharacterAnimInstance.h"

#include "Character/T7_CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UT7_CharacterAnimInstance::UT7_CharacterAnimInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UT7_CharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<AT7_CharacterBase>(TryGetPawnOwner());
	if(Character)
	{
		MovementComponent = Character->GetCharacterMovement();
	}
}

void UT7_CharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(Character == nullptr)
	{
		return;
	}
	if(MovementComponent == nullptr)
	{
		return;
	}
	Velocity = MovementComponent->Velocity;
	GroundSpeed = Velocity.Size2D();
	bShouldMove = (GroundSpeed > 3.0f && MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector);
	bIsFalling = MovementComponent->IsFalling();
}