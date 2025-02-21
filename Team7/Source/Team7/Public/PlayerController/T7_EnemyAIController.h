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
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UBehaviorTree> EnemyBehaviorTree;
};
