#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "T7_EnemyAIController.generated.h"

class AT7_EnemyCharacter;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
struct FAIStimulus;

UCLASS()
class TEAM7_API AT7_EnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AT7_EnemyAIController();
	virtual void OnPossess(APawn* InPawn) override;

protected:
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UBehaviorTree> EnemyBehaviorTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UBlackboardComponent> EnemyBlackboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Perception")
	TObjectPtr<UAIPerceptionComponent> EnemyPerception;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Perception")
	TObjectPtr<UAISenseConfig_Sight> SightConfig;
};
