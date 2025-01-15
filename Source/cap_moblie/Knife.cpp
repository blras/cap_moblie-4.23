// Fill out your copyright notice in the Description page of Project Settings.


#include "Knife.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Item.h"

AKnife::AKnife()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ItemMesh(TEXT("/Game/Meshes/Weapons/SK_Wep_American_Bayonet_01"));
	ItemMeshComponent->SetSkeletalMesh(ItemMesh.Object);
	AttackRate = 0.7;
	ProxSphere->RelativeLocation = FVector(0, -1, 0);
	HitSphere->RelativeLocation = FVector(0, -1.25, 0);
	HitSphere->SetSphereRadius(1.f);
	range = 100;
}