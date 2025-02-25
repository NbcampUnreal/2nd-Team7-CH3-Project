// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "T7_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TEAM7_API UT7_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UT7_GameInstance();

private:
	virtual void Init() override;
	
};
