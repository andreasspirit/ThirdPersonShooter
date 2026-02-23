// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ThirdPersonShooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API AThirdPersonShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AThirdPersonShooterGameModeBase();

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> WinWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> LoseWidget;

	// ← ADD THESE: Store created widgets so they don't get garbage collected
	UPROPERTY()
	class UUserWidget* GameModeWidget;
	// Function to show widget

	// Win the game
	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void GameWon();

	// Lose the game
	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void GameOver();
};
