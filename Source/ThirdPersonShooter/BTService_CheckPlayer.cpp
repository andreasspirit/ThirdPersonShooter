#include "BTService_CheckPlayer.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_CheckPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon)
	{
		return;
	}

	APawn* AIPawn = AICon->GetPawn();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(OwnerComp.GetWorld(), 0);

	if (!AIPawn || !PlayerPawn)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		return;
	}

	// 1) Distance check
	const float Distance = FVector::Dist(AIPawn->GetActorLocation(), PlayerPawn->GetActorLocation());
	const float Range = 3000.f;

	if (Distance > Range)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		return;
	}

	// 2) Line of Sight check
	if (!AICon->LineOfSightTo(PlayerPawn))
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		return;
	}

	// 3) In-front (FOV) check
	const FVector ToPlayer = (PlayerPawn->GetActorLocation() - AIPawn->GetActorLocation()).GetSafeNormal();
	const float Dot = FVector::DotProduct(AIPawn->GetActorForwardVector(), ToPlayer);

	// 0.0 = 180° vision, 0.5 ~ 60° cone, 0.7 ~ 45° cone
	const float FOVDotThreshold = 0.3f;

	if (Dot > FOVDotThreshold)
	{

		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), PlayerPawn);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey()); 
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("TargetActor"));
	}
}
