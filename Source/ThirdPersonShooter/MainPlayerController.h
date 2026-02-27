// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"


 class UUserWidget;
/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
private:
	
	//declare the UUserWidget which will implement the Minimap widget 
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> MiniMapClass;

	UPROPERTY()
	UUserWidget* MinimapUI = nullptr;  //Minimap UI


	int32 EnemiesKilled; //counter for enemies killed

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDWidgetClass;


	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> CrossHairClass;

	UPROPERTY()
	class UUserWidget* HUDWidget;



	UPROPERTY()
	class UUserWidget* CrossHair;
public:
	AMainPlayerController();

	UFUNCTION(BlueprintCallable)
	void EnemiesKilledCount();   // this function will get called when the enemy ai dies

	UFUNCTION(BlueprintCallable)
	void MainCharacterDied();    //this function will get called when the main character dies

	// Function to update HUD
	UFUNCTION(BlueprintCallable)
	void UpdatePlayerHUD(float CurrentHealth, float MaxHealth);



};
