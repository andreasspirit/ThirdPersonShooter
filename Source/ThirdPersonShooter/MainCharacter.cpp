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


	Health = MaxHealth;        //sets starting health as the max health 

	FireRate = 0.6f;             //Fire rate which is implemented with timer
	bCanFire = true;           


	GetCharacterMovement()->MaxWalkSpeed = 900.0f;          //Max Character Speed
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Sets the Game Mode Base 
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

	//Input binds for character Movement and mechanics
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &AMainCharacter::Strafe);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMainCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMainCharacter::Turn);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AMainCharacter::StopJumping);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMainCharacter::Fire);
}


//Move Forward declaration			
void AMainCharacter::MoveForward(float AxisAmount)
{
	
	 AddMovementInput(GetActorForwardVector(),AxisAmount);
}

//Move left or right
void AMainCharacter::Strafe(float AxisAmount)
{
	AddMovementInput(GetActorRightVector(), AxisAmount);
}

//Look up or down with moving the mouse Y
void AMainCharacter::LookUp(float AxisAmount)
{
	AddControllerPitchInput(AxisAmount);
}

//Look to your right or left moving the mouse X
void AMainCharacter::Turn(float AxisAmount)
{
	AddControllerYawInput(AxisAmount);
}


//Shooting function for the  main character
void AMainCharacter::Fire() {

	if (!bCanFire) return;

	if (!ProjectileClass || !ProjectileSpawnPoint) 
		return;

	const FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();    //gets the location of the projectile bullet component
	const FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();    //gets the rotation of the projectile bullet component

	GetWorld()->SpawnActor<AProjectileBullet>(ProjectileClass, SpawnLocation, SpawnRotation);        //spawns the bullet

	//Play shooting sound 
	UGameplayStatics::PlaySoundAtLocation(this, bullet_sound, GetActorLocation()); 

	// Fire rate cooldown
	bCanFire = false;
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AMainCharacter::ResetFire, FireRate, false); //Timer handle for shooting
		
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
		MainPlayerController->UpdatePlayerHUD(Health, MaxHealth);   //calls the health bar ui
	}
	if (Health <= 0.f)   //if health is 0 the player dies
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

	// Add health
	Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);


	// Update HUD of health bar
	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->UpdatePlayerHUD(Health, MaxHealth);
	}
}


void AMainCharacter::ResetFire()
{
	bCanFire = true;   //calling the fire function when the timer cooldown is reset
}
