#include "Team7/Public/PlayerController/T7_EnemyAIController.h"
#include "Team7/Public/Character/T7_EnemyCharacter.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void AT7_EnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (EnemyBehaviorTree)
	{
		RunBehaviorTree(EnemyBehaviorTree);
	}

	GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPath"), InPawn->GetActorLocation());

}

void AT7_EnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
}

