// Fill out your copyright notice in the Description page of Project Settings.


#include "RogStage.h"
#include "RogObject.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "TimerManager.h"
#include "EngineUtils.h"
#include "RogVarActor.h"
#include "RogEnemyActor.h"
#include "Enemy.h"
// Sets default values
ARogStage::ARogStage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>(FName("SphereComp"));
	SphereComp->SetupAttachment(RootComponent);


	MAXEnemy = 40;
}

// Called when the game starts or when spawned
void ARogStage::BeginPlay()
{
	//Super::BeginPlay();
	const FVector SpawnLocation = GetActorLocation();
	const FVector Dir = FVector(90.0f, 0.0f, 0.0f);
	const FRotator SpawnRotation = Dir.Rotation();
	UWorld* const World = GetWorld();
	int objectnum = FMath::RandRange(0, 5);
	spawn = true;
	SpawnEnemy();
}
// Called every frame
void ARogStage::Tick(float DeltaSeconds)
{

}
void ARogStage::SpawnObject_Implementation()
{
	FVector location = GetActorLocation();
	int envitr = 0;
	UWorld* const World = GetWorld();

}
void ARogStage::SpawnEnemy_Implementation()
{
	//int count = CharacterinStage.Num();
	float spawnChance = FMath::RandRange(0, 1);
	ARogEnemyActor* Var;
	int envitr = 0;
	UWorld* const World = GetWorld();
	float enemyRate = 0;
	for (TActorIterator<ARogEnemyActor>Itr(World); Itr; ++Itr)
	{
		Var = *Itr;
		envitr = Var->Getenvitr();
		enemyRate = Var->GetEnemyRate();
	}
	if (spawnChance < enemyRate)
	{
		UWorld* const world = GetWorld();
		//float length = Length;
		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.Z = SpawnLocation.Z + 280;
		const FVector Dir = FVector(FMath::RandRange(0, 360), 0.0f, 0.0f);
		const FRotator SpawnRotation = Dir.Rotation();
		AEnemy* enemy;
		enemy = world->SpawnActor<AEnemy>(SpawnLocation, SpawnRotation);
	}
	/*for (int i = 0; i < CharacterinStage.Num(); i++)
	{
		if (CharacterinStage[i] == nullptr)
		{
			CharacterinStage.RemoveAt(i);
		}
	}*/
}

