#include "Team7/Public/GameMode/T7_GameModeBase.h"

#include "Actor/T7_SpawnPoint.h"
#include "Data/T7_SpawnData.h"
#include "GameplayTags/T7_GameplayTags.h"
#include "System/T7_AssetManager.h"
#include "System/T7_GameStateBase.h"

AT7_GameModeBase::AT7_GameModeBase()
{
	
}

void AT7_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Spawn();
	
}

void AT7_GameModeBase::Spawn()
{
	UT7_SpawnData* SpawnData = Cast<UT7_SpawnData>(UT7_AssetManager::Get().GetAssetByTag(T7_BPClassTag::DA_BPClass));
	ensure(SpawnData);
	if (AT7_GameStateBase* T7GameState = GetGameState<AT7_GameStateBase>())
	{
		for (const AT7_SpawnPoint* SpawnPoint : T7GameState->GetSpawnPoints())
		{
			UClass* SpawnedActor = nullptr;
			switch (SpawnPoint->SpawnType)
			{
			case ESpawnType::Enemy_Normal:
				SpawnedActor = SpawnData->FindClassByTag(T7_BPClassTag::BP_CLASS_ENEMY_NORMAL);
				break;
			case ESpawnType::Enemy_Elite:
				SpawnedActor = SpawnData->FindClassByTag(T7_BPClassTag::BP_CLASS_ENEMY_ELITE);
				break;
				// 나중에 보스 추가?
			case ESpawnType::ItemBox_Weapon:
				SpawnedActor = SpawnData->FindClassByTag(T7_BPClassTag::BP_CLASS_ITEMBOX_WEAPON);
				break;
			case ESpawnType::ItemBox_Medikit:
				SpawnedActor = SpawnData->FindClassByTag(T7_BPClassTag::BP_CLASS_ITEMBOX_MEDIKIT);
				break;
			default:
				break;
			}
			if (UWorld* World = GetWorld())
			{
				World->SpawnActor<AActor>(SpawnedActor, SpawnPoint->GetActorLocation(), FRotator::ZeroRotator);
			}
		}
	}
}
