#include "BTTask_ShootPlayer.h"
#include "AIController.h"
#include "EnemyAICharacter.h"

UBTTask_ShootPlayer::UBTTask_ShootPlayer()
{
	NodeName = TEXT("Shoot Player");
}

EBTNodeResult::Type UBTTask_ShootPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	AEnemyAICharacter* EnemyAI = Cast<AEnemyAICharacter>(AIController->GetPawn());
	if (!EnemyAI)
	{
		return EBTNodeResult::Failed;
	}

	if (EnemyAI->IsDead())
	{
		return EBTNodeResult::Failed;
	}

	EnemyAI->ShootPlayer();
	return EBTNodeResult::Succeeded;
}
