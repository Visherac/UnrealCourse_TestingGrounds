// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int NumToSpawn)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);
	
	for(int32 i = 0; i < NumToSpawn; i++)
	{
		FVector SpawnLocation = FMath::RandPointInBox(Bounds) + GetActorLocation();
		FHitResult HitResult;
		bool WasHit = GetWorld()->SweepSingleByChannel(
			HitResult, 
			SpawnLocation, 
			SpawnLocation, 
			FQuat::Identity, 
			ECollisionChannel::ECC_GameTraceChannel2, //custom spawn channel
			FCollisionShape::MakeSphere(300)
		);
		if (WasHit)
		{
			DrawDebugSphere(GetWorld(), SpawnLocation, 300, 8, FColor::Red, true);
		}
		else
		{
			DrawDebugSphere(GetWorld(), SpawnLocation, 300, 8, FColor::Green, true);
		}
		AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn, SpawnLocation, FRotator::ZeroRotator);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));


	}
}

