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

	// Win the game
	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void GameWon();

	// Lose the game
	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void GameOver();
};
