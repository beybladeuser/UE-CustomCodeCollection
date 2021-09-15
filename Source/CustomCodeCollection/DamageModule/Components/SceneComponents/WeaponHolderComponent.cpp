// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponHolderComponent.h"
#include "../../Weapons/WeaponBase.h"
#include "../../Weapons/WeaponAgregate/WeaponAgregateBase.h"
#include "../../Widgets/DamageModuleInfo/WeaponInfoWidgetBase.h"

// Sets default values for this component's properties
UWeaponHolderComponent::UWeaponHolderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

TArray<AWeaponBase*> UWeaponHolderComponent::GetAllHeldWeapons() const
{
	if (!HeldWeapons.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("No Weapons associated with UWeaponHolderComponent of actor %s, dont forget to use the function AddHeldWeapon() in the blueprint BeginPlay of actor %s"), *GetOwner()->GetName(), *GetOwner()->GetName());
	}
	return HeldWeapons;
}

// Called when the game starts
void UWeaponHolderComponent::BeginPlay()
{
	Super::BeginPlay();

	int32 i = 0;
	HeldWeapons.Init(nullptr, HeldWeaponsClasses.Num());
	for (FHeldWeaponsSpawnInfo WeaponClass : HeldWeaponsClasses)
	{
		HeldWeapons[i] = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass.WeaponClass);
		if (HeldWeapons[i])
		{
			HeldWeapons[i]->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
			HeldWeapons[i]->SetOwner(GetOwner());
			HeldWeapons[i]->SetActorRelativeTransform(WeaponClass.Offset);
			HeldWeapons[i]->SetActorHiddenInGame(true);
		}
		i++;
	}
	SwapActiveWeapon(ActiveWeaponIndex);
	SetDisplayOfActiveWeapon(false, false);
	
	if (WeaponInfoWidgetClass)
	{
		WeaponInfoWidget = Cast<UWeaponInfoWidgetBase>(CreateWidget(GetWorld(), WeaponInfoWidgetClass));
	}
	if (WeaponInfoWidget)
	{
		WeaponInfoWidget->AddToViewport();
		WeaponInfoWidget->InitWeapons(ActiveWeaponIndex, GetAllHeldWeapons());
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
			FString::Printf(TEXT("WeaponInfoWidget")));
	}
}

void UWeaponHolderComponent::SetWeaponInfoWidget(UWeaponInfoWidgetBase* NewWeaponInfoWidget)
{
	WeaponInfoWidget = NewWeaponInfoWidget;
}

AWeaponBase* UWeaponHolderComponent::GetActiveWeapon() const
{
	TArray<AWeaponBase*> AllHeldWeapons = GetAllHeldWeapons();

	if ( 0 <= ActiveWeaponIndex && ActiveWeaponIndex < AllHeldWeapons.Num() )
	{
		return AllHeldWeapons[ActiveWeaponIndex];
	}
	else if (ActiveWeaponIndex != -1 && bUseActiveWeaponIndexEqualMinusOneAsUnharmed)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid ActiveWeaponIndex in UWeaponHolderComponent of Actor %s"), *GetOwner()->GetName())
	}
	return nullptr;
}

void UWeaponHolderComponent::SwapActiveWeapon(int32 Index)
{
	if (!bCanSwapWeapon)
	{
		return;
	}
	int32 MinClamp = bUseActiveWeaponIndexEqualMinusOneAsUnharmed ? -1 : 0;
	ActiveWeaponIndex = FMath::Clamp(Index, MinClamp, GetAllHeldWeapons().Num() - 1);
	AWeaponBase* SimpleWeapon = GetActiveWeapon();
	if (Cast<AWeaponAgregateBase>(SimpleWeapon))
	{
		bCurrentActiveWeaponIsAgregate = true;
	}
	else
	{
		bCurrentActiveWeaponIsAgregate = false;
	}

	if (WeaponInfoWidget)
	{
		WeaponInfoWidget->NotifyWeaponSwap(ActiveWeaponIndex);
	}
}

void UWeaponHolderComponent::SwapActiveWeaponByScroll(bool bSrollUp)
{
	if (!bCanSwapWeapon)
	{
		return;
	}
	int32 Sign = -1;
	if (bSrollUp)
	{
		Sign = 1;
	}
	int32 NewIndex = ActiveWeaponIndex + Sign;
	int32 MinClamp = bUseActiveWeaponIndexEqualMinusOneAsUnharmed ? -1 : 0;
	if (NewIndex >= GetAllHeldWeapons().Num())
	{
		NewIndex = MinClamp;
	}
	else if (NewIndex < MinClamp)
	{
		NewIndex = GetAllHeldWeapons().Num() - 1;
	}
	SwapActiveWeapon(NewIndex);
}

void UWeaponHolderComponent::SetDisplayOfActiveWeapon(bool bHideOtherWeapons, bool bDisplay)
{
	if (bHideOtherWeapons)
	{
		for (AWeaponBase* HeldWeapon : GetAllHeldWeapons())
		{
			if (HeldWeapon)
			{
				HeldWeapon->SetActorHiddenInGame(true);
			}
		}
	}
	AWeaponBase* ActiveWeapon = GetActiveWeapon();
	if (ActiveWeapon)
	{
		ActiveWeapon->SetActorHiddenInGame(!bDisplay);
	}
}

void UWeaponHolderComponent::StartUsingActiveWeapon(int32 AlternateFireID)
{
	bCanSwapWeapon = false;
	AWeaponBase* WeaponToFire = GetActiveWeapon();
	if (WeaponToFire)
	{
		if (AlternateFireID <= -1 || !bCurrentActiveWeaponIsAgregate)
		{
			WeaponToFire->StartUsingWeapon();
		}
		else
		{
			AWeaponAgregateBase* WeaponAgregateToFire = Cast<AWeaponAgregateBase>(WeaponToFire);
			WeaponAgregateToFire->StartUsingChildWeapon(AlternateFireID);
		}
	}
	
}

void UWeaponHolderComponent::StopUsingActiveWeapon(int32 AlternateFireID)
{
	AWeaponBase* WeaponToFire = GetActiveWeapon();
	if (WeaponToFire)
	{
		if (AlternateFireID <= -1 || !bCurrentActiveWeaponIsAgregate)
		{
			WeaponToFire->StopUsingWeapon();
		}
		else
		{
			AWeaponAgregateBase* WeaponAgregateToFire = Cast<AWeaponAgregateBase>(WeaponToFire);
			WeaponAgregateToFire->StopUsingChildWeapon(AlternateFireID);
		}
	}
	bCanSwapWeapon = true;
}

// Called every frame
void UWeaponHolderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

