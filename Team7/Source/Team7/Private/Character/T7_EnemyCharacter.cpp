#include "Team7/Public/Character/T7_EnemyCharacter.h"

AT7_EnemyCharacter::AT7_EnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AT7_EnemyCharacter::Dead()
{
	Super::Dead();
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::Destroyed, 10.0f, false);
}

