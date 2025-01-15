// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Engine/SkeletalMesh.h"
#include "EnemyDataTable.generated.h"
USTRUCT(BlueprintType)
struct FEnemyTableRow : public FTableRowBase
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TSoftObjectPtr<USkeletalMesh> CharacterMeshPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TSoftObjectPtr<USkeletalMesh> WeaponMeshPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		int Dmg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float DmgRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float Hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		int Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TSoftObjectPtr<UParticleSystem> EffectPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TSoftObjectPtr<UParticleSystem> HitEffectPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TSoftClassPtr<UClass> AnimPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float Size;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		int Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		int Location;
};
UCLASS()
class CAP_MOBLIE_API AEnemyDataTable : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AEnemyDataTable();
};
