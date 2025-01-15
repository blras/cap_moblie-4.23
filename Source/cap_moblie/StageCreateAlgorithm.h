// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class CAP_MOBLIE_API StageCreateAlgorithm
{
public:
	StageCreateAlgorithm();
	~StageCreateAlgorithm();
	struct tile
	{
		struct tile* up;
		struct tile* down;
		struct tile* right;
		struct tile* left;
	};
};
