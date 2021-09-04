// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WorldPositionedWidgetManager.h"
#include "WorldPositionedWidgetBase.generated.h"

//adapted from https://forums.unrealengine.com/t/damage-displayed/99716/2

class AWorldPositionedWidgetManager;
struct FWorldPositionedWidgetMovementPrams;

/**
 * 
 */
UCLASS()
class CUSTOMCODECOLLECTION_API UWorldPositionedWidgetBase : public UUserWidget
{
	GENERATED_BODY()

private:
	AWorldPositionedWidgetManager* WidgetManager;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "World Placement|Movement")
	FWorldPositionedWidgetMovementParams DefaultParams;

public:
	//You need to call this function for the widget to work propoerly
	UFUNCTION(BlueprintCallable)
	void PlaceAtWorldLocation(APlayerController* _OwningPlayer, const FVector& _WorldLocation);

	UFUNCTION(BlueprintCallable)
	FWorldPositionedWidgetMovementParams GetMovementParams();

	//if bRandomVelocity or bRandomScreenPosDelta are true it will recalculate random values
	UFUNCTION(BlueprintCallable)
	void SetMovementParams(const FWorldPositionedWidgetMovementParams& NewParams);

	UFUNCTION(BlueprintCallable)
	void StopRendering();
};
