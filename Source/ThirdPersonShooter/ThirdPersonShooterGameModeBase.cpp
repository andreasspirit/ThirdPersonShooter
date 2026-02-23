// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"



AThirdPersonShooterGameModeBase::AThirdPersonShooterGameModeBase() {
	WinWidget = nullptr;
	LoseWidget = nullptr;
	GameModeWidget = nullptr;  // ← Initialize
}

void AThirdPersonShooterGameModeBase::BeginPlay() {
	Super::BeginPlay();
}

void AThirdPersonShooterGameModeBase::GameWon() {
//	UGameplayStatics::OpenLevel(GetWorld(), TEXT("GameWonLevel"));
	if (WinWidget)
	{
		// Create widget and STORE it in CurrentWidget (prevents garbage collection)
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

void AThirdPersonShooterGameModeBase::GameOver() {
	if (LoseWidget)
	{
		// Create widget and STORE it in CurrentWidget (prevents garbage collection)
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

