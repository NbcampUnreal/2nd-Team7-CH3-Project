#include "Team7/Public/Character/T7_EnemyCharacter.h"
#include "Team7/Public/System/T7_GameStateBase.h"
#include "Team7/Public/PlayerController/T7_EnemyAIController.h"
#include "Kismet/GameplayStatics.h"

AT7_EnemyCharacter::AT7_EnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AT7_EnemyCharacter::Dead()
{
	Super::Dead();
	
	if (AT7_GameStateBase* GameState = Cast<AT7_GameStateBase>(UGameplayStatics::GetGameState(GetWorld())))
	{
		GameState->AddKill(1, this);
		GameState->AddScore(100);
	}

	if (AT7_EnemyAIController* AIController = Cast<AT7_EnemyAIController>(GetController()))
	{
		AIController->UnPossess();
	}

	SetLifeSpan(5.0f);
}
