// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementLockState.h"

void UMovementLockState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	AActor* MeshCompOwnerActor = MeshComp->GetOwner();
	if (!MeshCompOwnerActor) { return; }

	APawn* MeshCompOwnerPawn = Cast<APawn>(MeshCompOwnerActor);
	if (MeshCompOwnerPawn)
	{
		MeshCompOwnerController = MeshCompOwnerPawn->GetController();
		if (MeshCompOwnerController)
		{
			MeshCompOwnerController->SetIgnoreMoveInput(true);
		}
	}
}

void UMovementLockState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	AActor* MeshCompOwnerActor = MeshComp->GetOwner();
	if (!MeshCompOwnerActor) { return; }

	if (MeshCompOwnerController)
	{
		MeshCompOwnerController->SetIgnoreMoveInput(false);
	}
}