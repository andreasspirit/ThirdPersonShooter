#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class UBehaviorTree;
class UBlackboardComponent;

UCLASS()
class THIRDPERSONSHOOTER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	public:
		UPROPERTY(EditAnywhere,Category="AI")
		UBehaviorTree* BehaviorTreeAsset;
private:
	UPROPERTY()
	TArray<AActor*> Waypoints;
};
