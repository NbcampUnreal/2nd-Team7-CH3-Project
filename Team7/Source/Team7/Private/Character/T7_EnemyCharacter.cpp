#include "Team7/Public/Character/T7_EnemyCharacter.h"
#include "Team7/Public/PlayerController/T7_EnemyAIController.h"

AT7_EnemyCharacter::AT7_EnemyCharacter()
{
	AIControllerClass = AT7_EnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AT7_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

