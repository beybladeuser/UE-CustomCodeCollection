// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPositionedWidgetBase.h"

void UWorldPositionedWidgetBase::PlaceAtWorldLocation(APlayerController* _OwningPlayer,const FVector& _WorldLocation)
{
	if (!_OwningPlayer) 
	{
		UE_LOG(LogTemp, Error, TEXT("Widget %s was given a non valid _OwningPlayer"), *GetName());
		return; 
	}

	RemoveFromViewport();

	SetOwningPlayer(_OwningPlayer);

	FTransform Transform = FTransform();
	WidgetManager = _OwningPlayer->GetWorld()->SpawnActor<AWorldPositionedWidgetManager>
		(
			AWorldPositionedWidgetManager::StaticClass(),
			Transform
		);
	WidgetManager->StartManaging(this, _WorldLocation, DefaultParams);
}

FWorldPositionedWidgetMovementParams UWorldPositionedWidgetBase::GetMovementParams()
{
	if (!WidgetManager)
	{
		UE_LOG(LogTemp, Error, TEXT("UWorldPositionedWidgetBase %s has stopped rendering, therefore it cant get or set MovementParams"), *GetName());
		return FWorldPositionedWidgetMovementParams();
	}
	return WidgetManager->ManagedWidgetParams;
}

void UWorldPositionedWidgetBase::SetMovementParams(const FWorldPositionedWidgetMovementParams& NewParams)
{
	if (!WidgetManager)
	{
		UE_LOG(LogTemp, Error, TEXT("UWorldPositionedWidgetBase %s has stopped rendering, therefore it cant get or set MovementParams"), *GetName());
		return;
	}
	WidgetManager->ProcessParamaters(NewParams);
}

void UWorldPositionedWidgetBase::StopRendering()
{
	if (!WidgetManager)
	{
		UE_LOG(LogTemp, Error, TEXT("UWorldPositionedWidgetBase %s has already stopped rendering"), *GetName());
		return;
	}
	WidgetManager->GetWorld()->DestroyActor(WidgetManager);

	RemoveFromViewport();
}