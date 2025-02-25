// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "T7_DataAssets.generated.h"

USTRUCT()
struct FAssetEntry
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AssetTag;

	UPROPERTY(EditDefaultsOnly)
	FSoftObjectPath AssetPath;
};

USTRUCT()
struct FAssetContainer
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FAssetEntry> AssetEntries;
};
UCLASS()
class TEAM7_API UT7_DataAssets : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	
	FSoftObjectPath GetAssetPathByTag(const FGameplayTag& InTag);
private:
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, FAssetContainer> NameToLoadedAsset;

	UPROPERTY(VisibleAnywhere)
	TMap<FGameplayTag, FSoftObjectPath> AssetTagToPath;
	
};
