#include "BTService_CheckPlayer.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_CheckPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();


	APawn* AIPawn = AIController->GetPawn();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(OwnerComp.GetWorld(), 0);

	if (!AIPawn || !PlayerPawn)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		return;
	}

	//Distance check
	const float Distance = FVector::Dist(AIPawn->GetActorLocation(), PlayerPawn->GetActorLocation());
	const float Range = 5000.f;

	if (Distance > Range)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		
	}
	else
	{
		//
		//Gets the attack range of AI as boolean from blackboard 
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("InAttackRange"), true);
	}

	// 2) Line of Sight check
	if (AIController->LineOfSightTo(PlayerPawn))
	{		
		//Gets the line of sight of AI as boolean from blackboard 
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
		
	}
	else {
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}

	//  In-front of it check
	const FVector ToPlayer = (PlayerPawn->GetActorLocation() - AIPawn->GetActorLocation()).GetSafeNormal();
	const float Dot = FVector::DotProduct(AIPawn->GetActorForwardVector(), ToPlayer);


	const float FOVDotThreshold = 0.3f;


	//Dot Product declaration
	if (Dot > FOVDotThreshold)
	{



		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), PlayerPawn);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("HasLineOfSight"));
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("TargetActor"));
	}
}
