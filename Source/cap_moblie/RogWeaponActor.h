// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogWeaponActor.generated.h"

UCLASS()
class CAP_MOBLIE_API ARogWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARogWeaponActor();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<USkeletalMeshComponent*> WeaponMeshPath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<int> Dmg;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<float> DmgRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<int> Speed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<float> Range;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<UParticleSystem*> EffectPath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<UParticleSystem*> FireEffectPath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<USoundBase*> AttackSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
