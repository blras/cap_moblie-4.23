// Fill out your copyright notice in the Description page of Project Settings.


#include "RogItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "UserChar.h"
#include "Engine.h"
// Sets default values
ARogItem::ARogItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ItemMesh(TEXT("/Game/Meshes/items/SM_Item_Chr_Bag_Large_01"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetStaticMesh(ItemMesh.Object);
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	MeshComponent->SetWorldScale3D(FVector(1, 1, 1));

	ProxSphere = CreateDefaultSubobject<USphereComponent>(FName("ProxSphere"));
	ProxSphere->SetupAttachment(MeshComponent);
	ProxSphere->RelativeLocation = FVector(0, 0, 0);
	ProxSphere->SetSphereRadius(20.f);
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ARogItem::Prox);
}

// Called when the game starts or when spawned
void ARogItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARogItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ARogItem::Prox_Implementation(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AUserChar>(OtherActor) == nullptr)
	{
		return;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("itemProx"));
		AUserChar* user = Cast<AUserChar>(OtherActor);
		user->LevelUp();
		Destroy();
	}
}
