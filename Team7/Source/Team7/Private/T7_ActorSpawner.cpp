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
		UE_LOG(LogTemp, Warning, TEXT("ActorClass!!!"))
		SpawnActor();
	}
}

void AT7_ActorSpawner::SpawnActor()
{
	if (TargetPoints.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Empty!!!"))
		return;
	}

	for (AActor* Target : TargetPoints)
	{
		UE_LOG(LogTemp, Warning, TEXT("TargetPoints!!!"))
		if (Target->ActorHasTag("Enemy"))
		{
			TSubclassOf<UObject> EnemyObject = (UClass*)LoadObject<UBlueprint>(nullptr, TEXT("/Game/Characters/EnemyAI/BP_T7_EnemyCharacter.BP_T7_EnemyCharacter"))->GeneratedClass;
			GetWorld()->SpawnActor<AActor>(
				EnemyObject,
				Target->GetActorLocation(),
				FRotator::ZeroRotator);
			UE_LOG(LogTemp, Warning, TEXT("Enemy!!!"))
		}

		/*if (Target->ActorHasTag("Item"))
		{
			GetWorld()->SpawnActor<AActor>(
				AT7_ItemBox::StaticClass(),
				Target->GetActorLocation(),
				FRotator::ZeroRotator);
		}*/
	}
}

