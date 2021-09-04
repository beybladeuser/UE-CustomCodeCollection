// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DamageableCharacter.generated.h"

class UHealthComponent;
struct FDamageCompute;
class ADamageNumberBase;

UCLASS()
class CUSTOMCODECOLLECTION_API ADamageableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADamageableCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* Health;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void AddDamage(FDamageCompute Damage, AController* EventInstigator, AActor* DamageCauser, const FHitResult& Hit, bool bIsExplosion);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
