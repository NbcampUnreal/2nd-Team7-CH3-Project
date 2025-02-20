#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T7_ActorSpawner.generated.h"

UCLASS()
class TEAM7_API AT7_ActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AT7_ActorSpawner();
	void SpawnActor();

protected:
	virtual void BeginPlay() override;

public:
	TArray<AActor*> TargetPoints;
};
