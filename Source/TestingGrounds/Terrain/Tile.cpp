// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "engine/World.h"
#include "DrawDebugHelpers.h"
#include "components/HierarchicalInstancedStaticMeshComponent.h"
#include "engine/StaticMesh.h"

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
	
	for (auto Detail : DetailMeshes)
	{
		if (Detail.DetailMesh)
		{
			auto DetailComponent = NewObject<UHierarchicalInstancedStaticMeshComponent>(this, Detail.DetailMesh->GetFName());
			DetailComponent->RegisterComponent();
			DetailComponent->OnComponentCreated();
			DetailComponent->AttachTo(GetRootComponent());
			DetailComponents.Add(DetailComponent);
			DetailComponent->SetStaticMesh(Detail.DetailMesh);
			for (int32 InstanceInc = 0; InstanceInc < Detail.NumInstances; InstanceInc++)
			{
				FRotator RandomRotation = FRotator(0,FMath::RandRange(0.0f, 360.0f),0);
				FVector RandomLocation = GetRandomLocation();
				DetailComponent->AddInstance(FTransform(RandomRotation, RandomLocation, FVector(1)));
			}
			
		}
	}

}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawnCount, int32 MaxSpawnCount , float MinScaleValue , float MaxScaleValue)
{
	int32 NumToSpawn = FMath::RandRange(MinSpawnCount, MaxSpawnCount);
	
	//Get Actor Length
	auto TempActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	auto Bounds = TempActor->GetComponentsBoundingBox();
	FVector ActorSize = Bounds.GetSize();
	float Length = FMath::Max3(ActorSize.X, ActorSize.Y, ActorSize.Z);
	TempActor->Destroy();
	
	for(int32 i = 0; i < NumToSpawn; i++)
	{
		float ScaleValue = FMath::RandRange(MinScaleValue, MaxScaleValue);
		float Radius = Length / 2.0f * ScaleValue;

		FVector SpawnLocation;
		if (FindEmptyLocation(SpawnLocation, Radius, 10))
		{
			FRotator Rotator = FRotator(0, FMath::RandRange(0.0f, 360.0f), 0);
			PlaceActor(ToSpawn, SpawnLocation, Rotator, ScaleValue);
		}
	}
}

AActor* ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector Location, FRotator Rotation, float scale)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn, Location, FRotator::ZeroRotator);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	Spawned->SetActorRotation(Rotation);
	Spawned->SetActorScale3D(FVector(scale, scale, scale));
	return Spawned;
}

FVector ATile::GetRandomLocation()
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);
	FVector RandomLocation = FMath::RandPointInBox(Bounds);
	return RandomLocation;
}

bool ATile::FindEmptyLocation(FVector& OutLocation, float Radius = 500, int32 MaxAttempts = 10)
{
	for (int32 inc = 0; inc < MaxAttempts; inc++)
	{
		FVector SpawnLocation = GetRandomLocation() + GetActorLocation();
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
	//FColor ResultColor = WasHit ? FColor::Red : FColor::Green;
	//DrawDebugSphere(GetWorld(), Location, Radius, 8, ResultColor, true);
	
	return !WasHit;
}

