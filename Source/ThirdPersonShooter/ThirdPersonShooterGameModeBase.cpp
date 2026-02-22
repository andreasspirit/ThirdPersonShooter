// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"



AThirdPersonShooterGameModeBase::AThirdPersonShooterGameModeBase() {

}

void AThirdPersonShooterGameModeBase::BeginPlay() {
	Super::BeginPlay();
}

void AThirdPersonShooterGameModeBase::GameWon() {
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("GameWonLevel"));
}

void AThirdPersonShooterGameModeBase::GameOver() {
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("GameOverLevel"));
}