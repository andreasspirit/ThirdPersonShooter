
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	APawn*PlayerPawnRef = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawnRef)
	{
		SetFocus(PlayerPawnRef);
	}
	if(EnemyBehaviorTree)
	{
		RunBehaviorTree(EnemyBehaviorTree);
	}
	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawnRef->GetActorLocation());
}
void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn*PlayerPawnRef = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (LineOfSightTo(PlayerPawnRef)) {
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawnRef->GetActorLocation());
		GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"),PlayerPawnRef);
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
