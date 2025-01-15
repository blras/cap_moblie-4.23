// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Item.h"
AGun::AGun()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ItemMesh(TEXT("/Game/Meshes/Weapons/SK_Wep_Rifle_01"));
	ItemMeshComponent->SetSkeletalMesh(ItemMesh.Object);
	ItemMeshComponent->SetWorldScale3D(FVector(1, 1, 1));
	ItemMeshComponent->SetRelativeRotation(FRotator(0,0,0));

	ProxSphere->RelativeLocation = FVector(0, 20, 0);
	ProxSphere->SetSphereRadius(20);
	HitSphere->RelativeLocation = FVector(0, 0, 0);
	HitSphere->SetSphereRadius(0);

	AttackRate = 1;
	GunOffset = FVector(70, 0, 0);
	range = 1024;
}
