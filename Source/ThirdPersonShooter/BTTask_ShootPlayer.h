// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ShootPlayer.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API UBTTask_ShootPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_ShootPlayer();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
