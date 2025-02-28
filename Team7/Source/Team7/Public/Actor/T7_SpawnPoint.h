// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T7_SpawnPoint.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class ESpawnType : uint8
{
	None,
	Enemy_Normal,
	Enemy_Elite,
	Enemy_Boss,
	ItemBox_Weapon,
	ItemBox_Medikit,
	Weapon,
};
UCLASS()
class TEAM7_API AT7_SpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	AT7_SpawnPoint();

	UPROPERTY(EditAnywhere, Category="T7|SpawnType")
	ESpawnType SpawnType = ESpawnType::None;
	
protected:
	virtual void BeginPlay() override;

private:
	void Register();

};
