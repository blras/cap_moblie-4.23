// Fill out your copyright notice in the Description page of Project Settings.


#include "RogObject.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "EngineUtils.h"
#include "RogVarActor.h"
// Sets default values
ARogObject::ARogObject()
{
 	// Set this actor to call Tick() every frame.You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ObjectMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
	ObjectMeshComponent->SetupAttachment(RootComponent);
	ObjectMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ObjectMeshComponent->SetWorldScale3D(FVector(1, 1, 1));
}
// Called when the game starts or when spawned
void ARogObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARogObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARogObject::SetObjectType_Implementation(int num)
{
	Type = num;
	FVector location = GetActorLocation();
	ARogVarActor *Var;
	UWorld* const World = GetWorld();
	FRotator rotation = FRotator(0, 0, 0);
	//Var = World->SpawnActor<ARogVarActor>(GetActorLocation(),GetActorRotation());
	for (TActorIterator<ARogVarActor>Itr(World); Itr; ++Itr)
	{
		Var = *Itr;
		ObjectMeshPath = Var->Stages[1].EnvMesh;
		location = location + Var->Stages[1].EnvLocation[Type];
		rotation = Var->Stages[1].EnvRotator[Type];
	}
	ObjectMeshComponent->SetStaticMesh(ObjectMeshPath[Type]);
	SetActorLocation(location);
	SetActorRotation(rotation);
}

