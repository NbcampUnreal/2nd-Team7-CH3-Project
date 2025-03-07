﻿#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "T7_CharacterBase.generated.h"

// Player Character, Enemy Character 겹치는 부분 여기다 구현
// 추상 클래스로 상속받아 사용
class UT7_CombatComponent;
class AT7_Weapon;

UCLASS(Abstract)
class TEAM7_API AT7_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AT7_CharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	AT7_Weapon* GetCurrentWeapon() const { return CurrentWeapon; }

	void SetCurrentWeapon(AT7_Weapon* NewWeapon) { CurrentWeapon = NewWeapon; }

	void EquipWeapon(AT7_Weapon* Weapon);

	float GetCurrentHP() const { return CurrentHP; }
	
	float GetMaxHP() const { return MaxHP; }

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Dead();
protected:
	// 적 유닛 무기 셋업, 죽었을때 무기 드랍할 예정이면 Base에서 구현하는게 맞을듯
	
	void FireWeapon();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|CharacerStatus")
	float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|CharacerStatus")
	float CurrentHP = MaxHP;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|CharacerStatus")
	float Armor = 10.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|CharacerStatus")
	float NormalMaxWalkSpeed = 600.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "T7|CharacerStatus")
	float SprintMaxWalkSpeed = NormalMaxWalkSpeed * 1.5;

	UPROPERTY(VisibleAnywhere, Category = "T7|Weapon")
	TObjectPtr<AT7_Weapon> CurrentWeapon = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "T7|Combat")
	TObjectPtr<UT7_CombatComponent> CombatComponent = nullptr;

	const float DamageReduction = Armor / (Armor + 100);
	
};
