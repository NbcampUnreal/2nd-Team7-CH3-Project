// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/T7_SpawnData.h"

UClass* UT7_SpawnData::FindClassByTag(const FGameplayTag& Tag)
{
	if (SpawnDataMap[Tag])
	{
		return SpawnDataMap[Tag].Get();	
	}
	UE_LOG(LogTemp,Error,TEXT("Can't find BP Class for ClassTag [%s]"), *Tag.ToString());
	return nullptr;
}
