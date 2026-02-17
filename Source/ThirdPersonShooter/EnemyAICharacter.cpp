#include "EnemyAICharacter.h"
#include "ProjectileBullet.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

AEnemyAICharacter::AEnemyAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(GetMesh()); // or RootComponent if you prefer
	ProjectileSpawnPoint->SetRelativeLocation(FVector(100.f, 0.f, 50.f));
}

void AEnemyAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

float AEnemyAICharacter::TakeDamage(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= ActualDamage;

	if (Health <= 0.f)
	{
		Destroy(); // simple death
	}

	return ActualDamage;
}

void AEnemyAICharacter::ShootPlayer()
{
	if (IsDead() || !ProjectileClass || !ProjectileSpawnPoint) return;

	const FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	const FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AProjectileBullet>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (bullet_sound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, bullet_sound, GetActorLocation());
	}
}
