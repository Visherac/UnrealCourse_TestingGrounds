// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "EngineUtils.h"
#include "engine/World.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "ActorPool.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavPool = CreateDefaultSubobject<UActorPool>(FName("ActorPool"));
}

void AInfiniteTerrainGameMode::BeginPlay()
{
	Super::BeginPlay();
}


void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	TActorIterator<ANavMeshBoundsVolume> NavBoundsIter = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (NavBoundsIter)
	{
		AddToPool(*NavBoundsIter);
		++NavBoundsIter;
	}
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume* BoundsVolume)
{
	NavPool->Add(BoundsVolume);
}


