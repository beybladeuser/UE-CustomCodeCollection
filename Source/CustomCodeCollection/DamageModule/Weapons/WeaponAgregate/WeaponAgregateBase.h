// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../WeaponBase.h"
#include "WeaponAgregateBase.generated.h"

class AWeaponBase;

UCLASS()
class CUSTOMCODECOLLECTION_API AWeaponAgregateBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponAgregateBase();

protected:
	//if true 2 or more fire modes can be fired at the same time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alternate Fire Settings")
	bool bAllowConcurentFiring = false;

	bool bHasRecomputedAmmoInstance = false;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	TArray<UChildWeaponBaseComponent*> GetAllWeaponsChildren();

	AWeaponBase* GetWeaponByID(int32 ID);

public:
	virtual void SetOwner(AActor* NewOwner) override;

	virtual void SetActorHiddenInGame(bool bNewHidden) override;

	virtual void StartUsingWeapon() override;
	virtual void StopUsingWeapon() override;

	UFUNCTION(BlueprintCallable)
	virtual void StartUsingChildWeapon(int32 FireModeID);
	UFUNCTION(BlueprintCallable)
	virtual void StopUsingChildWeapon(int32 FireModeID);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
