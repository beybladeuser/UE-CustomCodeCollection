// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ContinuousProjectileBase.h"
#include "CapsuleProjectileBase.generated.h"

class UCapsuleComponent;

/**
 * 
 */
UCLASS()
class CUSTOMCODECOLLECTION_API ACapsuleProjectileBase : public AContinuousProjectileBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* Collision;

	virtual TArray<AActor*> GetActorsToDamage() override;

public:
	ACapsuleProjectileBase();
};
