
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

	// HUD 위젯 생성 및 표시
	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
		}
	}

	AT7_GameStateBase* T7_GameStateBase = GetWorld() ? GetWorld()->GetGameState<AT7_GameStateBase>() : nullptr;
	if (T7_GameStateBase)
	{
		T7_GameStateBase->UpdateHUD();
	}
}

UUserWidget* AT7_PlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}
