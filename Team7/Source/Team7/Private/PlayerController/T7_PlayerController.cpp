#include "Team7/Public/PlayerController/T7_PlayerController.h"
#include "Team7/Public/System/T7_GameStateBase.h"
#include "Blueprint/UserWidget.h"

AT7_PlayerController::AT7_PlayerController()
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
