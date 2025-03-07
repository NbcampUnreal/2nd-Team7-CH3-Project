﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/T7_SpawnPoint.h"
#include "GameFramework/GameModeBase.h"
#include "T7_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TEAM7_API AT7_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AT7_GameModeBase();

	virtual void BeginPlay() override;

private:
	void Spawn();
};
