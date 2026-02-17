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

	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon)
	{
		return EBTNodeResult::Failed;
	}

	AEnemyAICharacter* Enemy = Cast<AEnemyAICharacter>(AICon->GetPawn());
	if (!Enemy)
	{
		return EBTNodeResult::Failed;
	}

	if (Enemy->IsDead())
	{
		return EBTNodeResult::Failed;
	}

	Enemy->ShootPlayer();
	return EBTNodeResult::Succeeded;
}
