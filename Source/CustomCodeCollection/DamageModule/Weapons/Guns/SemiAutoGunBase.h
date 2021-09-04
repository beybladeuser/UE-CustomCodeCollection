// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunBase.h"
#include "SemiAutoGunBase.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMCODECOLLECTION_API ASemiAutoGunBase : public AGunBase
{
	GENERATED_BODY()
	
public:
	virtual void StartUsingWeapon() override;
};
