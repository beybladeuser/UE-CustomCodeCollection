// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponAgregateBase.h"
#include "FireModeToggleAgregateBase.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMCODECOLLECTION_API AFireModeToggleAgregateBase : public AWeaponAgregateBase
{
	GENERATED_BODY()
	
protected:
	int32 ActiveFireMode = 0;

	//Toggle between the different UChildWeaponBaseComponent
	void ScrollFireMode(bool bScrollForward);

public:
	//if FireModeID != 0 it will toggle to the next FireMode, if FireModeID == 0 it will fire the current FireMode
	virtual void StartUsingChildWeapon(int32 FireModeID) override;
	virtual void StopUsingChildWeapon(int32 FireModeID) override;
};
