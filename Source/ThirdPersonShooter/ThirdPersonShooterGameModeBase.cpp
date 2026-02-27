// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"



AThirdPersonShooterGameModeBase::AThirdPersonShooterGameModeBase() {
	WinWidget = nullptr;
	LoseWidget = nullptr;
	GameModeWidget = nullptr;  
}

void AThirdPersonShooterGameModeBase::BeginPlay() {
	Super::BeginPlay();
}

void AThirdPersonShooterGameModeBase::GameWon() {

	if (WinWidget)
	{
		// Create widget and set it in CurrentWidget 
		GameModeWidget = CreateWidget<UUserWidget>(GetWorld(), WinWidget);

		if (GameModeWidget)
		{
			GameModeWidget->AddToViewport();

			// Show mouse and set input mode
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PlayerController)
			{
				PlayerController->bShowMouseCursor = true;
				PlayerController->SetInputMode(FInputModeUIOnly());
			}
		}
		
	}
}


//game Over Widget
void AThirdPersonShooterGameModeBase::GameOver() {
	if (LoseWidget)
	{
		// Create widget and sets it in CurrentWidget (prevents garbage collection)
		GameModeWidget = CreateWidget<UUserWidget>(GetWorld(), LoseWidget);

		if (GameModeWidget)
		{
			GameModeWidget->AddToViewport();

			// Show mouse and set input mode
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PlayerController)
			{
				PlayerController->bShowMouseCursor = true;
				PlayerController->SetInputMode(FInputModeUIOnly());
			}
		}

	}

}

