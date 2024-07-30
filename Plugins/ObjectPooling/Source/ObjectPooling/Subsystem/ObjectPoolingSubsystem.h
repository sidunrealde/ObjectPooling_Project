// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPooling/Poolable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ObjectPoolingSubsystem.generated.h"



// Struct that contains array of pooled objects
USTRUCT()
struct FPoolArray
{
	GENERATED_BODY()
	// Array of pooled actors
	UPROPERTY()
	TArray<AActor*> ObjectPool;

	// Returns if the ObjectPool array is empty
	bool IsEmpty() const
	{
		return ObjectPool.IsEmpty();
	}
	// Pops Actor from array
	AActor* Pop()
	{
		return ObjectPool.Pop();
	}
	// Adds actor to object pool
	void Add(AActor* ActorToAdd)
	{
		ObjectPool.Add(ActorToAdd);
	}
};
/**
 * 
 */
UCLASS()
class OBJECTPOOLING_API UObjectPoolingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Pool Subsystem", meta = (DeterminesOutputType = "PoolClass", DynamicOutputParam = "SpawnedActor"))
	void SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation, AActor*& SpawnedActor);

	UFUNCTION(BlueprintCallable, Category = "Pool Subsystem")
	void ReturnToPool(AActor* Poolable);
	
	template<typename T>
	T* SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation);
	
	// Map to which all types of pooled objects get added to
	UPROPERTY()
	TMap<UClass*, FPoolArray> ObjectPools;
};

template <typename T>
T* UObjectPoolingSubsystem::SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation)
{
	T* PooledActor = nullptr;

	if(PoolClass.Get()->ImplementsInterface(UPoolable::StaticClass()))
	{
		FPoolArray& ObjectPool = ObjectPools.FindOrAdd(PoolClass);
		if(ObjectPool.IsEmpty())
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			PooledActor = GetWorld()->SpawnActor<T>(PoolClass, Location, Rotation, SpawnParameters);
		}
		else
		{
			PooledActor = CastChecked<T>(ObjectPool.Pop());
			PooledActor->SetActorLocationAndRotation(Location, Rotation);
		}
		IPoolable::Execute_OnSpawnFromPool(PooledActor);
	}

	return PooledActor;
	
}