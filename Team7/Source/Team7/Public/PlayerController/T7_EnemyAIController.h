#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "T7_EnemyAIController.generated.h"

class AT7_EnemyCharacter;

UCLASS()
class TEAM7_API AT7_EnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

protected:
	void MoveToCurrentPatrolPoint();
	AT7_EnemyCharacter* GetEnemyCharacter() const;

protected:
	int32 CurrentPatrolIndex = 0;
};
