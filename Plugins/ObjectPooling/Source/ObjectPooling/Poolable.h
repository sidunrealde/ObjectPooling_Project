// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Poolable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPoolable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OBJECTPOOLING_API IPoolable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Called when spawning object from pool
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Object Pool")
	void OnSpawnFromPool();
	// Called when returning object to pool
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Object Pool")
	void OnReturnToPool();

};
