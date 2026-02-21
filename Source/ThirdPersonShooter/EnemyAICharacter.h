#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include"GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "EnemyAICharacter.generated.h"


//class AProjectileBullet;
class USceneComponent;
class USoundBase;
class USpringArmComponent;
class UCameraComponent;
UCLASS()
class THIRDPERSONSHOOTER_API AEnemyAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyAICharacter();

	// Health
	UPROPERTY(EditAnywhere,Category = "AI|Health")
	float Health = 100.f;

	UFUNCTION(BlueprintCallable, Category = "AI|Health")
	bool IsDead() const { return Health <= 0.f; }

	// Shooting
	UFUNCTION(BlueprintCallable, Category = "AI|Combat")
	void ShootPlayer();

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Combat")
	//USceneComponent* ProjectileSpawnPoint;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Combat")
	//TSubclassOf<AProjectileBullet> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Combat")
	USoundBase* bullet_sound = nullptr;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	// RAYCASTING PROPERTIES
	// Maximum range of the raycast
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat|Raycasting")
	float RaycastRange;

	// Damage dealt by each shot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat|Raycasting")
	float RaycastDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float FireRate;  // Time between shots in seconds

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bCanFire;  

	FTimerHandle FireRateTimerHandle;  // Timer for fire rate


	


protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

      // Reset fire cooldown
       void ResetFire();
};
