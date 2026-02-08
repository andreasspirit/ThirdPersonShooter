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
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BulletMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float MovementSpeed = 8000.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);

};
