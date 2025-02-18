#include "Team7/Public/Character/T7_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Weapon/T7_Weapon.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Combat/T7_CombatComponent.h"
#include "PlayerController/T7_PlayerController.h"


AT7_PlayerCharacter::AT7_PlayerCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	TPSSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("TPSSpringArmComponent"));
	TPSSpringArmComponent->bUsePawnControlRotation = true;
	TPSSpringArmComponent->SetupAttachment(RootComponent);

	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPSCameraComponent"));
	TPSCameraComponent->bUsePawnControlRotation = false;
	TPSCameraComponent->SetupAttachment(TPSSpringArmComponent, USpringArmComponent::SocketName);

	FPSSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("FPSSpringArmComponent"));
	FPSSpringArmComponent->SetupAttachment(GetMesh(), TEXT("camera_socket"));
	FPSSpringArmComponent->TargetArmLength = 0.0f;
	
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCameraComponent"));
	FPSCameraComponent->bUsePawnControlRotation = true;
	FPSCameraComponent->SetupAttachment(FPSSpringArmComponent);

	CombatComponent = CreateDefaultSubobject<UT7_CombatComponent>(TEXT("CombatComponent"));

	GetCharacterMovement()->MaxWalkSpeed = NormalMaxWalkSpeed;
}

void AT7_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);

		EnhancedInputComponent->BindAction(PickupAction, ETriggerEvent::Started, this, &ThisClass::PickupWeapon);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ThisClass::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ThisClass::StopSprint);

		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ThisClass::StartAim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ThisClass::StopAim);
		
		EnhancedInputComponent->BindAction(SwitchCameraAction, ETriggerEvent::Completed, this, &ThisClass::SwitchCamera);
	}
}

void AT7_PlayerCharacter::Move(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AT7_PlayerCharacter::Look(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

//  무기 줍기 실행 (E키)
void AT7_PlayerCharacter::PickupWeapon()
{
	if (CombatComponent && OverlappingWeapon)
	{
		//  무기를 주운 순간 UI 숨기기
		OverlappingWeapon->SetPickupWidgetVisibility(false);

		//  CombatComponent를 통해 무기 장착
		CombatComponent->EquipWeapon(OverlappingWeapon);

		//  줍기 가능한 무기 초기화
		OverlappingWeapon = nullptr;
	}
}

void AT7_PlayerCharacter::EquipWeapon(AT7_Weapon* Weapon)
{
}

void AT7_PlayerCharacter::DropWeapon()
{
}

void AT7_PlayerCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintMaxWalkSpeed;
}

void AT7_PlayerCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = NormalMaxWalkSpeed;
}

void AT7_PlayerCharacter::StartAim()
{
	bUseTPSCamera = false;
	SwitchCamera();
}

void AT7_PlayerCharacter::StopAim()
{
	bUseTPSCamera = true;
	SwitchCamera();
}

void AT7_PlayerCharacter::SwitchCamera()
{
	// Aim 이외에도 특정 키(지금은 T)를 눌렀을 때 시점 변환을 Toggle하기 위해 Input Bool 값으로 처리하지 않음.
	if(bUseTPSCamera)
	{
		TPSCameraComponent->SetActive(true);
		FPSCameraComponent->SetActive(false);
		bUseControllerRotationPitch = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
	else
	{
		TPSCameraComponent->SetActive(false);
		FPSCameraComponent->SetActive(true);
		bUseControllerRotationPitch = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	// Toggle
	bUseTPSCamera = !bUseTPSCamera;
}

//  무기 장착
void AT7_PlayerCharacter::OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                          const FHitResult& SweepResult)
{
	AT7_Weapon* Weapon = Cast<AT7_Weapon>(OtherActor);
	if (Weapon)
	{
		OverlappingWeapon = Weapon;
	}
}

//  무기와 멀어졌을 때 (줍기 불가능)
void AT7_PlayerCharacter::OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AT7_Weapon* Weapon = Cast<AT7_Weapon>(OtherActor);
	if (Weapon && Weapon == OverlappingWeapon)
	{
		OverlappingWeapon = nullptr;
	}
}
