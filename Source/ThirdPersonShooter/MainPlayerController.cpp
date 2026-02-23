// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include"Blueprint/UserWidget.h"
#include "ThirdPersonShooterGameModeBase.h"
#include"Kismet/GameplayStatics.h"

AMainPlayerController::AMainPlayerController()
{
    EnemiesKilled = 0;          //starts with 0 enemies killed
}
void AMainPlayerController::BeginPlay() {
	Super::BeginPlay();
    
    //displays the minimap attached to the player
    if (MiniMapClass)
    {
        MinimapUI = CreateWidget<UUserWidget>(this, MiniMapClass);
        if (MinimapUI)
        {
            MinimapUI->AddToViewport();   //adds minimap ui widget to the viewport
        }
    }

    // Get reference to GameMode
	//GameModeRef = Cast<AThirdPersonShooterGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

}


void AMainPlayerController::EnemiesKilledCount()
{
	EnemiesKilled++;
	// Win after all 5 ai kills
	if (EnemiesKilled >= 10)
	{
		AThirdPersonShooterGameModeBase* GameMode = Cast<AThirdPersonShooterGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			//Get reference to the GameWon function of gamemode base
			GameMode->GameWon();
		}
	}
	
}

void AMainPlayerController::MainCharacterDied()  //Lose the game when main character is dead
{
	AThirdPersonShooterGameModeBase* GameMode = Cast<AThirdPersonShooterGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		//Get reference to the GameOver function of gamemode base
		GameMode->GameOver();
	}
}

