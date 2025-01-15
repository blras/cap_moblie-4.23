// Fill out your copyright notice in the Description page of Project Settings.


#include "RogVarActor.h"
#include "ObjectsDatatable.h"
#include "StageDataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "EngineUtils.h"
// Sets default values
ARogVarActor::ARogVarActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UDataTable>ObjectsDataTable(TEXT("/Game/DataTables/ObjectDataTable"));
	//static ConstructorHelpers::FObjectFinder<UDataTable>StagesDataTable(TEXT("/Game/DataTables/StageDataTable"));

	if (ObjectsDataTable.Succeeded())
	{
		ObjectDataTable = ObjectsDataTable.Object;
	}

	if (ObjectDataTable != nullptr)
	{
		UStaticMesh* Env;
		UStaticMesh* Obj;
		for (int i = 0; i < 142; i++)
		{
			FObjectsTableRow* ObjectTableRow = ObjectDataTable->FindRow<FObjectsTableRow>(FName(*FString::FormatAsNumber(i)), FString(""));
			Env = (*ObjectTableRow).EnviromentPath.Get();
			Obj = (*ObjectTableRow).ObjectsPath.Get();
			if (Env != nullptr)
			{
				EnvMeshPath.Add(Env);
			}
			if (Obj != nullptr)
			{
				ObjectMeshPath.Add(Obj);
			}
		}
	}
	for (int i = 0; i < 20; i++)
	{
		FStageData stage;
		stage.StageNum = i;
		Stages.Add(stage);
	}
	//SetStageSetting(1);
	//Stages[0].EnvMesh.Add(EnvMeshPath[0]);
}

// Called when the game starts or when spawned
void ARogVarActor::BeginPlay()
{
	Super::BeginPlay();
	//SetStageSetting(1);
}

// Called every frame
void ARogVarActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ARogVarActor::GetVarMesh_Implementation(int num)
{
//
}
void ARogVarActor::SetStageSetting(int num)
{
	int StageNum = num;
}
void ARogVarActor::SettingObjects(FString &info, int num)
{
	if (ObjectDataTable != nullptr)
	{
			FObjectsTableRow* ObjectsTableRow = ObjectDataTable->FindRow<FObjectsTableRow>(FName(*FString::FormatAsNumber(1)), FString(""));

			//FVector obl = FVector(x, y, z);
			//Stages[snum].EnvLocation.Add(obl);
	}
}
void ARogVarActor::SettingEnvs(FString& info, int num)
{
	int snum = num;
	TArray<FString> Info;
	FString MyString = info;
	MyString.ParseIntoArray(Info, TEXT(","), true);
	for (int i = 0; i < Info.Num(); i++)
	{
		int obt = FCString::Atoi(*Info[i]);
		Stages[snum].EnvMesh.Add(EnvMeshPath[obt]);
	}
}
void ARogVarActor::SetObjectLocation(int num)
{
	int snum = num;
	TArray<FString> XInfo;
	TArray<FString> YInfo;
	TArray<FString> ZInfo;
}
void ARogVarActor::SetEnvLocation(int num)
{
	int stagenum = num;
	TArray<FString> XInfo;
	TArray<FString> YInfo;
	TArray<FString> ZInfo;
	/*if (StageDataTable != nullptr)
	{
		FStageTableRow* StageTableRow = StageDataTable->FindRow<FStageTableRow>(FName(*FString::FormatAsNumber(stagenum)), FString(""));
		FString XString = (*StageTableRow).X;
		FString YString = (*StageTableRow).Y;
		FString ZString = (*StageTableRow).Z;
		XString.ParseIntoArray(XInfo, TEXT(","), true);
		YString.ParseIntoArray(YInfo, TEXT(","), true);
		ZString.ParseIntoArray(ZInfo, TEXT(","), true);
		for (int i = 0; i < XInfo.Num(); i++)
		{
			int x = 0, y = 0, z = 0;
			x = FCString::Atoi(*XInfo[i]);
			y = FCString::Atoi(*YInfo[i]);
			z = FCString::Atoi(*ZInfo[i]);
			FVector obl = FVector(x, y, z);
			Stages[stagenum].EnvLocation.Add(obl);
		}
	}*/
}
void ARogVarActor::SetObjectRotator(int num)
{
	int snum = num;
	TArray<FString> PitchInfo;
	TArray<FString> YawInfo;
	TArray<FString> RollInfo;
}
void ARogVarActor::SetEnvRotator(int num)
{
	int snum = num;
	TArray<FString> PitchInfo;
	TArray<FString> YawInfo;
	TArray<FString> RollInfo;
	/*if (StageDataTable != nullptr)
	{
		FStageTableRow* StageTableRow = StageDataTable->FindRow<FStageTableRow>(FName(*FString::FormatAsNumber(snum)), FString(""));
		FString PitchString = (*StageTableRow).Pitch;
		FString YawString = (*StageTableRow).Yaw;
		FString RollString = (*StageTableRow).Roll;
		PitchString.ParseIntoArray(PitchInfo, TEXT(","), true);
		YawString.ParseIntoArray(YawInfo, TEXT(","), true);
		RollString.ParseIntoArray(RollInfo, TEXT(","), true);
		for (int i = 0; i < PitchInfo.Num(); i++)
		{
			int p = 0, y = 0, r = 0;
			p = FCString::Atoi(*PitchInfo[i]);
			y = FCString::Atoi(*YawInfo[i]);
			r = FCString::Atoi(*RollInfo[i]);
			FRotator obr = FRotator(p, y, r);
			Stages[snum].EnvRotator.Add(obr);
		}
	}*/
}