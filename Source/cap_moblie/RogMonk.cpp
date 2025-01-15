// Fill out your copyright notice in the Description page of Project Settings.


#include "RogMonk.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/CollisionProfile.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "UserChar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RogEnemyActor.h"
#include "EngineUtils.h"
#include "Cap_AIController.h"
#include "Particles/ParticleSystem.h"
#include "RogEffect.h"
#include "Bullet.h"
#include "UserChar.h"
#include "Sound/SoundBase.h"

ARogMonk::ARogMonk()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Mesh(TEXT("/Game/meshes/Characters/SK_Character_Mystic_01"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> upperMesh(TEXT("/Game/meshes/Characters/SK_Arms_Upper_01"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> lowerMesh(TEXT("/Game/meshes/Characters/SK_Arms_Lower_01"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimFinder(TEXT("Class'/Game/polymonk/polymonkbp/Gideon_AnimBlueprint.Gideon_AnimBlueprint_C'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>bulleteffect(TEXT("/Game/Particles/Projectiles/P_Projectile_Bomb03Blue"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>hiteffect(TEXT("/Game/Particles/Muzzles/P_Muzzle_Bomb03Blue"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>chargeeffect(TEXT("/Game/Particles/Projectiles/P_Projectile_ElectricBall02Blue"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>chargehiteffect(TEXT("/Game/Particles/Muzzles/P_Muzzle_ElectricBall01Blue"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>jumpeffect(TEXT("/Game/Particles/Sci_Fi_Bullet/P_SF_Bullet_Shot"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>teleporteffect(TEXT("/Game/Particles/ParticleSystems/P_Trail_Fire"));
	static ConstructorHelpers::FObjectFinder<USoundBase>shotsound(TEXT("/Game/Sounds/Character/Player_Character_(Finish)/c1_Attack")); 
	// Create the mesh component
	MeshComponent->SetSkeletalMesh(Mesh.Object);
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	MeshComponent->SetWorldScale3D(FVector(3, 3, 3));
	MeshComponent->RelativeRotation = FRotator(0.f, -90.f, 0.f);
	MeshComponent->RelativeLocation = FVector(0, 0, -270);
	MeshComponent->SetGenerateOverlapEvents(true);

	UpperComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("UpperComponent"));
	LowerComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("LowerComponent"));
	UpperComponent->SetSkeletalMesh(upperMesh.Object);
	UpperComponent->SetupAttachment(RootComponent);
	UpperComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	UpperComponent->SetWorldScale3D(FVector(3, 3, 3));
	UpperComponent->RelativeRotation = FRotator(0.f, -90.f, 0.f);
	UpperComponent->RelativeLocation = FVector(-60, 0, 120);
	LowerComponent->SetSkeletalMesh(lowerMesh.Object);
	LowerComponent->SetupAttachment(RootComponent);
	LowerComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	LowerComponent->SetWorldScale3D(FVector(3, 3, 3));
	LowerComponent->RelativeRotation = FRotator(0.f, -90.f, 0.f);
	LowerComponent->RelativeLocation = FVector(-60, 0, 120);

	UCapsuleComponent* capsule = GetCapsuleComponent();
	capsule->SetCapsuleRadius(90);
	capsule->SetCapsuleHalfHeight(270);
	if (AnimFinder.Object)
	{
		UClass* Anim = AnimFinder.Object;
		MeshComponent->SetAnimInstanceClass(Anim);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Aanimmontage(TEXT("/Game/polymonk/Primary_Attack_A_Medium_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Banimmontage(TEXT("/Game/polymonk/Primary_Attack_B_Medium_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Canimmontage(TEXT("/Game/polymonk/Primary_Attack_C_Medium_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> deathmontage(TEXT("/Game/polymonk/Death_Fwd_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> chargemontage(TEXT("/Game/polymonk/CosmicRift_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> chargeshotmontage(TEXT("/Game/polymonk/Cosmic_Rift_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> jumpmontage(TEXT("/Game/polymonk/JumpPad_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> landingmontage(TEXT("/Game/polymonk/Jump_Idle_Land_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> teleportmontage(TEXT("/Game/polymonk/Torn_Space_intro_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> hotshotmontage(TEXT("/Game/polymonk/RMB_Cast_Montage"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> upperarm(TEXT("/Game/meshes/Characters/SK_Arms_Upper_01_Anim_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> lowerarm(TEXT("/Game/meshes/Characters/SK_Arms_Lower_01_Anim_Montage"));

	static ConstructorHelpers::FObjectFinder<USoundBase>chargeshotsound(TEXT("/Game/Sounds/Character/Boss/2_forest_Boss/e102_Cosmic_Rift"));
	static ConstructorHelpers::FObjectFinder<USoundBase>chargesound(TEXT("/Game/Sounds/Character/Boss/2_forest_Boss/e102_CosmicRift_Start"));
	static ConstructorHelpers::FObjectFinder<USoundBase>damagedsound(TEXT("/Game/Sounds/Character/Boss/2_forest_Boss/e102_Damaged"));
	static ConstructorHelpers::FObjectFinder<USoundBase>deathsound(TEXT("/Game/Sounds/Character/Boss/2_forest_Boss/e102_Death"));
	static ConstructorHelpers::FObjectFinder<USoundBase>landingsound(TEXT("/Game/Sounds/Character/Boss/2_forest_Boss/e102_Jump_in_Place_Recover"));
	static ConstructorHelpers::FObjectFinder<USoundBase>jumpsound(TEXT("/Game/Sounds/Character/Boss/2_forest_Boss/e102_Jump_in_Place_Start"));
	static ConstructorHelpers::FObjectFinder<USoundBase>startsound(TEXT("/Game/Sounds/Character/Boss/2_forest_Boss/e102_Level_Start"));
	static ConstructorHelpers::FObjectFinder<USoundBase>engagesound(TEXT("/Game/Sounds/Character/Boss/2_forest_Boss/e102_Level_Start_+_enegry_charge"));
	static ConstructorHelpers::FObjectFinder<USoundBase>Ashotsound(TEXT("/Game/Sounds/Character/Boss/2_forest_Boss/e102_Primary_Attack_A_Medium"));
	static ConstructorHelpers::FObjectFinder<USoundBase>Bshotsound(TEXT("/Game/Sounds/Character/Boss/2_forest_Boss/e102_Primary_Attack_B_Medium"));
	static ConstructorHelpers::FObjectFinder<USoundBase>Cshotsound(TEXT("/Game/Sounds/Character/Boss/2_forest_Boss/e102_Primary_Attack_C_Medium"));
	static ConstructorHelpers::FObjectFinder<USoundBase>hotshotsound(TEXT("/Game/Sounds/Character/Boss/2_forest_Boss/e102_RMB_Intro"));
	static ConstructorHelpers::FObjectFinder<USoundBase>teleportsound(TEXT("/Game/Sounds/Character/Boss/2_forest_Boss/e102_Torn_Space_intro"));



	if (Aanimmontage.Object)
		Animmontage = Aanimmontage.Object;
	if (Aanimmontage.Object)
		AAnimmontage = Aanimmontage.Object;
	if (Banimmontage.Object)
		BAnimmontage = Banimmontage.Object;
	if (Canimmontage.Object)
		CAnimmontage = Canimmontage.Object;
	if (chargemontage.Object)
		ChargeAnimmontage = chargemontage.Object;
	if (chargeshotmontage.Object)
		ChargeShotAnimmontage = chargeshotmontage.Object;
	if (jumpmontage.Object)
		JumpAnimmontage = jumpmontage.Object;
	if (landingmontage.Object)
		LandingAnimmontage = landingmontage.Object;
	if (teleportmontage.Object)
		TeleportAnimmontage = teleportmontage.Object;
	if (hotshotmontage.Object)
		HotShotAnimmontage = hotshotmontage.Object;
	if (deathmontage.Object)
		Deathmontage = deathmontage.Object;

	if (upperarm.Object)
		UpperArm = upperarm.Object;
	if (lowerarm.Object)
		LowerArm = lowerarm.Object;

	Hp = 1000;
	MaxHp = 1000;
	MoveSpeed = 800;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	faction = "Enemy";
	AIControllerClass = ACap_AIController::StaticClass();
	range = 1500;
	BreakRate = 300;

	if (shotsound.Object != nullptr)
		AttackSound = shotsound.Object;
	if (Ashotsound.Object != nullptr)
		AShotSound = Ashotsound.Object;
	if (Bshotsound.Object != nullptr)
		BShotSound = Bshotsound.Object;
	if (Cshotsound.Object != nullptr)
		CShotSound = Cshotsound.Object;
	if (chargeshotsound.Object != nullptr)
		ChargeShotSound = chargeshotsound.Object;
	if (hotshotsound.Object != nullptr)
		HotShotSound = hotshotsound.Object;
	if (startsound.Object != nullptr)
		StartSound = startsound.Object;
	if (engagesound.Object != nullptr)
		EngageSound = engagesound.Object;
	if (chargesound.Object != nullptr)
		ChargeSound = chargesound.Object;
	if (jumpsound.Object != nullptr)
		JumpStartSound = jumpsound.Object;
	if (landingsound.Object != nullptr)
		LandingSound = landingsound.Object;
	if (damagedsound.Object != nullptr)
		DamagedSound = damagedsound.Object;
	if (deathsound.Object != nullptr)
		DeathSound = deathsound.Object;
	if (teleportsound.Object != nullptr)
		TeleportSound = teleportsound.Object;

	if (bulleteffect.Object != nullptr)
		BulletEffect = bulleteffect.Object;
	if (hiteffect.Object != nullptr)
		HitEffect = hiteffect.Object;
	if (chargeeffect.Object != nullptr)
		ChargeEffect = chargeeffect.Object;
	if (chargehiteffect.Object != nullptr)
		ChargeHitEffect = chargehiteffect.Object;
	if (jumpeffect.Object != nullptr)
		JumpEffect = jumpeffect.Object;
	if (teleporteffect.Object != nullptr)
		TeleportEffect = teleporteffect.Object;
	testi = 0;
	combonum = 0;
	isboss = true;
	Name = "Monk";

	for (int i = 0; i < 2; i++)
	{
		phase.Add(MaxHp);
	}

}
void ARogMonk::BeginPlay()
{
	Super::Super::BeginPlay();
	AUserChar* player = Cast<AUserChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Level = player->Level;
	SetStat();
	int a = MaxHp / 3;
	phase[0] =MaxHp- a;
	phase[1] = phase[0] - a;
	isboss = true;

}
void ARogMonk::Tick(float DeltaSeconds)
{
	Super::Super::Tick(DeltaSeconds);
	if (Hp <= 0 && live)
	{
		//Destroy();
		Death();
		//MeshComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		MeshComponent->SetSimulatePhysics(true);
		//PlayAnimMontage(Deathmontage);
		//InputEnabled();
	}
	else if(live)
	{
		//Sight();
		if (testi > 300)
		{
			if (Hp>phase[0])
				Charge();
			else if (Hp < phase[0] && Hp>phase[1])
				Jump();
			else if (Hp < phase[1])
				Teleport();
			testi = 0;
		}
		testi++;
		if (bCanFire == true)
		{
			UpperComponent->PlayAnimation(UpperArm, true);
			LowerComponent->PlayAnimation(LowerArm, true);
			BossAI();
		}
	}
	
}
void ARogMonk::Jump()
{
	PlayAnimMontage(JumpAnimmontage, 1);
	UGameplayStatics::PlaySoundAtLocation(this, JumpStartSound, GetActorLocation());
	FVector Movement = FVector(0,0,0);
	if (Target != nullptr)
	{
		Movement = Target->GetActorLocation() - GetActorLocation();
		Movement.GetClampedToMaxSize(1);
		FVector launchdir = Movement + FVector(0, 0,900);
		LaunchCharacter(launchdir, true, true);
	}
	UWorld* const World = GetWorld();
	FVector gunoffset = FVector(0, 0, -100);
	if (World != NULL)
	{
		UWorld* const World = GetWorld();
		const FRotator FireRotation = Movement.Rotation();
		const FVector SpawnLocation = GetActorLocation();
		ARogEffect* effect;
		// spawn the projectile
		effect = World->SpawnActor<ARogEffect>(SpawnLocation + FireRotation.RotateVector(gunoffset), FireRotation);
		if (JumpEffect != nullptr)
			effect->SetParticle(JumpEffect);
	}
	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ARogCharacter::AttackTimerExpired, 1);
}
void ARogMonk::Teleport()
{
	UWorld* const World = GetWorld();
	FVector gunoffset = FVector(0, 0, -100);
	FVector Movement = FVector(0, 0, 0);
	if (World != NULL)
	{
		UWorld* const World = GetWorld();
		const FRotator FireRotation = Movement.Rotation();
		const FVector SpawnLocation = GetActorLocation();
		ARogEffect* effect;
		// spawn the projectile
		effect = World->SpawnActor<ARogEffect>(SpawnLocation + FireRotation.RotateVector(gunoffset), FireRotation);
		if (TeleportEffect != nullptr)
			effect->SetParticle(TeleportEffect);
	}
	PlayAnimMontage(TeleportAnimmontage, 1);
	UGameplayStatics::PlaySoundAtLocation(this, TeleportSound, GetActorLocation());
	if (Target != nullptr)
	{
		Movement = Target->GetActorLocation() - GetActorLocation();
		//Movement.GetClampedToMaxSize(1);
		//FVector launchdir = Movement + FVector(0, 0, 1200);
		float X = FMath::RandRange(0, 500);
		float Y = FMath::RandRange(0, 500);
		SetActorLocation(GetActorLocation()+Movement+(Movement/2));
	}
	if (World != NULL)
	{
		UWorld* const World = GetWorld();
		const FRotator FireRotation = Movement.Rotation();
		const FVector SpawnLocation = GetActorLocation();
		ARogEffect* effect;
		// spawn the projectile
		effect = World->SpawnActor<ARogEffect>(SpawnLocation + FireRotation.RotateVector(gunoffset), FireRotation);
		if (TeleportEffect != nullptr)
			effect->SetParticle(TeleportEffect);
	}
}
void ARogMonk::Charge()
{
	if (Target != nullptr)
	{
		PlayAnimMontage(ChargeAnimmontage, 1);
		UGameplayStatics::PlaySoundAtLocation(this, ChargeSound, GetActorLocation());
		UWorld* const World = GetWorld();
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ARogMonk::ChargeShot, 1.4);
		FVector Movement = FVector(0, 0, 0);
		Movement = Target->GetActorLocation() - GetActorLocation();
		FVector gunoffset = FVector(0, 0, 300);
		if (World != NULL)
		{
			UWorld* const World = GetWorld();
			const FRotator FireRotation = Movement.Rotation();
			const FVector SpawnLocation = GetActorLocation();
			ARogEffect* effect;
			// spawn the projectile
			effect = World->SpawnActor<ARogEffect>(SpawnLocation + FireRotation.RotateVector(gunoffset), FireRotation);
			if (ChargeEffect != nullptr)
				effect->SetParticle(ChargeEffect);
			if (ChargeSound != nullptr)
				UGameplayStatics::PlaySoundAtLocation(this, ChargeSound, GetActorLocation(), 0.7f);
			ChargeBullet = effect;
		}
	}
}
void ARogMonk::ChargeShot()
{
	FVector Movement = FVector(0, 0, 0);
	FVector gunoffset = FVector(0, 0, 300);
	if (Target != nullptr)
		Movement = Target->GetActorLocation()-gunoffset - GetActorLocation();
	PlayAnimMontage(ChargeShotAnimmontage, 1);
	UGameplayStatics::PlaySoundAtLocation(this, ChargeShotSound, GetActorLocation());
	if(ChargeBullet!=nullptr)
		ChargeBullet->EndEffect();
	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		UWorld* const World = GetWorld();
		const FRotator FireRotation = Movement.Rotation();
		const FVector SpawnLocation = GetActorLocation();
		ABullet* effect;
		// spawn the projectile
		effect = World->SpawnActor<ABullet>(SpawnLocation + FireRotation.RotateVector(gunoffset), FireRotation);
		effect->Shooter = this;
		if (ChargeEffect != nullptr)
			effect->SetParticle(ChargeEffect);
		if (ChargeHitEffect != nullptr)
			effect->SetHitParticle(ChargeHitEffect);
	}
	SetActorRotation(Movement.Rotation());
	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ARogCharacter::AttackTimerExpired, 0.8);
}
void ARogMonk::HotShot(FVector FireDirection)
{
	UWorld* const World = GetWorld();
	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ARogCharacter::AttackTimerExpired, 0.8);
	Animmontage = HotShotAnimmontage;
	AttackSound = HotShotSound;
	AttackRate = 0.8;
	combonum = -1;
	FVector gunoffset = FVector(30, 0, 0);
	Attack(FireDirection,gunoffset);
	//Attack(FireDirection);
}
void ARogMonk::Combo(FVector FireDirection)
{
	switch (combonum)
	{
	case 0: Animmontage = AAnimmontage; AttackRate = 0.6; AttackSound = AShotSound; break;
	case 1:	Animmontage = BAnimmontage; AttackRate = 0.6; AttackSound = BShotSound; break;
	case 2: Animmontage = CAnimmontage; AttackRate = 1.5; AttackSound = CShotSound; break;
	};
	if (bCanFire)
	{
		if (combonum < 2)
			combonum++;
		else
			combonum = 0;
	}
	FVector gunoffset = FVector(30, 0, 0);
	Attack(FireDirection,gunoffset);
	int hot = FMath::RandRange(0, 2);
	if (hot < 1&&combonum == 0&&Hp<30)
		HotShot(FireDirection);
}
void ARogMonk::BossAI_Implementation()
{
	FVector Movement;
	if (Target != nullptr)
	{
		Movement = Target->GetActorLocation() - GetActorLocation();
		if (Movement.Size() > range)
		{
			Movement.GetClampedToMaxSize(1);
			SetActorRotation(Movement.Rotation());
			AddMovementInput(Movement, MoveSpeed);
		}
		else
		{
			Combo(Movement);
		}
	}
}
void ARogMonk::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	UGameplayStatics::PlaySoundAtLocation(this, LandingSound, GetActorLocation());
}
void ARogMonk::JumpBall()
{

}
float ARogMonk::GetBreakRate()
{

	return BreakRate;
}
void ARogMonk::SetBreakeRate(float brate) 
{
	BreakRate = brate;
}