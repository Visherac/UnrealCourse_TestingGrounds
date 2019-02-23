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

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 NumToSpawn)
{
	for(int32 i = 0; i < NumToSpawn; i++)
	{
		FVector SpawnLocation;
		if (FindEmptyLocation(SpawnLocation, 500.0f, 10))
		{
			PlaceActor(ToSpawn, SpawnLocation);
		}
	}
}

AActor* ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector Location)
{

	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn, Location, FRotator::ZeroRotator);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	return Spawned;
}

bool ATile::FindEmptyLocation(FVector& OutLocation, float Radius = 500, int32 MaxAttempts = 10)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);
	for (int32 inc = 0; inc < MaxAttempts; inc++)
	{
		FVector SpawnLocation = FMath::RandPointInBox(Bounds) + GetActorLocation();
		if (IsValidLocation(SpawnLocation, Radius))
		{
			OutLocation = SpawnLocation;
			return true;
		}
	}
	return false;

}

bool ATile::IsValidLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	bool WasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Location,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, //custom spawn channel
		FCollisionShape::MakeSphere(Radius)
	);
	FColor ResultColor = WasHit ? FColor::Red : FColor::Green;
	DrawDebugSphere(GetWorld(), Location, Radius, 8, ResultColor, true);
	
	return !WasHit;
}

