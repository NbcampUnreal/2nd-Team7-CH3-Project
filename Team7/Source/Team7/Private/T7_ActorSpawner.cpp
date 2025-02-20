#include "T7_ActorSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "Team7/Public/Character/T7_EnemyCharacter.h"

AT7_ActorSpawner::AT7_ActorSpawner()
{
 	PrimaryActorTick.bCanEverTick = false;
}

void AT7_ActorSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), TargetPoints);
		SpawnActor();
	}
}

void AT7_ActorSpawner::SpawnActor()
{
	if (TargetPoints.IsEmpty())
	{
		return;
	}

	for (AActor* Target : TargetPoints)
	{
		// �� ����
		if (Target->ActorHasTag("Enemy"))
		{
			TSubclassOf<UObject> EnemyObject = (UClass*)LoadObject<UBlueprint>(nullptr, TEXT("/Game/Characters/EnemyAI/BP_T7_EnemyCharacter.BP_T7_EnemyCharacter"))->GeneratedClass;
			GetWorld()->SpawnActor<AActor>(
				EnemyObject,
				Target->GetActorLocation(),
				FRotator::ZeroRotator);
		}

		// ���� ���� ����
		/*TSubclassOf<UObject> ItemObject = (UClass*)LoadObject<UBlueprint>(nullptr, TEXT("****"))->GeneratedClass;
		if (Target->ActorHasTag("Item"))
		{
			GetWorld()->SpawnActor<AActor>(
				ItemObject,
				Target->GetActorLocation(),
				FRotator::ZeroRotator);
		}*/
	}
}

