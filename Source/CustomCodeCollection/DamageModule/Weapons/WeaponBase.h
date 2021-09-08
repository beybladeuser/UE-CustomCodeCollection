// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Components/ActorComponents/AmmoComponent.h"
#include "WeaponBase.generated.h"



UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	OneHandedSinglePistol	UMETA(DisplayName = "OneHandedSinglePistol"),
	TwoHandedSinglePistol	UMETA(DisplayName = "TwoHandedSinglePistol"),
	OneHandedDoublePistol	UMETA(DisplayName = "OneHandedDoublePistol"),
	Rifle					UMETA(DisplayName = "Rifle"),
	RocketLaucher			UMETA(DisplayName = "RocketLaucher"),
	OneHandedSingleSword	UMETA(DisplayName = "OneHandSingleSword"),
	TwoHandedSingleSword	UMETA(DisplayName = "TwoHandedSingleSword"),
	OneHandedDoubleSword	UMETA(DisplayName = "TwoHandedSingleSword"),
	Spear					UMETA(DisplayName = "Spear"),
	Shield					UMETA(DisplayName = "Shield")
};


UCLASS()
class CUSTOMCODECOLLECTION_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* Mesh;

	//Designed for a animBP to decide how the weapon is held
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	EWeaponType WeaponType;

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

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EWeaponType GetWeaponType() { return WeaponType; }

	AController* GetOwnerController() const;

	UAmmoComponent* GetAmmoComponent();
	//Usefull to make a weapon that has multiple AWeaponBase that share the same ammo count
	void SetAmmoComponentInstance(UAmmoComponent* AmmoComponentInst);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
