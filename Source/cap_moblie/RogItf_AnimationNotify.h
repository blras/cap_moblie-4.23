// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RogItf_AnimationNotify.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URogItf_AnimationNotify : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CAP_MOBLIE_API IRogItf_AnimationNotify
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Itf_Reload")  //! Blueprint상에서 사용할 수 있도록 UFunction세팅 
		//void ChannelingStart();

};
