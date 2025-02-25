// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/AssetManager.h"
#include "T7_AssetManager.generated.h"

class UT7_DataAssets;
/**
 * 
 */
UCLASS()
class TEAM7_API UT7_AssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	UT7_AssetManager();

	static UT7_AssetManager& Get();

	static UObject* GetAssetByTag(const FGameplayTag& Tag);

	static void LoadAssetSynchronouslyByTag(const FGameplayTag& Tag);

	void InitializeDataAssets();

private:
	virtual void StartInitialLoading() override;
	
	void AddLoadedAsset(UObject* Asset);
	
	UPROPERTY()
	TObjectPtr<UT7_DataAssets> LoadedDataAssets = nullptr;

	// GC 수집 방지
	UPROPERTY()
	TArray<TObjectPtr<UObject>> LoadedAssets;
};
