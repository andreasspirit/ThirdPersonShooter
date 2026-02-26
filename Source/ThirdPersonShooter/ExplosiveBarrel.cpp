#include "ExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectileBullet.h"   

AExplosiveBarrel::AExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = false;

	//Set the basic barrel mesh
	IntactMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IntactMesh"));
	SetRootComponent(IntactMesh);

	//Enable collision with physics 
	IntactMesh->SetSimulatePhysics(true);
	IntactMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);   //Enables query and physics collision
	IntactMesh->SetNotifyRigidBodyCollision(true);      // generates hit events

	//Set the broken mesh of the barrel
	BrokenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BrokenMesh"));
	BrokenMesh->SetupAttachment(RootComponent);

	BrokenMesh->SetSimulatePhysics(true);
	BrokenMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);   //Enables query and physics collision

	BrokenMesh->SetHiddenInGame(true);
	BrokenMesh->SetVisibility(false);

	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForce"));
	RadialForce->SetupAttachment(RootComponent);

	//Initialise radial force radius and strength
	RadialForce->Radius = ExplosionRadius;
	RadialForce->ImpulseStrength = ExplosionImpulseStrength;        
	RadialForce->bImpulseVelChange = true;    
	RadialForce->bAutoActivate = false; 
	RadialForce->bIgnoreOwningActor = true;

	// Physics effect
	RadialForce->AddCollisionChannelToAffect(ECC_PhysicsBody);
}

void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();

	// Hook the hit event to the intact mesh
	IntactMesh->OnComponentHit.AddDynamic(this, &AExplosiveBarrel::OnIntactHit);

	// Apply radius/impulse 
	RadialForce->Radius = ExplosionRadius;
	RadialForce->ImpulseStrength = ExplosionImpulseStrength;
}


void AExplosiveBarrel::OnIntactHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{


	//if the bullet hits the barrel it explodes and destoys the basic mesh for it
	if (OtherActor->IsA(AProjectileBullet::StaticClass()))
	{
		Explode();

		OtherActor->Destroy();   
	}

}

void AExplosiveBarrel::Explode()
{
	bExploded = true;

	// Swap meshes from the basic barrel mesh to the broken one
	IntactMesh->SetHiddenInGame(true);    //sets the barrel mesh hidden after explosion
	IntactMesh->SetVisibility(false);        //sets the barrel mesh not visible
	IntactMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BrokenMesh->SetHiddenInGame(false);     //when the barrel explodes the broken mesh is not hidded 
	BrokenMesh->SetVisibility(true);           //sets the broken mesh visible		
	BrokenMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);    

	// Place broken mesh exactly where the intact one was
	BrokenMesh->SetWorldTransform(IntactMesh->GetComponentTransform());

	// Fire impulse from center of barrel
	RadialForce->FireImpulse();


	// Small impulse kick when the barrel is hitted
	BrokenMesh->AddImpulse(FVector(0, 0, 1) * 200.f);


	//Explosion Sound when the barrel gets hit by the projectile bullet
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
}
