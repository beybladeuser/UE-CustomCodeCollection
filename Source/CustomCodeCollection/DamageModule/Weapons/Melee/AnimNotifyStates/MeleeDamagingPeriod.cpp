// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeDamagingPeriod.h"
#include "../../../Components/SceneComponents/WeaponHolderComponent.h"
#include "../MeleeBase.h"

void UMeleeDamagingPeriod::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	TArray<UWeaponHolderComponent*> WeaponHolders;
	MeshComp->GetOwner()->GetComponents(WeaponHolders, true);

	AMeleeBase* MeleeWeapon = nullptr;
	if (WeaponHolders.Num() && WeaponHolders[0])
	{
		MeleeWeapon = WeaponHolders[0]->GetActiveWeapon<AMeleeBase>();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Actor %s does not contain a UWeaponHolderComponent so UMeleeDamagingPeriod is useless"), *MeshComp->GetOwner()->GetName());
		return;
	}

	if (MeleeWeapon)
	{
		MeleeWeapon->SetCollisionTurnedOff(false);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Actor %s active weapon is not of type AMeleeBase so UMeleeDamagingPeriod is useless"), *MeshComp->GetOwner()->GetName());
	}
}

void UMeleeDamagingPeriod::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	TArray<UWeaponHolderComponent*> WeaponHolders;
	MeshComp->GetOwner()->GetComponents(WeaponHolders, true);

	AMeleeBase* MeleeWeapon = nullptr;
	if (WeaponHolders.Num() && WeaponHolders[0])
	{
		MeleeWeapon = WeaponHolders[0]->GetActiveWeapon<AMeleeBase>();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Actor %s does not contain a UWeaponHolderComponent so UMeleeDamagingPeriod is useless"), *MeshComp->GetOwner()->GetName());
		return;
	}

	if (MeleeWeapon)
	{
		MeleeWeapon->SetCollisionTurnedOff(true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Actor %s active weapon is not of type AMeleeBase so UMeleeDamagingPeriod is useless"), *MeshComp->GetOwner()->GetName());
	}
}