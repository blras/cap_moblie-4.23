// Fill out your copyright notice in the Description page of Project Settings.


#include "CapWheeledVehicle.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "WheeledVehicleMovementComponent.h"


ACapWheeledVehicle::ACapWheeledVehicle()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkelMesh(TEXT("/Game/meshes/Vehicles_Rigged/SK_Veh_Train_01"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimFinder(TEXT("Class'/Game/Blueprints/anim/train_anim.train_anim_C'"));
	// Create the mesh component
	MeshComponent = GetMesh();
	MeshComponent->SetSkeletalMesh(SkelMesh.Object);
	if (AnimFinder.Object)
	{
		UClass* Anim = AnimFinder.Object;
		MeshComponent->SetAnimInstanceClass(Anim);
	}
	MeshComponent->SetWorldScale3D(FVector(0.5, 0.5, 0.5));
	//GetVehicleMovementComponent()->Wheels.;
	GetVehicleMovementComponent()->WheelSetups[0].BoneName = "SK_Veh_Train_01_Wheel_L_01";
	GetVehicleMovementComponent()->WheelSetups[1].BoneName = "SK_Veh_Train_01_Wheel_R_01";
	GetVehicleMovementComponent()->WheelSetups[2].BoneName = "SK_Veh_Train_01_Wheel_L_04";
	GetVehicleMovementComponent()->WheelSetups[3].BoneName = "SK_Veh_Train_01_Wheel_R_04";
	GetVehicleMovementComponent()->MaxEngineRPM = 5729;//170km/h
}
//void ACapWheeledVehicle::BeginPlay()
//{
	//GetVehicleMovement()->SetThrottleInput(10.0);
//}
void ACapWheeledVehicle::Tick(float DeltaTime)
{
	//UWheeledVehicleMovementComponent *mov = GetVehicleMovement();
	//mov->SetThrottleInput(10.0);
	GetVehicleMovement()->SetThrottleInput(1.f);
	
	//Move();
}
void ACapWheeledVehicle::Move_Implementation()
{
}