#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "T7_CombatComponent.generated.h"

class AT7_Weapon;
class AT7_PlayerCharacter;
class AT7_WeaponHUD;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TEAM7_API UT7_CombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UT7_CombatComponent();

	void EquipWeapon(AT7_Weapon* WeaponToEquip);

	void DropWeapon();

	void SetHUDCrosshairs(float DeltaTime);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	class AT7_WeaponHUD* HUD;
	class AT7_PlayerController* Controller;

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY()
	AT7_PlayerCharacter* Character;

	UPROPERTY()
	AT7_Weapon* EquippedWeapon;

};