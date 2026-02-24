// Fill out your copyright notice in the Description page of Project Settings.


#include "MedKit.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MainCharacter.h"

// Sets default values
AMedKit::AMedKit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(50.0f);

	// Set collision settings for overlap
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	// Create mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MedKit"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);  // Visual only

	// Set default heal amount
	Healing = 20.0f;
}

// Called when the game starts or when spawned
void AMedKit::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMedKit::OnOverlapBegin);
}

// Called every frame
void AMedKit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMedKit::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if player picked it up
	AMainCharacter* Player = Cast<AMainCharacter>(OtherActor);
	if (Player)
	{
		// Heal the player
		Player->Heal(Healing);

		// Destroy the pickup
		Destroy();
	}
}

