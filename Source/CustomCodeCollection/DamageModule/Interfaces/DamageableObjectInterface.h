// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../Components/ActorComponents/DamageComponent.h"
#include "DamageableObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageableObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CUSTOMCODECOLLECTION_API IDamageableObjectInterface
{
	GENERATED_BODY()

public:
	//Custom damage applyer function should only be used to call the function with the same name of the UHealthComponent class 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddDamage(FDamageCompute Damage, AController* EventInstigator, AActor* DamageCauser, const FHitResult& Hit, bool bIsExplosion);
	//This is called by UHealthComponent and should handle what happens when the actor dies
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void NotifyDeath();
};
