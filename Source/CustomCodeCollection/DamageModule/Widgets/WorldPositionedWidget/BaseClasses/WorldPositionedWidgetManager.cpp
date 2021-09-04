// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPositionedWidgetManager.h"
#include "WorldPositionedWidgetBase.h"

void AWorldPositionedWidgetManager::DisplayToPlayer(float DeltaTime)
{
	if (APlayerController* OwningPlayer = ManagedWidget->GetOwningPlayer())
	{


		FVector2D OutProjectedScreenLocation;
		bool bSuccessfulProjection =
			OwningPlayer->ProjectWorldLocationToScreen
			(
				UpdateManagedWidgetWorldLocation(DeltaTime),
				OutProjectedScreenLocation
			);


		if (UpdateViewportStatus(bSuccessfulProjection))
		{
			ManagedWidget->SetPositionInViewport
				(
					GetManagedWidgetScreenLocation(OutProjectedScreenLocation, DeltaTime),
					true
				);
		}
	}
}

bool AWorldPositionedWidgetManager::UpdateViewportStatus(bool bSuccessfulProjection)
{
	bool DisplayStatus;
	if (!bSuccessfulProjection)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
		//	FString::Printf(TEXT("!!!!!!!bSuccessfulProjection")));
		DisplayStatus = false;
		if (bManagedWidgetIsBeingDisplayed)
		{
			ManagedWidget->RemoveFromViewport();
			bManagedWidgetIsBeingDisplayed = false;
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green,
		//	FString::Printf(TEXT("bSuccessfulProjection")));
		DisplayStatus = true;
		if (!bManagedWidgetIsBeingDisplayed)
		{
			ManagedWidget->AddToViewport();
			bManagedWidgetIsBeingDisplayed = true;
		}
	}
	return DisplayStatus;
}

FVector AWorldPositionedWidgetManager::UpdateManagedWidgetWorldLocation(float DeltaTime)
{
	if (ManagedWidgetParams.bUseMovementParams)
	{
		if (ManagedWidgetParams.bUseVelocity)
		{
			ManagedWidgetWorldLocation = UpdateManagedWidgetWorldLocationByVelocity(DeltaTime);
		}
	}
	
	return ManagedWidgetWorldLocation;
}

FVector AWorldPositionedWidgetManager::UpdateManagedWidgetWorldLocationByVelocity(float DeltaTime)
{
	return ManagedWidgetWorldLocation + ManagedWidgetParams.Velocity * DeltaTime;
}

FVector2D AWorldPositionedWidgetManager::GetManagedWidgetScreenLocation(FVector2D ProjectedScreenLocation, float DeltaTime)
{
	FVector2D Result = ProjectedScreenLocation - ManagedWidgetParams.ScreenOffSet;
	if (ManagedWidgetParams.bUseMovementParams && ManagedWidgetParams.bUseScreenPosDelta)
	{
		if (ManagedWidgetParams.bUseConstantInterpSpeed)
		{
			CurrentScreenPosDelta = FMath::Vector2DInterpConstantTo(CurrentScreenPosDelta, ManagedWidgetParams.ScreenPosDelta, DeltaTime, ManagedWidgetParams.ScreenPosDeltaInterpSpeed);
		}
		else
		{
			CurrentScreenPosDelta = FMath::Vector2DInterpTo(CurrentScreenPosDelta, ManagedWidgetParams.ScreenPosDelta, DeltaTime, ManagedWidgetParams.ScreenPosDeltaInterpSpeed);
		}
		Result += CurrentScreenPosDelta;
	}
	return Result;
}

void AWorldPositionedWidgetManager::ProcessParamaters(const FWorldPositionedWidgetMovementParams& _ManagedWidgetParams)
{
	ManagedWidgetParams = _ManagedWidgetParams;
	if (_ManagedWidgetParams.bUseMovementParams)
	{
		if (_ManagedWidgetParams.bUseVelocity && _ManagedWidgetParams.bRandomVelocity)
		{
			float VelocityX = FMath::RandRange
			(
				_ManagedWidgetParams.MinRandVelocity.X,
				_ManagedWidgetParams.MaxRandVelocity.X
			);
			float VelocityY = FMath::RandRange
			(
				_ManagedWidgetParams.MinRandVelocity.Y,
				_ManagedWidgetParams.MaxRandVelocity.Y
			);
			float VelocityZ = FMath::RandRange
			(
				_ManagedWidgetParams.MinRandVelocity.Z,
				_ManagedWidgetParams.MaxRandVelocity.Z
			);
			ManagedWidgetParams.Velocity = FVector(VelocityX, VelocityY, VelocityZ);
			ManagedWidgetParams.bRandomVelocity = false;
		}
		else if (_ManagedWidgetParams.bUseScreenPosDelta && _ManagedWidgetParams.bRandomScreenPosDelta)
		{
			float ScreenPosDeltaX = FMath::RandRange
			(
				_ManagedWidgetParams.MinRandScreenPosDelta.X,
				_ManagedWidgetParams.MaxRandScreenPosDelta.X
			);
			float ScreenPosDeltaY = FMath::RandRange
			(
				_ManagedWidgetParams.MinRandScreenPosDelta.Y,
				_ManagedWidgetParams.MaxRandScreenPosDelta.Y
			);

			ManagedWidgetParams.ScreenPosDelta = FVector2D(ScreenPosDeltaX, ScreenPosDeltaY);
			ManagedWidgetParams.bRandomScreenPosDelta = false;
		}
	}
}

// Sets default values
AWorldPositionedWidgetManager::AWorldPositionedWidgetManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldPositionedWidgetManager::BeginPlay()
{
	Super::BeginPlay();

}

void AWorldPositionedWidgetManager::StartManaging(UWorldPositionedWidgetBase* _ManagedWidget, const FVector& _ManagedWidgetWorldLocation, const FWorldPositionedWidgetMovementParams& _ManagedWidgetParams)
{
	ManagedWidget = _ManagedWidget;
	ManagedWidgetWorldLocation = _ManagedWidgetWorldLocation;
	bManagedWidgetIsBeingDisplayed = false;
	ProcessParamaters(_ManagedWidgetParams);

}

// Called every frame
void AWorldPositionedWidgetManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DisplayToPlayer(DeltaTime);
}

