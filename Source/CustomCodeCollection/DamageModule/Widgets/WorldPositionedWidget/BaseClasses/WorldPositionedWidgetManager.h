// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldPositionedWidgetManager.generated.h"

class UWorldPositionedWidgetBase;

USTRUCT(BlueprintType)
struct FWorldPositionedWidgetMovementParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Placement")
	FVector2D ScreenOffSet = FVector2D(64, 16);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bUseMovementParams = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (EditCondition = "bUseMovementParams && !bUseScreenPosDelta"))
	bool bUseVelocity = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (EditCondition = "bUseMovementParams && bUseVelocity && !bRandomVelocity && !bUseScreenPosDelta"))
	FVector Velocity;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (EditCondition = "bUseMovementParams && bUseVelocity && !bUseScreenPosDelta"))
	bool bRandomVelocity = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (EditCondition = "bUseMovementParams && bUseVelocity && bRandomVelocity && !bUseScreenPosDelta"))
	FVector MinRandVelocity;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (EditCondition = "bUseMovementParams && bUseVelocity && bRandomVelocity && !bUseScreenPosDelta"))
	FVector MaxRandVelocity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (EditCondition = "bUseMovementParams && !bUseVelocity"))
	bool bUseScreenPosDelta = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (EditCondition = "bUseMovementParams && !bUseVelocity && bUseScreenPosDelta && !bRandomScreenPosDelta"))
	FVector2D ScreenPosDelta;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (EditCondition = "bUseMovementParams && !bUseVelocity && bUseScreenPosDelta"))
	float ScreenPosDeltaInterpSpeed = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (EditCondition = "bUseMovementParams && !bUseVelocity && bUseScreenPosDelta"))
	bool bUseConstantInterpSpeed = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (EditCondition = "bUseMovementParams && !bUseVelocity && bUseScreenPosDelta"))
	bool bRandomScreenPosDelta = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (EditCondition = "bUseMovementParams && !bUseVelocity && bUseScreenPosDelta && bRandomScreenPosDelta"))
	FVector2D MinRandScreenPosDelta;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (EditCondition = "bUseMovementParams && !bUseVelocity && bUseScreenPosDelta && bRandomScreenPosDelta"))
	FVector2D MaxRandScreenPosDelta;
};

UCLASS()
class CUSTOMCODECOLLECTION_API AWorldPositionedWidgetManager : public AActor
{
	GENERATED_BODY()
	

private:
	friend class UWorldPositionedWidgetBase;

	void DisplayToPlayer(float DeltaTime);
	//true if is being displayed
	bool UpdateViewportStatus(bool bSuccessfulProjection);

	//returns updated value
	FVector UpdateManagedWidgetWorldLocation(float DeltaTime);
	FVector UpdateManagedWidgetWorldLocationByVelocity(float DeltaTime);
	FVector2D GetManagedWidgetScreenLocation(FVector2D ProjectedScreenLocation, float DeltaTime);

	void ProcessParamaters(const FWorldPositionedWidgetMovementParams& _ManagedWidgetParams);
public:	
	// Sets default values for this actor's properties
	AWorldPositionedWidgetManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UWorldPositionedWidgetBase* ManagedWidget = nullptr;

	bool bManagedWidgetIsBeingDisplayed;
	FVector ManagedWidgetWorldLocation;
	FVector2D CurrentScreenPosDelta = FVector2D(0.f, 0.f);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "World Placement|Movement")
	FWorldPositionedWidgetMovementParams ManagedWidgetParams;

	void StartManaging(UWorldPositionedWidgetBase* _ManagedWidget, const FVector& _ManagedWidgetWorldLocation, const FWorldPositionedWidgetMovementParams& _ManagedWidgetParams);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
