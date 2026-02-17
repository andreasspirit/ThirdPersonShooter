
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)
	{
		SetFocus(PlayerPawn);
	}
	if(EnemyBehaviorTree)
	{
		RunBehaviorTree(EnemyBehaviorTree);
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AIPawnRef = Cast<AEnemyAICharacter>(InPawn);
}

void AEnemyAIController::InvokeShootPlayer()
{
	if (!AIPawnRef || AIPawnRef->IsDead())
	{
		return;
	}

	// optional: keep facing player when shooting
	if (!PlayerPawn)
	{
		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	}

	if (PlayerPawn)
	{
		SetFocus(PlayerPawn);
	}

	AIPawnRef->ShootPlayer();
}
