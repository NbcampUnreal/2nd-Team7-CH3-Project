// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/T7_Weapon.h"
#include "T7_Shotgun.generated.h"

/**
 * 
 */
UCLASS()
class TEAM7_API AT7_Shotgun : public AT7_Weapon
{
	GENERATED_BODY()

public:
	AT7_Shotgun();
	virtual void Fire() override;

	//virtual void SpendRound() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class AT7_ShotgunProjectile> ShotgunProjectileClass;

	FVector HitTarget;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* ImpactParticles;
};
