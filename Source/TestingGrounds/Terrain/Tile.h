// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT(BlueprintType)
struct FSpawnPosition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SETUP)
	FVector Location;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SETUP)
	float Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SETUP)
	float Scale;

	FSpawnPosition()
	{
		Location = FVector();
		Rotation = 0.0f;
		Scale = 1.0f;
	}
};

USTRUCT(BlueprintType)
struct FMeshDetails
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	UStaticMesh* DetailMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	int32 NumInstances;

	FMeshDetails()
	{
		DetailMesh = nullptr;
		NumInstances = 0;
	}
};


class UActorPool;

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetNavMeshPool(UActorPool* ActorPool);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere, Category = Setup)
	class UActorPool* NavPool = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Spawning)
	FVector MinBounds;
	
	UPROPERTY(EditDefaultsOnly, Category = Spawning)
	FVector MaxBounds;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	TArray<AActor*> PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawnCount =1, int32 MaxSpawnCount =1, float MinScaleValue =1.0f, float MaxScaleValue = 1.0f);

	UFUNCTION(BlueprintCallable, Category = Setup)
	TArray<APawn*> PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 MinSpawnCount, int32 MaxSpawnCount);

	
private:
	AActor* NavMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TArray<FMeshDetails> DetailMeshes;

	UPROPERTY(VisibleDefaultsOnly)
	TArray<class UHierarchicalInstancedStaticMeshComponent*> DetailComponents;

	template<class T>
	TArray<T*> RandomlyPlaceObjects(TSubclassOf<T> ToSpawn, int32 MinSpawnCount = 1, int32 MaxSpawnCount = 1, float MinScaleValue = 1.0f, float MaxScaleValue = 1.0f);

	AActor* PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& Position);

	FVector GetRandomLocation();

	bool FindEmptyLocation(FVector& OutLocation, float Radius, int32 MaxAttempts);

	bool IsValidLocation(FVector Location, float Radius);

};

