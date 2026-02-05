// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include"GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent2D.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CharacterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Character Mesh"));
	CharacterMesh->SetupAttachment(RootComponent);


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);


	//Spring Arm for Minimap
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MiniMap Spring arm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->TargetArmLength = 600.f;
	CameraSpringArm->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f)); // look straight down
	CameraSpringArm->bDoCollisionTest = false;

	MiniMapCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MiniMap camera"));
	MiniMapCamera->SetupAttachment(CameraSpringArm);


	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &AMainCharacter::Strafe);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMainCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMainCharacter::Turn);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMainCharacter::Jump);
}

void AMainCharacter::MoveForward(float AxisAmount)
{
	
	AddMovementInput(GetActorRightVector() * AxisAmount);
}

void AMainCharacter::Strafe(float AxisAmount)
{
	AddMovementInput(GetActorForwardVector() * AxisAmount);
}

void AMainCharacter::LookUp(float AxisAmount)
{
	AddControllerPitchInput(AxisAmount);
}

void AMainCharacter::Turn(float AxisAmount)
{
	AddControllerYawInput(AxisAmount);
}