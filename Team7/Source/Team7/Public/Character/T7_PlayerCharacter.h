#pragma once

#include "CoreMinimal.h"
#include "T7_CharacterBase.h"
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
	AT7_PlayerCharacter();

protected:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
protected:
	// 전역적인 움직임(메뉴 이동 등)은 PlayerController의 SetupInputComponent()에서
	// 플레이어 캐릭터의 움직임은 Character의 SetupPlayerInputComponent()에서 처리하는게 일반적
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|Input")
	UInputMappingContext* DefaultMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|Input")
	UInputAction* MoveAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|Input")
	UInputAction* LookAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|Input")
	UInputAction* JumpAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|Input")
	UInputAction* SprintAction = nullptr;
	
private:
	UPROPERTY(VisibleAnywhere, Category="T7|Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category="T7|Camera")
	TObjectPtr<UCameraComponent> CameraComponent = nullptr;
};
