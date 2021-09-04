// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/WorldPositionedWidgetBase.h"
#include "../../Components/ActorComponents/DamageComponent.h"
#include "DamageNumbersWidget.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMCODECOLLECTION_API UDamageNumbersWidget : public UWorldPositionedWidgetBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetDamageNumber(FDamageCompute Damage);
};
