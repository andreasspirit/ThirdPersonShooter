
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* PlayerCharacterRef = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacterRef)
	{
		SetFocus(PlayerCharacterRef);
	}
	if(EnemyBehaviorTree)
	{
		RunBehaviorTree(EnemyBehaviorTree);
	}
	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerCharacterRef->GetActorLocation());
}
void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ACharacter*PlayerCharacterRef = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	//LineOfSIght created in blackboard base to get the player location
	if (LineOfSightTo(PlayerCharacterRef)) {
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerCharacterRef->GetActorLocation());
		GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"),PlayerCharacterRef);
	}

	
}
//keep facing player when shooting
void AEnemyAIController::InvokeShootPlayer()
{
	if (!AIPawnRef || AIPawnRef->IsDead())
	{
		return;
	}

	
	if (!PlayerCharacter)
	{
		PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	}

	if (PlayerCharacter)
	{
		SetFocus(PlayerCharacter);  
	}

	AIPawnRef->ShootPlayer();
}
