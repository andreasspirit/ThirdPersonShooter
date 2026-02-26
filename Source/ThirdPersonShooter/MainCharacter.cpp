// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include"GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SceneComponent.h"
#include"ProjectileBullet.h"
#include"Kismet/GameplayStatics.h"
#include "MainPlayerController.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CharacterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Character Mesh"));
	CharacterMesh->SetupAttachment(RootComponent);


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
    SpringArm->bUsePawnControlRotation = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	


	//Spring Arm for Minimap
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MiniMap Spring arm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->TargetArmLength = 600.f;
	CameraSpringArm->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f)); // look straight down
	CameraSpringArm->bDoCollisionTest = false;


	//minimap camera declaration
	MiniMapCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MiniMap camera"));
	MiniMapCamera->SetupAttachment(CameraSpringArm);


	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(GetMesh()); 
	ProjectileSpawnPoint->SetRelativeLocation(FVector(100.f, 0.f, 0.f));

	AutoPossessPlayer = EAutoReceiveInput::Player0;


	Health = MaxHealth;

	FireRate = 0.3f;
	bCanFire = true;


	GetCharacterMovement()->MaxWalkSpeed = 900.0f;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	GameModeRef = Cast<AThirdPersonShooterGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
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
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AMainCharacter::StopJumping);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMainCharacter::Fire);
}

void AMainCharacter::MoveForward(float AxisAmount)
{
	
	 AddMovementInput(GetActorForwardVector(),AxisAmount);
}

void AMainCharacter::Strafe(float AxisAmount)
{
	AddMovementInput(GetActorRightVector(), AxisAmount);
}

void AMainCharacter::LookUp(float AxisAmount)
{
	AddControllerPitchInput(AxisAmount);
}

void AMainCharacter::Turn(float AxisAmount)
{
	AddControllerYawInput(AxisAmount);
}

void AMainCharacter::Fire() {

	if (!bCanFire) return;

	if (!ProjectileClass || !ProjectileSpawnPoint) 
		return;

	const FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	const FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

	GetWorld()->SpawnActor<AProjectileBullet>(ProjectileClass, SpawnLocation, SpawnRotation);

	UGameplayStatics::PlaySoundAtLocation(this, bullet_sound, GetActorLocation()); 

	// Fire rate cooldown
	bCanFire = false;
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AMainCharacter::ResetFire, FireRate, false);
		
}

float AMainCharacter::TakeDamage(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= ActualDamage;
	AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(GetController());
	if (MainPlayerController) {
		MainPlayerController->UpdatePlayerHUD(Health, MaxHealth);
	}
	if (Health <= 0.f)
	{


        if (MainPlayerController)
        {
            MainPlayerController->MainCharacterDied();
        }
		Destroy(); // simple death
	}

	return ActualDamage;
}


void AMainCharacter::Heal(float Amount)
{

	// Add health (don't exceed max)
	Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);


	// Update HUD
	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->UpdatePlayerHUD(Health, MaxHealth);
	}
}

void AMainCharacter::ResetFire()
{
	bCanFire = true;
}
