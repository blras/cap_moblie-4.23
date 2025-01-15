// Fill out your copyright notice in the Description page of Project Settings.


#include "RogVar.h"
//#include <RogObject.cpp>
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
RogVar::RogVar()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> deco4Mesh(TEXT("/Game/Tile/desert/desert_2_deco_4"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> deco1Mesh(TEXT("/Game/Tile/desert/desert_2_deco_1_changed"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> deco2Mesh(TEXT("/Game/Tile/desert/desert_2_deco_2_changed"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> deco3Mesh(TEXT("/Game/Tile/desert/desert_2_deco_3_changed"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> wall1Mesh(TEXT("/Game/Tile/desert/desert_2_wall_1_changed"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> wall2Mesh(TEXT("/Game/Tile/desert/desert_2_wall_2_changed"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> wall3Mesh(TEXT("/Game/Tile/desert/desert_2_wall_3_changed"));
	ObjectMeshType.Add(deco1Mesh.Object);
	ObjectMeshType.Add(deco2Mesh.Object);
	ObjectMeshType.Add(deco3Mesh.Object);
	ObjectMeshType.Add(deco4Mesh.Object);
	ObjectMeshType.Add(wall1Mesh.Object);
	ObjectMeshType.Add(wall2Mesh.Object);
	ObjectMeshType.Add(wall3Mesh.Object);
}

RogVar::~RogVar()
{
}

