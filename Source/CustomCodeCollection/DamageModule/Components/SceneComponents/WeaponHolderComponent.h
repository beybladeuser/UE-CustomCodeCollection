// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponHolderComponent.generated.h"

class AWeaponBase;
class UWeaponInfoWidgetBase;

USTRUCT(BlueprintType)
struct FHeldWeaponsSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeldWeaponsSpawnInfo")
	TSubclassOf<AWeaponBase> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeldWeaponsSpawnInfo")
	FTransform Offset;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CUSTOMCODECOLLECTION_API UWeaponHolderComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponHolderComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons")
	TArray<FHeldWeaponsSpawnInfo> HeldWeaponsClasses;

	TArray<AWeaponBase*> HeldWeapons;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (ClampMin = "0"))
	int32 ActiveWeaponIndex = 0;
	//if true ActiveWeaponIndex == -1 == unarmed, this will also make it so that when scrolling the equiped weapons you will scroll through the unharmed state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	bool bUseActiveWeaponIndexEqualMinusOneAsUnharmed = true;
	bool bCurrentActiveWeaponIsAgregate = false;
	bool bCanSwapWeapon = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons|UI")
	TSubclassOf<UWeaponInfoWidgetBase> WeaponInfoWidgetClass;
	UWeaponInfoWidgetBase* WeaponInfoWidget;

	TArray<AWeaponBase*> GetAllHeldWeapons() const;

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetWeaponInfoWidget(UWeaponInfoWidgetBase* NewWeaponInfoWidget);

	UFUNCTION(BlueprintPure)
	AWeaponBase* GetActiveWeapon() const;

	template<class T>
	T* GetActiveWeapon() const;

	UFUNCTION(BlueprintCallable)
	void SwapActiveWeapon(int32 Index);
	UFUNCTION(BlueprintCallable)
	void SwapActiveWeaponByScroll(bool bSrollUp);

	//if bHideOtherWeapons==true hides every weapon and sets the visibility of the active waepon to visible if bDisplay == true, 
	//this isnt called anywhere in this class because you might want to only call this after a holstering animation as ended
	UFUNCTION(BlueprintCallable)
	virtual void SetDisplayOfActiveWeapon(bool bHideOtherWeapons, bool bDisplay = true);

	//AlternateFireID is only usefull if the active weapon is of class AWeaponAgregateBase, if AlternateFireID == -1 then it will be ignored and if the active weapon is of class AWeaponAgregateBase will fire the active fire mode
	UFUNCTION(BlueprintCallable)
	void StartUsingActiveWeapon(int32 AlternateFireID = -1);
	//AlternateFireID is only usefull if the active weapon is of class AWeaponAgregateBase, if AlternateFireID == -1 then it will be ignored and if the active weapon is of class AWeaponAgregateBase will fire the active fire mode
	UFUNCTION(BlueprintCallable)
	void StopUsingActiveWeapon(int32 AlternateFireID = -1);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};

template<class T>
T* UWeaponHolderComponent::GetActiveWeapon() const
{
	return Cast<T>(GetActiveWeapon());
}
