// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/T7_InputData.h"

const UInputAction* UT7_InputData::FindInputActionByTag(const FGameplayTag& Tag) const
{
	for(FT7InputAction Action : InputActions)
	{
		if(Action.InputAction && Action.InputTag == Tag)
		{
			return Action.InputAction.Get();
		}
	}
	UE_LOG(LogTemp,Error,TEXT("Can't find InputAction for InputTag [%s]"), *Tag.ToString());
	return nullptr;
}
