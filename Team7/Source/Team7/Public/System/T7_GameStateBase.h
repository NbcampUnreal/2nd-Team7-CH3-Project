#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "T7_GameStateBase.generated.h"

class AT7_PlayerController;
class AT7_PlayerCharacter;

UCLASS()
class TEAM7_API AT7_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AT7_GameStateBase();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;

	UFUNCTION(BLueprintCallable, Category = "Score")
	void AddScore(int32 Amount);

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetKill() const;

	UFUNCTION(BLueprintCallable, Category = "Score")
	void AddKill(int32 Amount);

	UFUNCTION(BLueprintCallable, Category = "HUD")
	void UpdateHUD();

	UFUNCTION(BLueprintCallable, Category = "HUD")
	void UpdateWeaponInfo(UTexture2D* NewWeaponTexture, FString WeaponName, int32 CurAmmo, int32 MaxAmmo);

	AT7_PlayerController* GetT7Controller();
	AT7_PlayerCharacter* GetT7Character();


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Kill = 0;
};
