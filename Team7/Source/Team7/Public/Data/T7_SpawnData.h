// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "T7_SpawnData.generated.h"

UCLASS()
class TEAM7_API UT7_SpawnData : public UDataAsset
{
	GENERATED_BODY()

public:
	UClass* FindClassByTag(const FGameplayTag& Tag);
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, TSubclassOf<AActor>> SpawnDataMap;
};
