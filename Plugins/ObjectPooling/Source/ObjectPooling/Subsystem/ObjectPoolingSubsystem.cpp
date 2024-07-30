// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolingSubsystem.h"

void UObjectPoolingSubsystem::SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation,
	AActor*& SpawnedActor)
{
	SpawnedActor = SpawnFromPool<AActor>(PoolClass, Location, Rotation);
}

void UObjectPoolingSubsystem::ReturnToPool(AActor* Poolable)
{
	const UClass* PoolableClass = Poolable->GetClass();
	if(PoolableClass->ImplementsInterface(UPoolable::StaticClass()))
	{
		IPoolable::Execute_OnReturnToPool(Poolable);
		FPoolArray* ObjectPool = ObjectPools.Find(PoolableClass);
		ObjectPool->Add(Poolable);
	}
	else
	{
		Poolable->Destroy();
	}
}
