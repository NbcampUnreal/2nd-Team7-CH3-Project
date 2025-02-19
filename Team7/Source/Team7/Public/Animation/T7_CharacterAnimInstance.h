#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "T7_CharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class AT7_CharacterBase;
/**
 * 
 */
UCLASS()
class TEAM7_API UT7_CharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UT7_CharacterAnimInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void NativeInitializeAnimation() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AT7_CharacterBase> Character = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCharacterMovementComponent> MovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Velocity = FVector::ZeroVector;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float GroundSpeed = 0.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bShouldMove = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsFalling = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsEquippedWeapon = false;
};
