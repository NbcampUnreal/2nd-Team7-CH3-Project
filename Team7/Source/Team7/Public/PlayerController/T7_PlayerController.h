#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "T7_PlayerController.generated.h"

UCLASS()
class TEAM7_API AT7_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AT7_PlayerController();

	UFUNCTION(BlueprintPure, Category = "UI")
	UUserWidget* GetHUDWidget() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowHUDWidget();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowMainMenu();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MainMenuWidgetClass = nullptr;

	UUserWidget* MainMenuWidgetInstance = nullptr;
	UUserWidget* HUDWidgetInstance = nullptr;

};
