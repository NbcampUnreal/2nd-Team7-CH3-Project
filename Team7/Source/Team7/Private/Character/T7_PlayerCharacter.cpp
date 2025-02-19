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


AT7_PlayerCharacter::AT7_PlayerCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	CombatComponent = CreateDefaultSubobject<UT7_CombatComponent>(TEXT("CombatComponent"));
}

void AT7_PlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AT7_PlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AT7_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
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

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AT7_PlayerCharacter::FireWeapon);

	}
}


//  무기 줍기 실행 (E키)
void AT7_PlayerCharacter::PickupWeapon()
{
    if (CombatComponent && OverlappingWeapon)
    {
        OverlappingWeapon->SetPickupWidgetVisibility(false);

        // CombatComponent를 통해 무기 장착
        CombatComponent->EquipWeapon(OverlappingWeapon);

        // 현재 무기 설정 (중요!)
        CurrentWeapon = OverlappingWeapon;

        // 줍기 가능한 무기 초기화
        OverlappingWeapon = nullptr;
    }
}


//  무기 장착
void AT7_PlayerCharacter::OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void AT7_PlayerCharacter::FireWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("FireWeapon() 호출됨!"));

	if (CurrentWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("현재 무기 있음 -> 무기 발사"));
		CurrentWeapon->Fire();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("현재 무기 없음!"));
	}
}