// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"



void AEnemyAIController::BeginPlay() {
	Super::BeginPlay();

	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//SetFocus(PlayerPawn);

	//MoveToActor(PlayerPawn, 20.0f);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);

	MoveToActor(Waypoints[0]);
}

