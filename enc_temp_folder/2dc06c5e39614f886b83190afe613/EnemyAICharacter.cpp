#include "EnemyAICharacter.h"
#include "ProjectileBullet.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "MainPlayerController.h"

AEnemyAICharacter::AEnemyAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	//ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	//ProjectileSpawnPoint->SetupAttachment(GetMesh()); // or RootComponent if you prefer
	//ProjectileSpawnPoint->SetRelativeLocation(FVector(100.f, 0.f, 50.f));



	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);    
    
    
    FireRate = 0.5f;  
    bCanFire = true;
}

void AEnemyAICharacter::BeginPlay()
{
	Super::BeginPlay();
}


float AEnemyAICharacter::TakeDamage(float DamageAmount,FDamageEvent const& DamageEvent,AController* EventInstigator,
	AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= ActualDamage;     //Decrease health when taking damage

	if (Health <= 0.f)
	{

        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(PlayerController);

        if (MainPlayerController)
        {
            MainPlayerController->EnemiesKilledCount();  //count enemies killed for winning condition
        }
        Destroy(); // simple death
	}

	return ActualDamage;
}

void AEnemyAICharacter::ShootPlayer()
{

    if (!bCanFire) return;


    AController* ControllerRef = GetController();
    if (!ControllerRef) 
    return;

    FVector CameraLocation;
    FRotator CameraRotation;
    ControllerRef->GetPlayerViewPoint(CameraLocation, CameraRotation);

    FVector TraceEnd = CameraLocation + (CameraRotation.Vector() * RaycastRange);

    FHitResult HitResult;
    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(this);      //Ignore hitting itself and other Ai characters

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult,CameraLocation,TraceEnd,ECollisionChannel::ECC_Visibility,
        TraceParams);

    // Draw debug line to visualize the raycast
    DrawDebugLine(GetWorld(),CameraLocation,TraceEnd,bHit ? FColor::Red : FColor::Green,false,2.0f,0,2.0f);

    // Play fire sound
    if (bullet_sound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, bullet_sound, GetActorLocation());
    }

    // Apply damage if hit
    if (bHit)
    {
        AActor* HitActor = HitResult.GetActor();
        if (HitActor)
        {
            UGameplayStatics::ApplyDamage(
                HitActor,
                RaycastDamage,                //Raycast damage 
                ControllerRef,                
                this,
                UDamageType::StaticClass());
        }
    }

    // Fire rate cooldown with handling timer
    bCanFire = false;
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyAICharacter::ResetFire, FireRate, false);

}


void AEnemyAICharacter::ResetFire()
{
    bCanFire = true;
}
