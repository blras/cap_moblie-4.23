// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Engine/SkeletalMesh.h"
#include "WeaponsDatatable.generated.h"
USTRUCT(BlueprintType)
struct FWeaponsTableRow : public FTableRowBase
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSoftObjectPtr<USkeletalMesh> WeaponMeshPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		int Dmg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float DmgRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSoftObjectPtr<UParticleSystem> EffectPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSoftObjectPtr<UParticleSystem> FireEffectPath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
		TSoftObjectPtr<USoundBase> AttackSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		FVector Scale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		FRotator Rotation;
};
UCLASS()
class CAP_MOBLIE_API AWeaponsDatatable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponsDatatable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
