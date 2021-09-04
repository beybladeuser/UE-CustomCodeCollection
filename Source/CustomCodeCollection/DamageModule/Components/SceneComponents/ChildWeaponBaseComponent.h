// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ChildWeaponBaseComponent.generated.h"

class AWeaponBase;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CUSTOMCODECOLLECTION_API UChildWeaponBaseComponent : public USceneComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AWeaponBase> WeaponClass;

	AWeaponBase* Weapon;

	virtual void BeginPlay() override;

public:
	template<class T>
	T* GetChild();

	UFUNCTION(BlueprintCallable)
	void StartUsingChildWeapon();
	UFUNCTION(BlueprintCallable)
	void StopUsingChildWeapon();
};

template<class T>
inline T* UChildWeaponBaseComponent::GetChild()
{
	return Cast<T>(Weapon);
}
