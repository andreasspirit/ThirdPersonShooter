// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include"Blueprint/UserWidget.h"
#include "ThirdPersonShooterGameModeBase.h"
#include"Kismet/GameplayStatics.h"

AMainPlayerController::AMainPlayerController()
{
    EnemiesKilled = 0;
}
void AMainPlayerController::BeginPlay() {
	Super::BeginPlay();
    
    //displays the minimap attached to the player
    if (MiniMapClass)
    {
        MinimapUI = CreateWidget<UUserWidget>(this, MiniMapClass);
        if (MinimapUI)
        {
            MinimapUI->AddToViewport();
        }
    }

    // Get reference to GameMode
	GameModeRef = Cast<AThirdPersonShooterGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

}


void AMainPlayerController::EnemiesKilledCount()
{
	EnemiesKilled++;
	// Win after 3 kills
	if (EnemiesKilled >= 10)
	{
		if (GameModeRef)
		{
			GameModeRef = Cast<AThirdPersonShooterGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			GameModeRef->GameWon();
		}
	}
	
}

void AMainPlayerController::MainCharacterDied()
{

	if (GameModeRef)
	{
		GameModeRef->GameOver();
	}
}