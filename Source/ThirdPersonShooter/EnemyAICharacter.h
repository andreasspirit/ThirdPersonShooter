#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyAICharacter.generated.h"

class AProjectileBullet;
class USceneComponent;
class USoundBase;

UCLASS()
class THIRDPERSONSHOOTER_API AEnemyAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyAICharacter();

	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Health")
	float Health = 100.f;

	UFUNCTION(BlueprintCallable, Category = "AI|Health")
	bool IsDead() const { return Health <= 0.f; }

	// Shooting
	UFUNCTION(BlueprintCallable, Category = "AI|Combat")
	void ShootPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Combat")
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Combat")
	TSubclassOf<AProjectileBullet> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Combat")
	USoundBase* bullet_sound = nullptr;

protected:
	virtual void BeginPlay() override;

	// Works with UGameplayStatics::ApplyDamage
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;
};
