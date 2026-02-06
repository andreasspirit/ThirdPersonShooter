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

	//declare the UUserWidget which will implement the Minimap widget 
private:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> MiniMapClass;

	UPROPERTY()
	UUserWidget* MinimapUI = nullptr;
};
