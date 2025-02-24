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

	//  줍기 가능한 무기
	UPROPERTY(VisibleAnywhere, Category = "T7|Weapon")
	AT7_Weapon* OverlappingWeapon = nullptr;

protected:

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

	// 전역적인 움직임(메뉴 이동 등)은 PlayerController의 SetupInputComponent()에서
	// 플레이어 캐릭터의 움직임은 Character의 SetupPlayerInputComponent()에서 처리하는게 일반적
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|Input")
	TObjectPtr<UInputAction> MoveAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|Input")
	TObjectPtr<UInputAction> LookAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|Input")
	TObjectPtr<UInputAction> JumpAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|Input")
	TObjectPtr<UInputAction> SprintAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|Input")
	TObjectPtr<UInputAction> PickupAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|Input")
	TObjectPtr<UInputAction> FireAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|Input")
	TObjectPtr<UInputAction> AimAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|Input")
	TObjectPtr<UInputAction> SwitchCameraAction = nullptr;

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
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
