// Fill out your copyright notice in the Description page of Project Settings.


#include "RogCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/WidgetComponent.h"
#include "Sound/SoundBase.h"
#include "Item.h"
#include "Gun.h"
#include "Knife.h"
#include "Bullet.h"
#include "RogHpbar.h"
#include "RogTextActor.h"
#include "RogItem.h"
#include "Particles/ParticleSystem.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ARogCharacter::ARogCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = GetMesh();
	UCapsuleComponent* capsule = GetCapsuleComponent();
	capsule->SetCapsuleRadius(35);
	capsule->SetCapsuleHalfHeight(90);

	static ConstructorHelpers::FClassFinder<UUserWidget>Hpbar(TEXT("/Game/Blueprints/widgetbp/bp_RogHpbar"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem>resurrecteffect(TEXT("/Game/Particles/ParticleSystems/P_Beam_Lightning_Hit"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> healmontage(TEXT("/Game/polyStaff/skill16_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> resurrectmontage(TEXT("/Game/polyStaff/skill12_Montage"));

	static ConstructorHelpers::FObjectFinder<USoundBase>resurrectsound(TEXT("/Game/Sounds/Character/Boss/2_forest_Boss/e102_Torn_Space_intro"));

	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("WeaponComponent"));
	AimComponent = CreateDefaultSubobject<UArrowComponent>(FName("AimComponent"));
	HpWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("RogHpbar"));
	HpWidgetComp -> AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	HpWidgetComp -> RelativeLocation = FVector(0, 0, 90);
	
	if (Hpbar.Succeeded())
		HpWidgetComp->SetWidgetClass(Hpbar.Class);

	if (healmontage.Object)
		HealAnimmontage = healmontage.Object;
	if (resurrectmontage.Object)
		ResurrectAnimmontage = resurrectmontage.Object;
	if (resurrecteffect.Object)
		ResurrectEffect = resurrecteffect.Object;
	if (resurrectsound.Object)
		ResurrectSound = resurrectsound.Object;
	HpWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	HpWidgetComp->SetDrawAtDesiredSize(true);
	HpWidgetComp->SetVisibility(false);


	Hp = 5;
	MoveSpeed = 400;
	AttackRate = 1;
	bCanFire = true;
	bCanDmg = true;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	range = 200;
	live = true;
	Uidmg = -1;
	Dmg = 5;
	Exp = 0;
	CooldownRate = 1;
	isSkillCast = false;
	Crit = 5;
	CritDmg = 2;
	Armor = 0;
	Level = 1;
	levelcount = 0;
	bCanResurrect = false;
}

// Called when the game starts or when spawned
void ARogCharacter::BeginPlay()
{
	Super::BeginPlay();
	HpbarRef = Cast<URogHpbar>(HpWidgetComp->GetUserWidgetObject());
	HpbarRef->SetHp(Hp);
	HpbarRef->SetMaxHp(Hp);
}

// Called every frame
void ARogCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetActorLocation().Z < -4000)
		Death();
	HpbarRef->SetHp(Hp);
}
float ARogCharacter::GetHp()
{
	return Hp;
}
float ARogCharacter::GetMaxHp()
{
	return MaxHp;
}
int ARogCharacter::GetExp()
{
	return Exp;
}
void ARogCharacter::SetExp(int exp)
{
	Exp = exp;
}
int ARogCharacter::GetNextExp()
{

	return 100;
}
// Called to bind functionality to input
void ARogCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void ARogCharacter::Attack(FVector FireDirection,FVector gunoffset)
{
	if (bCanFire == true)
	{
		// If we are pressing fire stick in a direction
		if (FireDirection.SizeSquared() > 0.0f)
		{

			UWorld* const World = GetWorld();
			const FRotator FireRotation = FireDirection.Rotation();
			const FVector SpawnLocation = GetActorLocation(); //+ FireRotation.RotateVector(GunOffset);
			// Spawn projectile at an offset from this pawn
			PlayAnimMontage(Animmontage, 1);
			//FVector gunoffset = Cast<AGun>(Weapon)->GunOffset;
			//FVector gunoffset = FVector(30,0,0);
			if (World != NULL)
			{
				ABullet* bullet;
				// spawn the projectile
				//bullet = World->SpawnActor<ABullet>(SpawnLocation + FireRotation.RotateVector(gunoffset), FireRotation);
				bullet = World->SpawnActor<ABullet>(SpawnLocation + gunoffset, FireRotation);
				bullet->Shooter = this;
				int critD = 1;
				if (FMath::RandRange(0, 100) < Crit)
					critD = CritDmg;
				bullet->SetDmg(Dmg* critD);
				if (BulletEffect != nullptr)
				{
					bullet->SetParticle(BulletEffect);
				}
				if (HitEffect != nullptr)
				{
					bullet->SetHitParticle(HitEffect);
				}
				if (AttackSound != nullptr)
				{
					UGameplayStatics::PlaySoundAtLocation(this, AttackSound, GetActorLocation());
				}
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ARogCharacter::AttackTimerExpired, AttackRate);
			SetActorRotation(FireRotation);
			// try and play the sound if specified
		//	if (FireSound != nullptr)
			//{
				//UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			//}
		}
	}
}
void ARogCharacter::AttackTimerExpired()
{
	bCanFire = true;
	bCanDmg = true;
}
void ARogCharacter::HpBarTimerExpired()
{
	HpWidgetComp->SetVisibility(false);
}
void ARogCharacter::Death()
{
	if (live)
	{
		if (Deathmontage != nullptr)
			PlayAnimMontage(Deathmontage, 1);
		if(DeathSound !=nullptr)
			UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	MeshComponent->SetSimulatePhysics(true);
	UCapsuleComponent* capsule = GetCapsuleComponent();
	capsule->SetEnableGravity(false);
	capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	live = false;
	if (Target != nullptr)
	{
		int gex = 20;
		if (this->isBoss())
			gex = 100;
		Target->SetExp(Target->GetExp() + gex);
	}
	DropItem();
	UWorld* const World = GetWorld();
	World->GetTimerManager().SetTimer(TimerHandle_DeathTimerExpired, this, & ARogCharacter::ObjDestroy, 5);
}
void ARogCharacter::Resurrect()
{
	live = true;
	Hp += 20;
	bCanResurrect = false;
	MeshComponent->SetCollisionProfileName("NoCollision");
	MeshComponent->SetSimulatePhysics(false);
	UCapsuleComponent* capsule = GetCapsuleComponent();
	//MeshComponent->AttachToComponent(capsule,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	MeshComponent->AttachTo(capsule);
	MeshComponent->SetRelativeLocation(FVector(0, 0, -90));
	MeshComponent->SetRelativeRotation(FRotator(0, -90, 0));
	//MeshComponent->SetWorldLocation(GetActorLocation(), false, nullptr, ETeleportType::TeleportPhysics);
	//MeshComponent->SetRelativeLocation(FVector(0, 0, -90), false, nullptr, ETeleportType::TeleportPhysics);
	capsule->SetEnableGravity(true);
	capsule->SetCollisionProfileName("Pawn");
	//MeshComponent->SetTeleportDistanceThreshold
	//MeshComponent->locaion
	//SetActorRotation(FRotator(0,GetActorRotation().Yaw,0));

}
void ARogCharacter::SetResurrect(bool r)
{
	bCanResurrect = r;
}
bool ARogCharacter::GetResurrect()
{
	return bCanResurrect;
}
void ARogCharacter::Equip_Implementation(AItem* item)
{
	/*if (Weapon == nullptr)
	{
		FName handsocket = TEXT("Hand_R");
		FRotator SpawnRotation;
		Weapon = item;
		Weapon->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepWorldTransform, handsocket);
		if (item->GetClass() == AKnife::StaticClass())
		{
			SpawnRotation = FRotator(0, -90, 90);
			Weapon->SetActorRelativeLocation(FVector(-12, 0, -3));
		}
		else
		{
			SpawnRotation = FRotator(0, -100, 185);
			Weapon->SetActorRelativeLocation(FVector(-5, 0, -5));
		}
		Weapon->SetActorRelativeRotation(SpawnRotation);
		Weapon->IsUse = true;
		Weapon->faction = faction;
		Weapon->Setting();
		range = Weapon->range;
		AttackRate = Weapon->AttackRate;
		bCanDmg = false;
	}
	else
	{
		
	}*/
}
void ARogCharacter::HitDamage_Implementation(int damage, FVector dir)
{
	FVector knockback = dir;
	int damaged = damage - Armor;
	UWorld* const World = GetWorld();
	const FVector SpawnLocation = GetActorLocation();

	if (HitSound != nullptr)
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	//RootComponent->MoveComponent(dir, GetActorLocation().Rotation(), true);
	Uidmg = damaged;
	Hp -= damaged;
	if (!isboss )
	{
		HpWidgetComp->SetVisibility(true);
		World->GetTimerManager().SetTimer(TimerHandle_HpTimerExpired, this, &ARogCharacter::HpBarTimerExpired, 5);
	}
	//if(target)
	// //+ FireRotation.RotateVector(GunOffset);
	// Spawn projectile at an offset from this pawn
	if (World != NULL)
	{
		ARogTextActor* textActor;
		// spawn the projectile
		textActor = World->SpawnActor<ARogTextActor>(SpawnLocation, GetActorRotation());
		textActor->SetText(FString::FromInt(damaged));
	}
}
bool ARogCharacter::isBoss()
{
	return isboss;
}
FString ARogCharacter::GetName()
{
	return Name;
}
void ARogCharacter:: SetDmg(int32 dmg)
{
	Dmg = dmg;
}
void ARogCharacter::SetMaxHp(int32 maxhp)
{
	MaxHp = maxhp;
}
void ARogCharacter::SetMoveSpeed(float movespeed)
{
	MoveSpeed = movespeed;
}
void ARogCharacter::SetCooldownRate(float cooldownrate)
{
	CooldownRate = cooldownrate;
}
void ARogCharacter::ObjDestroy()
{
	if (bCanResurrect)
		Resurrect();
	else if(!live)
		Destroy();
}
void ARogCharacter::DropItem()
{
	float spawnChance = FMath::RandRange(0, 99);
	int envitr = 0;
	UWorld* const World = GetWorld();
	if (spawnChance < 20)
	{
		UWorld* const world = GetWorld();
		//float length = Length;
		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.Z = SpawnLocation.Z + 180;
		const FVector Dir = FVector(FMath::RandRange(0, 360), 0.0f, 0.0f);
		const FRotator SpawnRotation = Dir.Rotation();
		ARogItem* item;
		item = world->SpawnActor<ARogItem>(SpawnLocation, SpawnRotation);
	}
}
bool ARogCharacter::isLive()
{
	return live;
}
int ARogCharacter::GetLevelCount()
{
	return levelcount;
}
void ARogCharacter::SetLevelCount(int lc)
{
	levelcount = lc;
}