#pragma once

#include "CoreMinimal.h"
#include "Team7/Public/Character/T7_CharacterBase.h"
#include "T7_PlayerCharacter.generated.h"

class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;

struct FInputActionValue;

UCLASS()
class TEAM7_API AT7_PlayerCharacter : public AT7_CharacterBase
{
	GENERATED_BODY()

public:
	AT7_PlayerCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void PickupWeapon();

	void DropWeapon();
	void ReloadWeapon();

	void StartSprint();

	void StopSprint();

	void StartAim();

	void StopAim();

	void SwitchCamera();

public:
	//  줍기 가능한 무기
	UPROPERTY(VisibleAnywhere, Category = "T7|Weapon")
	AT7_Weapon* OverlappingWeapon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|Input")
	TObjectPtr<UInputAction> ReloadAction = nullptr;

private:
	UPROPERTY(VisibleAnywhere, Category = "T7|Camera")
	TObjectPtr<USpringArmComponent> TPSSpringArmComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "T7|Camera")
	TObjectPtr<USpringArmComponent> FPSSpringArmComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "T7|Camera")
	TObjectPtr<UCameraComponent> TPSCameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "T7|Camera")
	TObjectPtr<UCameraComponent> FPSCameraComponent = nullptr;

	bool bUseTPSCamera = true;

	//  무기 트리거 감지를 위한 함수
	UFUNCTION()
	void OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                     const FHitResult& SweepResult);

	UFUNCTION()
	void OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
