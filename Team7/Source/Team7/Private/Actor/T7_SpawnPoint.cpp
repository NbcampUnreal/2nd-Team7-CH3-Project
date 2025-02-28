#include "Actor/T7_SpawnPoint.h"

#include "GameMode/T7_GameModeBase.h"
#include "System/T7_GameStateBase.h"

AT7_SpawnPoint::AT7_SpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AT7_SpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	Register();
}

void AT7_SpawnPoint::Register()
{
	if (UWorld* World = GetWorld())
	{
		if (AT7_GameStateBase* GameState = World->GetGameState<AT7_GameStateBase>())
		{
			GameState->RegisterSpawnPoint(this);
		}
	}
}

