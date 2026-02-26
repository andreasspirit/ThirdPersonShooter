
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class AEnemyAICharacter;

UCLASS()
class THIRDPERSONSHOOTER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	// Called by your BTTask
	UFUNCTION(BlueprintCallable, Category = "AI")
	void InvokeShootPlayer();

private:
	UPROPERTY()
	ACharacter* PlayerCharacter = nullptr;

	UPROPERTY()
	AEnemyAICharacter* AIPawnRef = nullptr;


	UPROPERTY(EditAnywhere)
	UBehaviorTree* EnemyBehaviorTree;
};
