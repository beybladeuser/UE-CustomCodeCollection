// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Components/ActorComponents/AmmoComponent.h"
#include "WeaponBase.generated.h"

UCLASS()
class CUSTOMCODECOLLECTION_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	UAmmoComponent* AmmoComponent = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool CanBeUsed();

	virtual void HandleAmmoComponent(float Charge = 1.f);

	void RefreshAmmoComponentInstance();

public:
	UFUNCTION(BlueprintCallable)
	virtual void StartUsingWeapon();
	UFUNCTION(BlueprintCallable)
	virtual void StopUsingWeapon();

	UFUNCTION(BlueprintCallable)
	virtual void Reload();

	AController* GetOwnerController() const;

	UAmmoComponent* GetAmmoComponent();
	//Usefull to make a weapon that has multiple AWeaponBase that share the same ammo count
	void SetAmmoComponentInstance(UAmmoComponent* AmmoComponentInst);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
