// Fill out your copyright notice in the Description page of Project Settings.


#include "System/T7_AssetManager.h"

#include "Data/T7_DataAssets.h"

UT7_AssetManager::UT7_AssetManager()
{
}

UT7_AssetManager& UT7_AssetManager::Get()
{
	check(GEngine);
	if (UT7_AssetManager* Singleton = Cast<UT7_AssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}
	UE_LOG(LogTemp, Fatal, TEXT("Can't Find BN_AssetManager"));
	return *NewObject<UT7_AssetManager>();
}


UObject* UT7_AssetManager::GetAssetByTag(const FGameplayTag& Tag)
{
	UT7_DataAssets* DataAsset = Get().LoadedDataAssets;
	check(DataAsset);
	UObject* LoadedAsset = nullptr;
	const FSoftObjectPath& AssetPath = DataAsset->GetAssetPathByTag(Tag);
	if (AssetPath.IsValid())
	{
		LoadedAsset = AssetPath.ResolveObject();
		if (LoadedAsset == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Attempted sync loading because asset had not not loaded yet.[%s]"),
			       *AssetPath.ToString());

			LoadedAsset = AssetPath.TryLoad();
		}
	}
	return LoadedAsset;
}

void UT7_AssetManager::LoadAssetSynchronouslyByTag(const FGameplayTag& InTag)
{
	UT7_DataAssets* Asset = Get().LoadedDataAssets;
	check(Asset);
	const FSoftObjectPath& AssetPath = Asset->GetAssetPathByTag(InTag);
	UObject* LoadedAsset = AssetPath.ResolveObject();
	if (LoadedAsset == nullptr)
	{
		if (IsInitialized())
		{
			LoadedAsset = GetStreamableManager().LoadSynchronous(AssetPath, false);
		}
		else
		{
			LoadedAsset = AssetPath.TryLoad();
		}
	}
	if (LoadedAsset)
	{
		Get().AddLoadedAsset(LoadedAsset);
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Failed to load asset [%s]"), *InTag.ToString());
	}
}

void UT7_AssetManager::InitializeDataAssets()
{
	UT7_DataAssets* DataAssets = nullptr;
	FPrimaryAssetType PrimaryAssetType(UT7_DataAssets::StaticClass()->GetFName());
	TSharedPtr<FStreamableHandle> Handle = LoadPrimaryAssetsWithType(PrimaryAssetType);
	if (Handle.IsValid())
	{
		Handle->WaitUntilComplete(0.f, false);
		DataAssets = Cast<UT7_DataAssets>(Handle->GetLoadedAsset());
	}
	if (DataAssets)
	{
		LoadedDataAssets = DataAssets;
	}
}

void UT7_AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

}

void UT7_AssetManager::AddLoadedAsset(UObject* Asset)
{
	if (Asset)
	{
		LoadedAssets.Emplace(Asset);
	}
}
