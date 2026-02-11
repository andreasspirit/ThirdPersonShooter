#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBullet.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class THIRDPERSONSHOOTER_API AProjectileBullet : public AActor
{
	GENERATED_BODY()

public:
	AProjectileBullet();

protected:
	virtual void BeginPlay() override;

private:

	//Mesh for the collision checks
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BulletMesh = nullptr;

	//Projectile movement particle
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement = nullptr;


	//Bullet Speed
	UPROPERTY(EditAnywhere, Category = "Projectile")
	float MovementSpeed = 8000.f;


	//Handles logic on collision
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);

};
