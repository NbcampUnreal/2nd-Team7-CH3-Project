// Fill out your copyright notice in the Description page of Project Settings.


#include "Team7/Public/GameMode/T7_GameStateBase.h"
#include "Team7/Public/PlayerController/T7_PlayerController.h"
#include "Team7/Public/Character/T7_PlayerCharacter.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInstanceDynamic.h"
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
    Super::BeginPlay();

    // 게임 시작 시 HUD 숨기기
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        AT7_PlayerController* T7_PlayerController = Cast<AT7_PlayerController>(PlayerController);
        if (T7_PlayerController)
        {
            if (UUserWidget* HUDWidget = T7_PlayerController->GetHUDWidget())
            {
                UWidget* WeaponUIPanel = HUDWidget->GetWidgetFromName(TEXT("WeaponUIPanel"));
                if (WeaponUIPanel)
                {
                    WeaponUIPanel->SetVisibility(ESlateVisibility::Hidden);
                }
            }
        }
    }

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
			}
		}
	}
}

void AT7_GameStateBase::UpdateWeaponInfo(UTexture2D* NewWeaponTexture, FString WeaponName, int32 CurAmmo, int32 MaxAmmo)
{
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        AT7_PlayerController* T7_PlayerController = Cast<AT7_PlayerController>(PlayerController);
        if (T7_PlayerController)
        {
            if (UUserWidget* HUDWidget = T7_PlayerController->GetHUDWidget())
            {
                // 무기 UI 패널 찾기 (이름은 HUD 위젯에서 설정한 이름과 동일해야 함)
                UWidget* WeaponUIPanel = HUDWidget->GetWidgetFromName(TEXT("WeaponUIPanel"));

                if (WeaponUIPanel)
                {
                    bool bShouldShow = (CurAmmo > 0 || MaxAmmo > 0);
                    WeaponUIPanel->SetVisibility(bShouldShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
                }

                if (UImage* WeaponImage = Cast<UImage>(HUDWidget->GetWidgetFromName(TEXT("Image_Weapon"))))
                {
                    if (NewWeaponTexture)
                    {
                        WeaponImage->SetBrushFromTexture(NewWeaponTexture);
                    }
                }

                if (UTextBlock* WeaponText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Text_Weapon"))))
                {
                    WeaponText->SetText(FText::FromString(WeaponName));
                }

                if (UTextBlock* CurAmmoText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Text_CurAmmo"))))
                {
                    CurAmmoText->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurAmmo)));
                }

                if (UTextBlock* MaxAmmoText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Text_MaxAmmo"))))
                {
                    MaxAmmoText->SetText(FText::FromString(FString::Printf(TEXT("%d"), MaxAmmo)));
                }
            }
        }
    }
}

