
#include "PlayerController/T7_PlayerController.h"  
#include "Team7/Public/GameMode/T7_GameStateBase.h"
#include "Blueprint/UserWidget.h"


AT7_PlayerController::AT7_PlayerController()
	:HUDWidgetClass(nullptr),
	HUDWidgetInstance(nullptr)
{

}

void AT7_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	ShowHUDWidget();
}

UUserWidget* AT7_PlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

void AT7_PlayerController::ShowHUDWidget()
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();

			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());
		}

		AT7_GameStateBase* T7_GameStateBase = GetWorld() ? GetWorld()->GetGameState<AT7_GameStateBase>() : nullptr;
		if (T7_GameStateBase)
		{
			T7_GameStateBase->UpdateHUD();
		}
	}
}

void AT7_PlayerController::ShowMainMenu()
{

}

void AT7_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (HUDWidgetClass)
    {
        HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
        if (HUDWidgetInstance)
        {
            HUDWidgetInstance->AddToViewport();
            UE_LOG(LogTemp, Warning, TEXT(" HUD 위젯이 정상적으로 생성되었습니다."));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT(" HUD 위젯 생성 실패!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT(" HUDWidgetClass가 설정되지 않았습니다!"));
    }
}


UUserWidget* AT7_PlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}
