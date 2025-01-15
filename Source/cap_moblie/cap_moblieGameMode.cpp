// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "cap_moblieGameMode.h"
#include "cap_mobliePawn.h"
#include "UserChar.h"

Acap_moblieGameMode::Acap_moblieGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = Acap_mobliePawn::StaticClass();
	//DefaultPawnClass = AUserChar::StaticClass();
}

