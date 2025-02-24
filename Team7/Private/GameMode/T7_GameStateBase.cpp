// Fill out your copyright notice in the Description page of Project Settings.


#include "Team7/Public/GameMode/T7_GameStateBase.h"
#include "Team7/Public/PlayerController/T7_PlayerController.h"
#include "Team7/Public/Character/T7_PlayerCharacter.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"

AT7_PlayerCharacter* T7_PlayerCharacter;

AT7_GameStateBase::AT7_GameStateBase()
{
	Score = 0;
	Kill = 0;

}

void AT7_GameStateBase::BeginPlay()
{
	UpdateHUD();
}

int32 AT7_GameStateBase::GetScore() const
{
	return Score;
}

void AT7_GameStateBase::AddScore(int32 Amount)
{
	Score += Amount;
	UpdateHUD();
}

int32 AT7_GameStateBase::GetKill() const
{
	return Kill;
}

void AT7_GameStateBase::AddKill(int32 Amount)
{
	Kill += Amount;
	UpdateHUD();
}

void AT7_GameStateBase::UpdateHUD()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		AT7_PlayerController* T7_PlayerController = Cast<AT7_PlayerController>(PlayerController);
		{
			if (UUserWidget* HUDWidget = T7_PlayerController->GetHUDWidget())
			{
				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Text_Score"))))
				{
					ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), Score)));
				}
				if (UTextBlock* KillText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Text_Kill"))))
				{
					KillText->SetText(FText::FromString(FString::Printf(TEXT("Kill: %d"), Kill)));
				}
				if (UTextBlock* HpText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Text_Hp"))))
				{
					HpText->SetText(FText::FromString(FString::Printf(TEXT("%.0f/%.0f"), T7_PlayerCharacter->GetCurrentHp(), T7_PlayerCharacter->GetMaxHp())));
				}
				if (UProgressBar* HpProgressBar = Cast<UProgressBar>(HUDWidget->GetWidgetFromName(TEXT("ProgressBar_Hp"))))
				{
					HpProgressBar->SetPercent(T7_PlayerCharacter->GetCurrentHp() / T7_PlayerCharacter->GetMaxHp());
				}
				if (UTextBlock* AmmoText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Text_Ammo"))))
				{
					AmmoText->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), T7_PlayerCharacter->GetCurrentAmmo(), T7_PlayerCharacter->GetMaxAmmo())));
				}

				if (UTextBlock* WeaponText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Text_Weapon"))))
				{
					//WeaponText->SetText(FText::FromString(T7_PlayerCharacter->GetWeaponName()));
				}
			}
		}
	}
}
