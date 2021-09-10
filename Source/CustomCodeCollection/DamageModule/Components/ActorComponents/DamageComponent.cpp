// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "../../Widgets/WorldPositionedWidget/DamageNumbersWidget.h"
#include "../../Characters/DamageableCharacter.h"

// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	DamageChargeVariation.EditorCurveData.AddKey(0.f, 0.3f, true, DamageChargeVariationDefaultHandle1);
	DamageChargeVariation.EditorCurveData.AddKey(1.f, 1.f, true, DamageChargeVariationDefaultHandle2);

	CritChanceChargeVariation.EditorCurveData.AddKey(0.f, 0.3f, true, CritChanceChargeVariationDefaultHandle1);
	CritChanceChargeVariation.EditorCurveData.AddKey(1.f, 1.f, true, CritChanceChargeVariationDefaultHandle2);

	CritMultiplierChargeVariation.EditorCurveData.AddKey(0.f, 0.3f, true, CritMultiplierChargeVariationDefaultHandle1);
	CritMultiplierChargeVariation.EditorCurveData.AddKey(1.f, 1.f, true, CritMultiplierChargeVariationDefaultHandle2);
}


// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UDamageComponent::IsCrit(float Charge)
{
	float CurrentCritChance = CritChance * CritChanceChargeVariation.EditorCurveData.Eval(Charge);
	float DecimalChance = CurrentCritChance - FMath::TruncToFloat(CurrentCritChance);
	return FMath::RandRange(0.f, 1.f) < DecimalChance;
}

float UDamageComponent::GetCritDamage(float Charge, int32& OutCritLvl)
{
	float CurrentCritChance = CritChance * CritChanceChargeVariation.EditorCurveData.Eval(Charge);
	float CurrentCritMult = CritMultiplier * CritMultiplierChargeVariation.EditorCurveData.Eval(Charge);
	float IntegerChance = FMath::TruncToFloat(CurrentCritChance);
	//Damage from "Red crits" like in warframe
	float Result = FMath::Pow(CurrentCritMult, IntegerChance);
	//The last crit that is not garanteed
	bool HasCrit = IsCrit(Charge);
	Result *= 1 + (CurrentCritMult - 1) * HasCrit;
	OutCritLvl = IntegerChance + HasCrit;
	return Result;
}

FDamageCompute UDamageComponent::ComputeFlatDamage(float Charge)
{
	float CurrentDamage = Damage * DamageChargeVariation.EditorCurveData.Eval(Charge);
	int32 CritLvl;
	float DamageAfterCrit = CurrentDamage * GetCritDamage(Charge, CritLvl);
	return FDamageCompute{ DamageAfterCrit, CritLvl, DamageType, 0.f, DamageNumbersWidgetClass };
}

void UDamageComponent::DamageActor(float ChargePercentage, AActor* OtherActor, const FHitResult& Hit, bool IsExplosion)
{
	FDamageCompute FlatDamage = ComputeFlatDamage(ChargePercentage);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
		FString::Printf(TEXT("Damage: %f"), FlatDamage.Damage));
	APawn* OwnerPawn = GetOwner()->GetOwner<APawn>();
	if (OwnerPawn)
	{
		if (ADamageableCharacter* Enemy = Cast<ADamageableCharacter>(OtherActor))
		{
			Enemy->AddDamage(FlatDamage, OwnerPawn->GetController(), OwnerPawn, Hit, IsExplosion);
		}
		else
		{
			UGameplayStatics::ApplyDamage(OtherActor, FlatDamage.Damage, OwnerPawn->GetController(), OwnerPawn, FlatDamage.DamageType);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot Add Damage Because %s 's owner is not a pawn"), *GetOwner()->GetName());
	}
}