#include "Team7/Public/PlayerController/T7_EnemyAIController.h"
#include "Team7/Public/Character/T7_EnemyCharacter.h"
#include "Navigation/PathFollowingComponent.h"

void AT7_EnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AT7_EnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	MoveToCurrentPatrolPoint();
}

void AT7_EnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if (Result.Code == EPathFollowingResult::Success)
	{
		int32 PatrolPointsCount = GetEnemyCharacter()->PatrolPoints.Num();
		CurrentPatrolIndex = (CurrentPatrolIndex + 1) % PatrolPointsCount;
		MoveToCurrentPatrolPoint();
	}
}

void AT7_EnemyAIController::MoveToCurrentPatrolPoint()
{
	AT7_EnemyCharacter* MyEnemyChar = GetEnemyCharacter();

	MoveToActor(
		MyEnemyChar->PatrolPoints[CurrentPatrolIndex],
		5.0f,
		true,
		true,
		false,
		nullptr,
		true);
}

AT7_EnemyCharacter* AT7_EnemyAIController::GetEnemyCharacter() const
{
	AT7_EnemyCharacter* MyEnemyChar = Cast<AT7_EnemyCharacter>(GetPawn());

	if (!MyEnemyChar)
	{
		return nullptr;
	}

	if (MyEnemyChar->PatrolPoints.Num() == 0)
	{
		return nullptr;
	}

	return MyEnemyChar;
}
