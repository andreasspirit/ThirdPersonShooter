// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include"GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Sound/SoundBase.h"
#include "MainCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class USceneComponent;
class AProjectileBullet;

UCLASS()
class THIRDPERSONSHOOTER_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CharacterMesh;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	//UPROPERTY(EditAnywhere)
	//USoundBase* ShooterMusic;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float AxisAmount);
	void Strafe(float AxisAmount);
	void LookUp(float AxisAmount);
	void Turn(float AxisAmount);


	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraSpringArm;

	UPROPERTY(EditAnywhere)
	USceneCaptureComponent2D* MiniMapCamera;


	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectileBullet> ProjectileClass;

	UPROPERTY(EditAnywhere)
	USoundBase* bullet_sound;

private:
	void Fire();

};
