// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/T7_DataAssets.h"
#include "UObject/ObjectSaveContext.h"

void UT7_DataAssets::PreSave(FObjectPreSaveContext SaveContext)
{
	Super::PreSave(SaveContext);
	
	AssetTagToPath.Empty();
	NameToLoadedAsset.KeySort([](const FName& Lhs, const FName& Rhs)
	{
		return (Lhs.Compare(Rhs) < 0);
	});
	
	for(const TTuple<FName, FAssetContainer>& Pair : NameToLoadedAsset)
	{
		const FAssetContainer& AssetContainer = Pair.Value;
		for(FAssetEntry AssetEntry : AssetContainer.AssetEntries)
		{
			AssetTagToPath.Emplace(AssetEntry.AssetTag, AssetEntry.AssetPath);
		}
	}
}

FSoftObjectPath UT7_DataAssets::GetAssetPathByTag(const FGameplayTag& InTag)
{
	FSoftObjectPath* AssetPath = AssetTagToPath.Find(InTag);
	ensureAlwaysMsgf(AssetPath, TEXT("Can't find Asset path from Asset Tag [%s]."), *InTag.ToString());
	return *AssetPath;
}
