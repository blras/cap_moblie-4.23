// Fill out your copyright notice in the Description page of Project Settings.


#include "RogLevelStream.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "StageDataTable.h"
#include "Engine/CollisionProfile.h"
#include "Engine/LevelStreaming.h"
#include "UserChar.h"
#include "Engine/World.h"
#include "Engine.h"
#include "RogEnemyActor.h"
#include "Enemy.h"
// Sets default values
ARogLevelStream::ARogLevelStream()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable>StagesDataTable(TEXT("/Game/DataTables/StageDataTable"));

	if (StagesDataTable.Succeeded())
	{
		StageDataTable = StagesDataTable.Object;
	}
	if (StageDataTable != nullptr)
	{
		FName name;
		for (int i = 1; i < 22; i++)
		{
			FStageTableRow* StageTableRow = StageDataTable->FindRow<FStageTableRow>(FName(*FString::FormatAsNumber(i)), FString(""));
			name = (*StageTableRow).name;
			if (!name.IsNone())
			{
				LevelArray.Add(name);
				levelname = name;
			}
		}
	}
	

	Box.BoxVolume = CreateDefaultSubobject<UBoxComponent>(FName("BoxVolume"));
	Box.BoxVolume->SetBoxExtent(FVector(2400, 2400, 1000));
	Box.outYaw = 0;
	PreBox.BoxVolume = CreateDefaultSubobject<UBoxComponent>(FName("PreBox"));
	PreBox.BoxVolume->SetBoxExtent(FVector(2400, 2400, 1000));
	PreBox.outYaw = 0;
	mPreBox.BoxVolume = CreateDefaultSubobject<UBoxComponent>(FName("mPreBox"));
	mPreBox.BoxVolume->SetBoxExtent(FVector(2400, 2400, 1000));
	mPreBox.outYaw = 0;
	NextBox.BoxVolume = CreateDefaultSubobject<UBoxComponent>(FName("NextBox"));
	NextBox.BoxVolume->SetBoxExtent(FVector(2400, 2400, 1000));
	NextBox.outYaw = 0;
	mNextBox.BoxVolume = CreateDefaultSubobject<UBoxComponent>(FName("mNextBox"));
	mNextBox.BoxVolume->SetBoxExtent(FVector(2400, 2400, 1000));
	mNextBox.outYaw = 0;

	NextBox.BoxVolume->OnComponentBeginOverlap.AddDynamic(this, &ARogLevelStream::Prox);
	//PreBox.BoxVolume->OnComponentBeginOverlap.AddDynamic(this, &ARogLevelStream::PreBoxProx);

	int len = 5590;
	Box.PreBox = &PreBox;
	Box.NextBox = &NextBox;
	PreBox.NextBox = &Box;
	PreBox.PreBox = &mPreBox;
	mPreBox.NextBox = &PreBox;
	NextBox.PreBox = &Box;
	NextBox.NextBox = &mNextBox;
	mNextBox.PreBox = &NextBox;

	FTransform trans = FTransform(FRotator(0, 0, 0), FVector(0, -len, 0), FVector(1, 1, 1));
	PreBox.BoxVolume->SetWorldTransform(trans);
	mPreBox.BoxVolume->SetWorldTransform(trans);
	trans = FTransform(FRotator(0, 0, 0), FVector(0, 0, 0), FVector(1, 1, 1));
	Box.BoxVolume -> SetWorldTransform(trans);
	trans = FTransform(FRotator(0, 0, 0), FVector(0, len, 0), FVector(1, 1, 1));
	NextBox.BoxVolume->SetWorldTransform(trans);
	mNextBox.BoxVolume->SetWorldTransform(trans);


	levelcount = 0;
	backcount = 0;
	FString levelstring = FString::FromInt(levelcount);
	levelname = TEXT("desert-4");
	spawnname = TEXT("1x0");
	spawnname = TEXT("1x") + levelstring;
}

// Called when the game starts or when spawned
void ARogLevelStream::BeginPlay()
{
	Super::BeginPlay();
	//Testap();
	//int num = FMath::RandRange(2, 7);
	InitiateLevelStream();
	//LevelStream(num, mNextBox);
	//num = FMath::RandRange(2, 7);
	//LevelStream(num, mNextBox);
	BoxVol0 = false;
}

// Called every frame
void ARogLevelStream::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARogLevelStream::Testap_Implementation()
{
	int levelnum = FMath::RandRange(2, 7);
	SpawnLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), LevelArray[levelnum]);
	ULevelStreaming* level = SpawnLevel->CreateInstance(spawnname);
	FTransform trans = FTransform(FRotator(0, 0, 0), FVector(0, 5590, -54000), FVector(1, 1, 1));

	level->LevelTransform = trans;
	level->SetShouldBeLoaded(true);
	level->SetShouldBeVisible(true);

	
	/*SpawnLevel->LevelTransform = trans;
	SpawnLevel->CreateInstance(spawnname);
	SpawnLevel->LevelTransform=trans;
	SpawnLevel->SetShouldBeLoaded(true);
	SpawnLevel->SetShouldBeVisible(true);*/
	//level->load
	//SpawnLevel->initiallyLoaded();
}
void ARogLevelStream::LevelStream_Implementation(int32 leveli, FBoxVolume StreamBox)
{
	SpawnLevel = UGameplayStatics::GetStreamingLevel(GetWorld(),LevelArray[leveli]);
	//SpawnLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), TEXT("desert-9"));
	//level.name
	int len = 5590;
	int height = 18000;
	int zlen = leveli;
	if (leveli > 9)
		zlen = -(leveli - 9);
	float xlen = 0;
	float ylen = 0;
	float tyaw = 0;
	bool isnext = false;
	levelcount++;
	FString levelstring = FString::FromInt(levelcount);
	spawnname = TEXT("1x") + levelstring;
	ULevelStreaming* level = SpawnLevel->CreateInstance(spawnname);
	FTransform trans = FTransform(FRotator(0, 0, 0), FVector(0, 0, 0), FVector(1, 1, 1));
	if (StreamBox.NextBox == nullptr)
	{
		isnext = true;
		trans = StreamBox.BoxVolume->GetComponentTransform();
		if(mPreBox.level!=nullptr)
		{
			mPreBox.level->SetShouldBeLoaded(false);
			mPreBox.level->SetShouldBeVisible(false);
		}
		if (PreBox.level != nullptr)
		{
			mPreBox.level = PreBox.level;
			mPreBox.BoxVolume->SetWorldTransform(PreBox.BoxVolume->GetComponentTransform());
			mPreBox.outYaw = PreBox.outYaw;
			FTransform ptrans = mPreBox.level->LevelTransform;
			ptrans = FTransform(FRotator(0, ptrans.Rotator().Yaw+180, 0), FVector(ptrans.GetTranslation().X, ptrans.GetTranslation().Y, ptrans.GetTranslation().Z), FVector(1, 1, 1));
			BackgroundLevelStream(ptrans, false);
		}
		if (Box.level != nullptr)
		{
			PreBox.level = Box.level;
			PreBox.BoxVolume->SetWorldTransform(Box.BoxVolume->GetComponentTransform());
			PreBox.outYaw = Box.outYaw;
		}
		if (NextBox.level != nullptr)
		{
			Box.level = NextBox.level;
			Box.BoxVolume->SetWorldTransform(NextBox.BoxVolume->GetComponentTransform());
			Box.outYaw = NextBox.outYaw;
		}
		if (mNextBox.level != nullptr)
		{
			NextBox.level = mNextBox.level;
			NextBox.BoxVolume->SetWorldTransform(mNextBox.BoxVolume->GetComponentTransform());
			NextBox.outYaw = mNextBox.outYaw;
		}
		tyaw = NextBox.outYaw;
		switch (NextBox.outYaw)
		{
		case 0: ylen =ylen + len; break;
		case 90: xlen = xlen - len; break;
		case 180: ylen = ylen - len; break;
		case 270: xlen = xlen + len; break;
		}
		mNextBox.level = level;
		trans = FTransform(FRotator(0, tyaw, 0), FVector(trans.GetTranslation().X+xlen, trans.GetTranslation().Y + ylen, 0), FVector(1, 1, 1));
		mNextBox.BoxVolume->SetWorldTransform(trans);
		if (leveli == 7)
			mNextBox.outYaw = mNextBox.outYaw - 90 < 0 ? mNextBox.outYaw + 270 : mNextBox.outYaw - 90;
		else if (leveli == 6)
			mNextBox.outYaw = mNextBox.outYaw + 90 >= 360 ? mNextBox.outYaw - 270 : mNextBox.outYaw + 90;
	}
	if (StreamBox.PreBox == nullptr)
	{
		isnext = false;
		trans = StreamBox.BoxVolume->GetComponentTransform();
		if (mNextBox.level != nullptr)
		{
			mNextBox.level->SetShouldBeLoaded(false);
			mNextBox.level->SetShouldBeVisible(false);
		}
		if (NextBox.level != nullptr)
		{
			mNextBox.level = NextBox.level;
			mNextBox.BoxVolume->SetWorldTransform(NextBox.BoxVolume->GetComponentTransform());
			mNextBox.outYaw = NextBox.outYaw;
			FTransform ntrans = mNextBox.level->LevelTransform;
			BackgroundLevelStream(ntrans, true);
		}
		if (Box.level != nullptr)
		{
			NextBox.level = Box.level;
			NextBox.BoxVolume->SetWorldTransform(Box.BoxVolume->GetComponentTransform());
			NextBox.outYaw = Box.outYaw;
		}
		if (PreBox.level != nullptr)
		{
			Box.level = PreBox.level;
			Box.BoxVolume->SetWorldTransform(PreBox.BoxVolume->GetComponentTransform());
			Box.outYaw = PreBox.outYaw;
		}
		if (mPreBox.level != nullptr)
		{
			PreBox.level = mPreBox.level;
			PreBox.BoxVolume->SetWorldTransform(mPreBox.BoxVolume->GetComponentTransform());
			PreBox.outYaw = mPreBox.outYaw;
		}
		tyaw = PreBox.outYaw;
		//if(leveli==6)
			//trans = FTransform(FRotator(0, 90, 0), FVector(0, 0, 0), FVector(1, 1, 1));
		switch (PreBox.outYaw)
		{
		case 0: ylen = ylen - len; break;
		case 90: xlen = xlen - len; break;
		case 180: ylen = ylen + len; break;
		case 270: xlen = xlen + len; break;
		}
		PreBox.level = level;		
		if (tyaw == 180)
			tyaw = 0;
		else if (tyaw == 0)
			tyaw = 180;
		trans = FTransform(FRotator(0, tyaw, 0), FVector(trans.GetTranslation().X + xlen, trans.GetTranslation().Y + ylen, 0), FVector(1, 1, 1));
		mPreBox.BoxVolume->SetWorldTransform(trans);
		if (leveli == 6)
			mPreBox.outYaw = mPreBox.outYaw - 90 < 0 ? mPreBox.outYaw + 270 : mPreBox.outYaw - 90;
		else if (leveli == 7)
			mPreBox.outYaw = mPreBox.outYaw + 90 >= 360 ? mPreBox.outYaw - 270 : mPreBox.outYaw + 90;
	}
	//trans = FTransform(FRotator(0, 90 * levelcount - 90, 0), FVector(trans.GetLocation().X, len * levelcount, -(height * leveli)), FVector(1, 1, 1));
	//UWorld* const World = GetWorld();
	//FVector spawnLo = FVector(trans.GetTranslation().X, trans.GetTranslation().Y, 280);
	//AEnemy* enemy;
	//enemy = World->SpawnActor<AEnemy>(spawnLo, FRotator(0, trans.Rotator().Yaw, 0));
	BackgroundLevelStream(trans, isnext);
	trans = FTransform(FRotator(0, trans.Rotator().Yaw, 0), FVector(trans.GetTranslation().X, trans.GetTranslation().Y, -(height * zlen)), FVector(1, 1, 1));
	level->LevelTransform = trans;
	level->SetShouldBeLoaded(true);
	level->SetShouldBeVisible(true);
	ARogEnemyActor* Var;
	UWorld* const World = GetWorld();
	for (TActorIterator<ARogEnemyActor>Itr(World); Itr; ++Itr)
	{
		Var = *Itr;
		//int envitr = Var->Getenvitr();
		int envitr = levelcount / 4;
		if(envitr<7)
			Var->Setenvitr(envitr);
		float rate = Var->GetEnemyRate();
		Var->SetEnemyRate(rate+1);
	}
	BoxVol0 = true;
}
void ARogLevelStream::InitiateLevelStream_Implementation()
{
	SpawnLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), LevelArray[0]);
	int len = 5590;
	int height = 18000;
	float xlen = 0;
	float ylen = 0;
	float tyaw = 0;
	levelcount++;
	FString levelstring = FString::FromInt(levelcount);
	spawnname = TEXT("1x") + levelstring;
	ULevelStreaming* level = SpawnLevel->CreateInstance(spawnname);
	FTransform trans = FTransform(FRotator(0, 0, 0), FVector(0, 0, 0), FVector(1, 1, 1));
	Box.level = level;
	level->LevelTransform = trans;
	level->SetShouldBeLoaded(true);
	level->SetShouldBeVisible(true);

	int num = FMath::RandRange(2, 7);

	SpawnLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), LevelArray[num]);
	levelcount++;
	levelstring = FString::FromInt(levelcount);
	spawnname = TEXT("1x") + levelstring;
	level = SpawnLevel->CreateInstance(spawnname);
	NextBox.level = level;
	trans = FTransform(FRotator(0, tyaw, 0), FVector(trans.GetTranslation().X, trans.GetTranslation().Y + len, 0), FVector(1, 1, 1));
	NextBox.BoxVolume->SetWorldTransform(trans);
	if (num == 7)
		NextBox.outYaw = NextBox.outYaw - 90 < 0 ? NextBox.outYaw + 270 : NextBox.outYaw - 90;
	else if (num == 6)
		NextBox.outYaw = NextBox.outYaw + 90 >= 360 ? NextBox.outYaw - 270 : NextBox.outYaw + 90;
	trans = FTransform(FRotator(0, trans.Rotator().Yaw, 0), FVector(trans.GetTranslation().X, trans.GetTranslation().Y, -(height * num)), FVector(1, 1, 1));
	level->LevelTransform = trans;
	level->SetShouldBeLoaded(true);
	level->SetShouldBeVisible(true);

	num = FMath::RandRange(2, 7);

	SpawnLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), LevelArray[num]);
	levelcount++;
	levelstring = FString::FromInt(levelcount);
	spawnname = TEXT("1x") + levelstring;
	level = SpawnLevel->CreateInstance(spawnname);
	mNextBox.level = level;
	tyaw = NextBox.outYaw;
	mNextBox.outYaw = tyaw;
	switch (NextBox.outYaw)
	{
	case 0: ylen = ylen + len; break;
	case 90: xlen = xlen - len; break;
	case 180: ylen = ylen - len; break;
	case 270: xlen = xlen + len; break;
	}
	trans = FTransform(FRotator(0, tyaw, 0), FVector(trans.GetTranslation().X+xlen, trans.GetTranslation().Y+ylen, 0), FVector(1, 1, 1));
	mNextBox.BoxVolume->SetWorldTransform(trans);
	if (num == 7)
		mNextBox.outYaw = mNextBox.outYaw - 90 < 0 ? mNextBox.outYaw + 270 : mNextBox.outYaw - 90;
	else if (num == 6)
		mNextBox.outYaw = mNextBox.outYaw + 90 >= 360 ? mNextBox.outYaw - 270 : mNextBox.outYaw + 90;
	trans = FTransform(FRotator(0, trans.Rotator().Yaw, 0), FVector(trans.GetTranslation().X, trans.GetTranslation().Y, -(height * num)), FVector(1, 1, 1));
	level->LevelTransform = trans;
	level->SetShouldBeLoaded(true);
	level->SetShouldBeVisible(true);

	num = FMath::RandRange(2, 7);

	/*SpawnLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), LevelArray[num]);
	levelcount++;
	levelstring = FString::FromInt(levelcount);
	spawnname = TEXT("1x") + levelstring;
	level = SpawnLevel->CreateInstance(spawnname);
	mNextBox.level = level;
	trans = FTransform(FRotator(0, tyaw + 90, 0), FVector(trans.GetTranslation().X - len *2, trans.GetTranslation().Y, 0), FVector(1, 1, 1));
	mNextBox.BoxVolume->SetWorldTransform(trans);
	mNextBox.outYaw = 90;
	trans = FTransform(FRotator(0, trans.Rotator().Yaw, 0), FVector(trans.GetTranslation().X, trans.GetTranslation().Y, -(height * num)), FVector(1, 1, 1));
	level->LevelTransform = trans;
	level->SetShouldBeLoaded(true);
	level->SetShouldBeVisible(true);*/

}
void ARogLevelStream::BackgroundLevelStream_Implementation(FTransform trans, bool isnext)
{
	int num = 8;
	if (levelcount > 10)
		num = 15;
	SpawnLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), LevelArray[num]);
	int len = 5590;
	int height = 18000;
	int zlen = num;
	if (num > 9)
		zlen = -(num - 9);
	backcount++;
	FString levelstring = FString::FromInt(backcount);
	spawnname = TEXT("backx") + levelstring;
	ULevelStreaming* level = SpawnLevel->CreateInstance(spawnname);
	trans = FTransform(FRotator(0, trans.Rotator().Yaw, 0), FVector(trans.GetTranslation().X, trans.GetTranslation().Y, -(height * zlen)), FVector(1, 1, 1));
	level->LevelTransform = trans;
	level->SetShouldBeLoaded(true);
	level->SetShouldBeVisible(true);
	if (isnext && NextBG != nullptr)
	{
		NextBG->SetShouldBeLoaded(false);
		NextBG->SetShouldBeVisible(false);
	}
	else if (!isnext && PreBG != nullptr)
	{
		PreBG->SetShouldBeLoaded(false);
		PreBG->SetShouldBeVisible(false);
	}
	if (isnext)
		NextBG = level;
	else
		PreBG = level;
}
void ARogLevelStream::LevelStreamOff_Implementation(int32 leveli)
{

}
void ARogLevelStream::Prox_Implementation(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AUserChar>(OtherActor) == nullptr)
	{
		return;
	}
	if (BoxVol0 == false)
	{
		if (PreBox.level != nullptr)
		{
			PreBox.level->SetShouldBeLoaded(false);
			PreBox.level->SetShouldBeVisible(false);
		}
		int num = 0;
		//if (levelcount < 10)
		num = FMath::RandRange(2, 7);
		if (levelcount == 10)
		{
			num = 9;
		}
		else if (levelcount > 10&& levelcount < 20)
			num = FMath::RandRange(10, 14);
		else if (levelcount == 20)
			num = 17;
		else if (levelcount > 20)
			num = FMath::RandRange(10, 14);
		if (num == 11)
		{
			AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			int lc = player->GetLevelCount();
			player->SetLevelCount(lc + 1);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("!"));
		}
		LevelStream(num, mNextBox);
		//BoxVolume0->SetWorldTransform(trans);
		return;
	}
	BoxVol0 = false;
}
void ARogLevelStream::PreBoxProx_Implementation(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AUserChar>(OtherActor) == nullptr)
	{
		return;
	}
	if (BoxVol0 == false)
	{
		if (NextBox.level != nullptr)
		{
			NextBox.level -> SetShouldBeLoaded(false);
			NextBox.level -> SetShouldBeVisible(false);
		}
		int num = FMath::RandRange(2, 7);
		if (levelcount == 10)
		{
			num = 9;
		}
		else if (levelcount > 10 && levelcount < 20)
			num = FMath::RandRange(10, 14);
		else if (levelcount == 20)
			num = 17;
		if (num == 11)
		{
			AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			int lc = player->GetLevelCount();
			player->SetLevelCount(lc + 1);
		}
		LevelStream(num, mPreBox);
		return;
		//BoxVolume0->SetWorldTransform(trans);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ProxPrebox"));
	}
	BoxVol0 = false;
}