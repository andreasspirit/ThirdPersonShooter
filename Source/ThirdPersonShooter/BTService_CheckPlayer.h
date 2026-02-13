// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CheckPlayer.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API UBTService_CheckPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
