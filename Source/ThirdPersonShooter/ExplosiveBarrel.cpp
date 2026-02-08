#include "ExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectileBullet.h"   

AExplosiveBarrel::AExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = false;

	IntactMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IntactMesh"));
	SetRootComponent(IntactMesh);

	
	IntactMesh->SetSimulatePhysics(true);
	IntactMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	IntactMesh->SetNotifyRigidBodyCollision(true); // generates hit events
	IntactMesh->SetGenerateOverlapEvents(false);

	BrokenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BrokenMesh"));
	BrokenMesh->SetupAttachment(RootComponent);

	BrokenMesh->SetSimulatePhysics(true);
	BrokenMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BrokenMesh->SetNotifyRigidBodyCollision(false);
	BrokenMesh->SetHiddenInGame(true);
	BrokenMesh->SetVisibility(false);

	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForce"));
	RadialForce->SetupAttachment(RootComponent);

	// Good defaults (you can tweak in editor)
	RadialForce->Radius = ExplosionRadius;
	RadialForce->ImpulseStrength = ExplosionImpulseStrength;
	RadialForce->bImpulseVelChange = true;
	RadialForce->bAutoActivate = false; // we trigger it manually
	RadialForce->bIgnoreOwningActor = true;

	// If you only want physics objects affected:
	RadialForce->AddCollisionChannelToAffect(ECC_PhysicsBody);
}

void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();

	// Hook the hit event to the intact mesh
	IntactMesh->OnComponentHit.AddDynamic(this, &AExplosiveBarrel::OnIntactHit);

	// Make sure radius/impulse are synced if changed in editor
	RadialForce->Radius = ExplosionRadius;
	RadialForce->ImpulseStrength = ExplosionImpulseStrength;
}

void AExplosiveBarrel::OnIntactHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{



	if (OtherActor->IsA(AProjectileBullet::StaticClass()))
	{
		Explode();

		OtherActor->Destroy();
	}

}

void AExplosiveBarrel::Explode()
{
	bExploded = true;

	// Swap meshes
	IntactMesh->SetHiddenInGame(true);
	IntactMesh->SetVisibility(false);
	IntactMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BrokenMesh->SetHiddenInGame(false);
	BrokenMesh->SetVisibility(true);
	BrokenMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// Place broken mesh exactly where intact was
	BrokenMesh->SetWorldTransform(IntactMesh->GetComponentTransform());

	// Fire impulse from center of barrel
	RadialForce->FireImpulse();


	// OPTIONAL: if you want the broken pieces to “kick” upward a bit
	BrokenMesh->AddImpulse(FVector(0, 0, 1) * 200.f, NAME_None, true);

		UGameplayStatics::PlaySound2D(
		GetWorld(),
		ExplosionSound,
		1.0f,
		1.0f,
		0.0f);
}
