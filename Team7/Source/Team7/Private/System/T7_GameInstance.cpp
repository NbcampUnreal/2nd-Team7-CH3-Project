// Fill out your copyright notice in the Description page of Project Settings.


#include "System/T7_GameInstance.h"
#include "System/T7_AssetManager.h"

UT7_GameInstance::UT7_GameInstance()
{
}

void UT7_GameInstance::Init()
{
	Super::Init();
	UT7_AssetManager::Get().InitializeDataAssets();
}
