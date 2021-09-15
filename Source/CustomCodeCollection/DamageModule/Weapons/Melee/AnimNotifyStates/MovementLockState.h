// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MovementLockState.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMCODECOLLECTION_API UMovementLockState : public UAnimNotifyState
{
	GENERATED_BODY()
	
private:
	AController* MeshCompOwnerController = nullptr;

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
