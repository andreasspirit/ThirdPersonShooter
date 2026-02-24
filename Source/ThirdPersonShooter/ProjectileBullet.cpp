#include "ProjectileBullet.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ExplosiveBarrel.h"
#include"Kismet/GameplayStatics.h"
AProjectileBullet::AProjectileBullet()
{
	PrimaryActorTick.bCanEverTick = false;

	//Sets the bullet mesh
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	SetRootComponent(BulletMesh);

	//Sets collisions on other actors
	BulletMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BulletMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	BulletMesh->SetSimulatePhysics(false);
	BulletMesh->SetNotifyRigidBodyCollision(true);       
	BulletMesh->SetGenerateOverlapEvents(false);
	


	//Set up components and their attributes
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 1.0f;   //Destroy after 1 sec of spawning so the range is smaller
}

void AProjectileBullet::BeginPlay()
{
	Super::BeginPlay();

	//Sets the speed of the bullet
	if (ProjectileMovement)
	{
		ProjectileMovement->InitialSpeed = MovementSpeed;
		ProjectileMovement->MaxSpeed = MovementSpeed;
	}

	// Hit event
	if (BulletMesh)
	{
		BulletMesh->OnComponentHit.AddDynamic(this, &AProjectileBullet::OnHit);
	}
}

//Hitting Actors and destroys them
void AProjectileBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
	

{
    UGameplayStatics::ApplyDamage(OtherActor, 20.f, GetInstigatorController(), this, UDamageType::StaticClass());
    UGameplayStatics::ApplyDamage(
	OtherActor,
	20.f,
	GetInstigatorController(),
	this,
	UDamageType::StaticClass()
);
	Destroy();
	
}


