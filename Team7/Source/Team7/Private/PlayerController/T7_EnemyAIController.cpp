#include "Team7/Public/PlayerController/T7_EnemyAIController.h"
#include "Team7/Public/Character/T7_EnemyCharacter.h"
#include "Team7/Public/Character/T7_PlayerCharacter.h"
#include "Team7/Public/Weapon/T7_Projectile.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AIPerceptionTypes.h"
#include "Kismet/GameplayStatics.h"

AT7_EnemyAIController::AT7_EnemyAIController()
{
	EnemyPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 2000.0f;
	SightConfig->LoseSightRadius = 3000.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));

	EnemyPerception->ConfigureSense(*SightConfig);
	EnemyPerception->ConfigureSense(*DamageConfig);
	EnemyPerception->SetDominantSense(SightConfig->GetSenseImplementation());

	EnemyPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AT7_EnemyAIController::OnTargetPerceptionUpdated);
}

void AT7_EnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (EnemyBehaviorTree)
	{
		RunBehaviorTree(EnemyBehaviorTree);
		EnemyBlackboard = GetBlackboardComponent();
		EnemyBlackboard->SetValueAsVector(TEXT("PatrolPath"), InPawn->GetActorLocation());
		EnemyBlackboard->SetValueAsFloat(TEXT("AttackRange"), AttackRange);
	}
}

void AT7_EnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		EnemyBlackboard->SetValueAsBool(TEXT("IsDetected"), true);

		if (AT7_Projectile* Weapon = Cast<AT7_Projectile>(Actor))
		{
			EnemyBlackboard->SetValueAsObject(TEXT("TargetActor"), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		}
		if (AT7_PlayerCharacter* PlayerCharacter = Cast<AT7_PlayerCharacter>(Actor))
		{
			EnemyBlackboard->SetValueAsObject(TEXT("TargetActor"), PlayerCharacter);
		}
	}
	else
	{
		EnemyBlackboard->SetValueAsBool(TEXT("IsDetected"), false);
		EnemyBlackboard->SetValueAsObject(TEXT("TargetActor"), nullptr);
	}
}

