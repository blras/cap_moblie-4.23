// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
/**
 * 
 */
class CAP_MOBLIE_API RogVar
{
public:
	RogVar();
	~RogVar();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array Stuff")
	TArray<UStaticMesh*>ObjectMeshType;
};
