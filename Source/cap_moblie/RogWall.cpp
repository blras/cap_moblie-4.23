// Fill out your copyright notice in the Description page of Project Settings.


#include "RogWall.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "EngineUtils.h"
#include "RogVarActor.h"
// Sets default values
ARogWall::ARogWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ObjectMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
	ObjectMeshComponent->SetupAttachment(RootComponent);
	ObjectMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ObjectMeshComponent->SetWorldScale3D(FVector(192, 192, 192));
}

// Called when the game starts or when spawned
void ARogWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARogWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ARogWall::SetWallType_Implementation(int num)
{
	Type = num;
	FVector location = GetActorLocation();
	ARogVarActor* Var;
	UWorld* const World = GetWorld();
	//Var = World->SpawnActor<ARogVarActor>(GetActorLocation(),GetActorRotation());
	for (TActorIterator<ARogVarActor>Itr(World); Itr; ++Itr)
	{
		Var = *Itr;
		WallMeshPath = Var->GetObjectMeshPath();
	}
	switch (Type)
	{
	case 0: location = FVector(location.X + 330, location.Y - 740, location.Z - 10); break;
	case 1: location = FVector(location.X - 830, location.Y + 110, location.Z - 20); break;
	case 2: location = FVector(location.X + 100, location.Y + 0, location.Z - 10); break;
	case 3: location = FVector(location.X + 780, location.Y + 240, location.Z + 0); break;
	case 4: location = FVector(location.X + 100, location.Y + 840, location.Z + 0); break;
	case 5: location = FVector(location.X - 780, location.Y + 840, location.Z - 10); break;
	}
	SetActorLocation(location);
	ObjectMeshComponent->SetStaticMesh(WallMeshPath[Type]);
}

