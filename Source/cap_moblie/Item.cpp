// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Engine/SkeletalMesh.h"
#include "RogCharacter.h"
// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ItemMesh(TEXT("/Game/Meshes/Weapons/SK_Wep_Shotgun_01"));
	ItemMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemMesh"));
	ItemMeshComponent->SetSkeletalMesh(ItemMesh.Object);
	ItemMeshComponent->SetupAttachment(RootComponent);
	ItemMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ItemMeshComponent->SetWorldScale3D(FVector(1, 1, 1));
	//ItemMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProxSphere = CreateDefaultSubobject<USphereComponent>(FName("ProxSphere"));
	ProxSphere->SetupAttachment(ItemMeshComponent);
	ProxSphere->RelativeLocation = FVector(0, 15, 0);
	ProxSphere->SetSphereRadius(20.f);
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::Prox);

	HitSphere = CreateDefaultSubobject<USphereComponent>(FName("HitSphere"));
	HitSphere->SetupAttachment(ItemMeshComponent);
	HitSphere->RelativeLocation = FVector(0, 20, 0);
	HitSphere->SetSphereRadius(12.f);
	HitSphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::HitBox);
	range = 120;
	AttackRate = 1.0f;
	IsUse = false;
	bCanDmg = true;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::Prox_Implementation(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsUse == false) {
		if (Cast<ARogCharacter>(OtherActor) == nullptr)
		{
			return;
		}
		Cast<ARogCharacter>(OtherActor)->Equip(this);
	}
}
void AItem::HitBox_Implementation(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsUse == true)
	{
		if (bCanDmg == true)
		{
			if (Cast<ARogCharacter>(OtherActor) == nullptr)
			{
				return;
			}
			else if (Cast<ARogCharacter>(OtherActor)->faction.Equals(faction))
			{
				return;
			}
			ARogCharacter* target = Cast<ARogCharacter>(OtherActor);
			//target->Hp -= 1;
			//target->HitDamege
			bCanDmg = false;
		}
	}
}
void AItem::CanDmg_Implementation()
{
	bCanDmg = true;
}
void AItem::Setting_Implementation()
{
	ItemMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}