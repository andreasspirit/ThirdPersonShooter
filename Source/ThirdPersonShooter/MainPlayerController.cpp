// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include"Blueprint/UserWidget.h"
#include "ThirdPersonShooterGameModeBase.h"
#include"Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h" 
#include "Components/TextBlock.h"

AMainPlayerController::AMainPlayerController()
{
    EnemiesKilled = 0;          //starts with 0 enemies killed
	HUDWidgetClass = nullptr;
	HUDWidget = nullptr;
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

	if(HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UUserWidget>(this, HUDWidgetClass);

		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}


	if (CrossHairClass)
	{
		CrossHair = CreateWidget<UUserWidget>(this, CrossHairClass);
		if (CrossHair)
		{
			CrossHair->AddToViewport();   //adds minimap ui widget to the viewport
		}
	}
  
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




void AMainPlayerController::UpdatePlayerHUD(float CurrentHealth, float MaxHealth)
{


	// Update health bar
	UProgressBar* HealthBar = Cast<UProgressBar>(HUDWidget->GetWidgetFromName(TEXT("HealthBar")));
	if (HealthBar)
	{
		float Percent = CurrentHealth / MaxHealth;
		HealthBar->SetPercent(Percent);
		
	}


	// Update health text
	UTextBlock* HealthText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("HealthText")));
	if (HealthText)
	{
		FString HealthString = FString::Printf(TEXT("%.0f / %.0f"), CurrentHealth, MaxHealth);
		HealthText->SetText(FText::FromString(HealthString));
	}

}


