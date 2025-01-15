// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotGun.h"
AShotGun::AShotGun()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>ItemMesh(TEXT("/Game/Meshes/Weapons/SK_Wep_Shotgun_01"));
	ItemMeshComponent->SetSkeletalMesh(ItemMesh.Object);
	ItemMeshComponent->SetWorldScale3D(FVector(1, 1, 1));
	ItemMeshComponent->SetRelativeRotation(FRotator(0, 0, 0));
	AttackRate = 1;
	GunOffset = FVector(70, 0, 0);
	range = 1024;
}

