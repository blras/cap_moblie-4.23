// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/SkeletalMesh.h"
#include "RogEnemyActor.generated.h"

UCLASS()
class CAP_MOBLIE_API ARogEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARogEnemyActor();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<USkeletalMesh*> CharacterMeshPath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<USkeletalMesh*> WeaponMeshPath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<int> Dmg;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<float> DmgRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<int> Hp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<int> Speed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<float> Range;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<UParticleSystem*> EffectPath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<UParticleSystem*> HitEffectPath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<UClass*> AnimPath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<UAnimMontage*> MontagePath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<UAnimMontage*> DeathMontagePath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<float> Size;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<int> Type;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<int> Location;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<USoundBase*> AttackSound;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
		TArray<USoundBase*> DeathSoundPath;

protected:
	// Called when the game starts or when spawned
	int envitr;
	int MaxEnemyNum;
	float EnemyRate;
	virtual void BeginPlay() override;
private:
	class UDataTable* EnemyDataTable;
public:
	int Getenvitr();
	void Setenvitr(int itr);
	int GetMaxEnemy();
	void SetMaxEnemy(int num);
	float GetEnemyRate();
	void SetEnemyRate(float f);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
