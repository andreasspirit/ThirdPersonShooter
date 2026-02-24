#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosiveBarrel.generated.h"

class URadialForceComponent;
class UParticleSystem;
class USoundBase;
UCLASS()
class THIRDPERSONSHOOTER_API AExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	AExplosiveBarrel();

protected:
	virtual void BeginPlay() override;

	// Intact mesh (visible at start)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Barrel")
	UStaticMeshComponent* IntactMesh;

	// Broken mesh (hidden at start)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Barrel")
	UStaticMeshComponent* BrokenMesh;

	// Radial force for explosion push
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Barrel")
	URadialForceComponent* RadialForce;

	// Explosion tuning
	UPROPERTY(EditAnywhere, Category = "Explosion")
	float ExplosionImpulseStrength = 2500.f;


	//Explosion radius
	UPROPERTY(EditAnywhere, Category = "Explosion")
	float ExplosionRadius = 400.f;


	//Define the sound to play when explosion happens
	UPROPERTY(EditAnywhere, Category = "Explosion")
	USoundBase* ExplosionSound;

	// Prevent exploding twice
	bool bExploded = false;


	//Function declaration of interacthit and ComponentHit for handling collision between 
	// the barrel and the projectile bullet
	UFUNCTION()
	void OnIntactHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void Explode();
};
