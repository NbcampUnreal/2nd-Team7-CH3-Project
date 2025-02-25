// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "T7_InputData.generated.h"

class UInputMappingContext;
class UInputAction;

USTRUCT()
struct FT7InputAction
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag::EmptyTag;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputAction = nullptr;
};
UCLASS()
class TEAM7_API UT7_InputData : public UDataAsset
{
	GENERATED_BODY()
public:
	const UInputAction* FindInputActionByTag(const FGameplayTag& Tag) const;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TArray<FT7InputAction> InputActions;
};
