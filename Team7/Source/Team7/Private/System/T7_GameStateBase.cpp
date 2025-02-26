#include "System/T7_GameStateBase.h"
#include "Team7/Public/PlayerController/T7_PlayerController.h"
#include "Team7/Public/Character/T7_PlayerCharacter.h"
#include "Team7/Public/Character/T7_CharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "Components/ProgressBar.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Blueprint/UserWidget.h"

AT7_GameStateBase::AT7_GameStateBase()
{

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

void AT7_GameStateBase::AddKill(int32 Amount, AT7_CharacterBase* Enemy)
{
	Kill += Amount;
	AddKillLog(Enemy);
	UpdateHUD();
}

void AT7_GameStateBase::UpdateHUD()
{
	if (AT7_PlayerController* PlayerController = GetT7Controller())
	{
		if (AT7_PlayerCharacter* PlayerCharacter = GetT7Character())
		{
			if (UUserWidget* HUDWidget = PlayerController->GetHUDWidget())
			{
				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Text_Score"))))
				{
					ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), Score)));
				}

				if (UTextBlock* KillText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Text_Kill"))))
				{
					KillText->SetText(FText::FromString(FString::Printf(TEXT("Kill: %d"), Kill)));
				}

				if (UTextBlock* HpText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Text_HP"))))
				{
					HpText->SetText(FText::FromString(FString::Printf(TEXT("%.0f/%.0f"), PlayerCharacter->GetCurrentHP(), PlayerCharacter->GetMaxHP())));
				}
				if (UProgressBar* HpProgressBar = Cast<UProgressBar>(HUDWidget->GetWidgetFromName(TEXT("ProgressBar_HP"))))
				{
					HpProgressBar->SetPercent(PlayerCharacter->GetCurrentHP() / PlayerCharacter->GetMaxHP());
				}

				if (PlayerCharacter->GetCurrentWeapon() != nullptr)
				{
					UpdateWeaponInfo(nullptr, FString("Rifle"), 12, 24);
				}
				else
				{
					UpdateWeaponInfo(nullptr, FString("FryFan"), 0, 0);
				}
			}
		}
	}
}

void AT7_GameStateBase::UpdateWeaponInfo(UTexture2D* NewWeaponTexture, FString WeaponName, int32 CurAmmo, int32 MaxAmmo)
{
	if (AT7_PlayerController* PlayerController = GetT7Controller())
	{
		if (UUserWidget* HUDWidget = PlayerController->GetHUDWidget())
		{
			if (UImage* WeaponImage = Cast<UImage>(HUDWidget->GetWidgetFromName(TEXT("Image_Weapon"))))
			{
				if (UMaterialInstanceDynamic* DynamicMaterial = WeaponImage->GetDynamicMaterial())
				{
					if (NewWeaponTexture)
					{
						DynamicMaterial->SetTextureParameterValue(TEXT("Image"), NewWeaponTexture);
					}
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

void AT7_GameStateBase::AddKillLog(AT7_CharacterBase* Enemy)
{
	FText PlayerName = FText::FromString(TEXT("Legend"));
	//FText EnemyName = FText::FromName(Enemy->GetName());
	FText EnemyName = FText::FromString(TEXT("Newbie"));

	if (AT7_PlayerCharacter* PlayerCharacter = GetT7Character())
	{
		//PlayerCharacter->GetCurrentWeapon()->GetWeaponImage();
		PlayerName = FText::FromString(PlayerCharacter->GetName());
	}

	if (AT7_PlayerController* PlayerController = GetT7Controller())
	{
		if (UUserWidget* HUDWidget = PlayerController->GetHUDWidget())
		{
			if (UVerticalBox* KillLogBox = Cast<UVerticalBox>(HUDWidget->GetWidgetFromName(TEXT("KillLogBox"))))
			{
				if (UUserWidget* KillLog = PlayerController->CreateKillLogWidget())
				{
					if (UTextBlock* PlayerText = Cast<UTextBlock>(KillLog->GetWidgetFromName(TEXT("PlayerName"))))
					{
						PlayerText->SetText(PlayerName);
					}
					if (UTextBlock* EnemyText = Cast<UTextBlock>(KillLog->GetWidgetFromName(TEXT("EnemyName"))))
					{
						EnemyText->SetText(EnemyName);
					}
					if (UImage* WeaponImage = Cast<UImage>(KillLog->GetWidgetFromName(TEXT("Image_Weapon"))))
					{
						if (UMaterialInstanceDynamic* DynamicMaterial = WeaponImage->GetDynamicMaterial())
						{
							/*if (NewWeaponTexture)
							{
								DynamicMaterial->SetTextureParameterValue(TEXT("Image"), NewWeaponTexture);
							}*/
						}
					}
					KillLogBox->AddChild(KillLog);
				}
			}
		}
	}
	
}

AT7_PlayerController* AT7_GameStateBase::GetT7Controller()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AT7_PlayerController* T7_PlayerController = Cast<AT7_PlayerController>(PlayerController))
		{
			return T7_PlayerController;
		}
	}

	return nullptr;
}

AT7_PlayerCharacter* AT7_GameStateBase::GetT7Character()
{
	if (ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if (AT7_PlayerCharacter* T7_PlayerCharacter = Cast<AT7_PlayerCharacter>(PlayerCharacter))
		{
			return T7_PlayerCharacter;
		}
	}

	return nullptr;
}
