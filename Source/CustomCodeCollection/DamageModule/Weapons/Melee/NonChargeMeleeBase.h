// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MeleeBase.h"
#include "NonChargeMeleeBase.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMCODECOLLECTION_API ANonChargeMeleeBase : public AMeleeBase
{
	GENERATED_BODY()
	
public:
	virtual void StartUsingWeapon() override;
};
