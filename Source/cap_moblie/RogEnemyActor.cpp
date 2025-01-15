// Fill out your copyright notice in the Description page of Project Settings.


#include "RogEnemyActor.h"
#include "EnemyDatatable.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Particles/ParticleSystem.h"
#include "Animation/AnimMontage.h"
#include "Sound/SoundBase.h"
// Sets default values
ARogEnemyActor::ARogEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UDataTable>enemydatatable(TEXT("/Game/DataTables/EnemyDataTable"));

	static ConstructorHelpers::FObjectFinder<UClass> AnimFinder_Mace(TEXT("Class'/Game/polymace/polymacebp/Serath_AnimBlueprint.Serath_AnimBlueprint_C'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimFinder_Archer(TEXT("Class'/Game/polyArcher/polyArcherbp/Sparrow_AnimBlueprint.Sparrow_AnimBlueprint_C'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimFinder_Punch(TEXT("Class'/Game/polyPunch/polyPunchbp/Crunch_AnimBlueprint.Crunch_AnimBlueprint_C'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimFinder_Sorcery(TEXT("Class'/Game/polySorcery/polySorcerybp/Gideon_AnimBlueprint.Gideon_AnimBlueprint_C'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimFinder_Magic(TEXT("Class'/Game/polyMagic/polyMagicbp/Fey_AnimBlueprint.Fey_AnimBlueprint_C'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimFinder_Sword(TEXT("Class'/Game/polySword/polySwordbp/Sword_AnimBlueprint.Sword_AnimBlueprint_C'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimFinder_Staff(TEXT("Class'/Game/polyStaff/polyStaffbp/Staff_AnimBlueprint.Staff_AnimBlueprint_C'"));


	static ConstructorHelpers::FObjectFinder<UAnimMontage> animmontage_Mace(TEXT("/Game/polymace/Primary_Attack_A_Medium_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> animmontage_Archer(TEXT("/Game/polyarcher/Primary_Fire_Med_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> animmontage_Punch(TEXT("/Game/polyPunch/Ability_Combo_02_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> animmontage_Sorcery(TEXT("/Game/polySorcery/Primary_Attack_B_Medium_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> animmontage_Magic(TEXT("/Game/polyMagic/Ability_LMB_B_Medium_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> animmontage_Sword(TEXT("/Game/polySword/A_SW_Attack_01_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> animmontage_Staff(TEXT("/Game/polyStaff/skill14_Montage"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> deathmontage_Mace(TEXT("/Game/polymace/Death_Fwd_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> deathmontage_Archer(TEXT("/Game/polyarcher/Death_Fwd_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> deathmontage_Punch(TEXT("/Game/polyPunch/Death_A_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> deathmontage_Sorcery(TEXT("/Game/polySorcery/Death_Fwd_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> deathmontage_Magic(TEXT("/Game/polyMagic/Death_Fwd_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> deathmontage_Sword(TEXT("/Game/polyStaff/Dead_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> deathmontage_Staff(TEXT("/Game/polyStaff/Dead_Montage"));
	
	static ConstructorHelpers::FObjectFinder<USoundBase> sound_Mace(TEXT("/Game/Sounds/Character/Enemies_(Finish)/e1_Attack"));
	static ConstructorHelpers::FObjectFinder<USoundBase> sound_Archer(TEXT("/Game/Sounds/Character/Enemies_(Finish)/e5_Attack"));
	static ConstructorHelpers::FObjectFinder<USoundBase> sound_Punch(TEXT("/Game/Sounds/Character/Enemies_(Finish)/e13_Attack"));
	static ConstructorHelpers::FObjectFinder<USoundBase> sound_Sorcery(TEXT("/Game/Sounds/Character/Enemies_(Finish)/e24_Attack"));
	static ConstructorHelpers::FObjectFinder<USoundBase> sound_Magic(TEXT("/Game/Sounds/Character/Enemies_(Finish)/e24_Attack"));
	static ConstructorHelpers::FObjectFinder<USoundBase> sound_Sword(TEXT("/Game/Sounds/Character/Enemies_(Finish)/e15_Attack"));
	static ConstructorHelpers::FObjectFinder<USoundBase> sound_Staff(TEXT("/Game/Sounds/Character/Enemies_(Finish)/e28_Attack"));
	static ConstructorHelpers::FObjectFinder<USoundBase> dead_Mace(TEXT("/Game/Sounds/Character/Enemies_(Finish)/e1_Dead"));
	static ConstructorHelpers::FObjectFinder<USoundBase> dead_Archer(TEXT("/Game/Sounds/Character/Enemies_(Finish)/e5_Dead"));
	static ConstructorHelpers::FObjectFinder<USoundBase> dead_Punch(TEXT("/Game/Sounds/Character/Enemies_(Finish)/e13_Dead"));
	static ConstructorHelpers::FObjectFinder<USoundBase> dead_Sorcery(TEXT("/Game/Sounds/Character/Enemies_(Finish)/e7_Dead"));
	static ConstructorHelpers::FObjectFinder<USoundBase> dead_Magic(TEXT("/Game/Sounds/Character/Enemies_(Finish)/e7_Dead"));
	static ConstructorHelpers::FObjectFinder<USoundBase> dead_Sword(TEXT("/Game/Sounds/Character/Enemies_(Finish)/e4_Dead"));
	static ConstructorHelpers::FObjectFinder<USoundBase> dead_Staff(TEXT("/Game/Sounds/Character/Enemies_(Finish)/e9_Dead"));
	if (enemydatatable.Succeeded())
	{
		EnemyDataTable = enemydatatable.Object;
	}
	if (EnemyDataTable != nullptr)
	{
		USkeletalMesh* mesh;
		USkeletalMesh* weapon;
		UClass* anim;
		UAnimMontage* montage;
		UAnimMontage* deathmontage;
		UParticleSystem* effect;
		UParticleSystem* hiteffect;
		USoundBase* sound;
		USoundBase* deathsound;
		//int dmg, hp, speed;
		//float dmgrate, range;
		for (int i = 1; i < 30; i++)
		{
			FEnemyTableRow* EnemyTableRow = EnemyDataTable->FindRow<FEnemyTableRow>(FName(*FString::FormatAsNumber(i)), FString(""));
			mesh = (*EnemyTableRow).CharacterMeshPath.Get();
			weapon = (*EnemyTableRow).WeaponMeshPath.Get();
			effect = (*EnemyTableRow).EffectPath.Get();
			hiteffect = (*EnemyTableRow).HitEffectPath.Get();
			CharacterMeshPath.Add(mesh);
			WeaponMeshPath.Add(weapon);
			EffectPath.Add(effect);
			HitEffectPath.Add(hiteffect);
			Dmg.Add((*EnemyTableRow).Dmg);
			DmgRate.Add((*EnemyTableRow).DmgRate);
			Hp.Add((*EnemyTableRow).Hp);
			Speed.Add((*EnemyTableRow).Speed);
			Range.Add((*EnemyTableRow).Range);
			
			int type = (*EnemyTableRow).Type;
			switch (type)
			{
			case 0:
				if (AnimFinder_Mace.Object != nullptr)
			{
				anim = AnimFinder_Mace.Object;
			} 
				if (animmontage_Mace.Object !=nullptr)
					montage = animmontage_Mace.Object;
				if (deathmontage_Mace.Object != nullptr)
					deathmontage = deathmontage_Mace.Object;
				if (sound_Mace.Object != nullptr)
					sound = sound_Mace.Object;
				if (dead_Mace.Object != nullptr)
					deathsound = dead_Mace.Object;
				break;
			case 1:
				if (AnimFinder_Archer.Object != nullptr)
				{
					anim = AnimFinder_Archer.Object;
				}
				if (animmontage_Archer.Object != nullptr)
					montage = animmontage_Archer.Object;
				if (deathmontage_Archer.Object != nullptr)
					deathmontage = deathmontage_Archer.Object;
				if (sound_Archer.Object != nullptr)
					sound = sound_Archer.Object;
				if (dead_Archer.Object != nullptr)
					deathsound = dead_Archer.Object;
				 break;
			case 2: 
				if (AnimFinder_Punch.Object != nullptr)
				{
					anim = AnimFinder_Punch.Object;
				}
				if (animmontage_Punch.Object != nullptr)
					montage = animmontage_Punch.Object;
				if (deathmontage_Punch.Object != nullptr)
					deathmontage = deathmontage_Punch.Object;
				if (sound_Punch.Object != nullptr)
					sound = sound_Punch.Object;
				if (dead_Punch.Object != nullptr)
					deathsound = dead_Punch.Object;
				break;
			case 3: 
				if (AnimFinder_Magic.Object != nullptr)
				{
					anim = AnimFinder_Magic.Object;
				}
				if (animmontage_Magic.Object != nullptr)
					montage = animmontage_Magic.Object;
				if (deathmontage_Magic.Object != nullptr)
					deathmontage = deathmontage_Magic.Object;
				if (sound_Magic.Object != nullptr)
					sound = sound_Magic.Object;
				if (dead_Magic.Object != nullptr)
					deathsound = dead_Magic.Object;
				break;
			case 4: 
				if (AnimFinder_Sorcery.Object != nullptr)
				{
					anim = AnimFinder_Sorcery.Object;
				}
				if (animmontage_Sorcery.Object != nullptr)
					montage = animmontage_Sorcery.Object;
				if (deathmontage_Sorcery.Object != nullptr)
					deathmontage = deathmontage_Sorcery.Object;
				if (sound_Sorcery.Object != nullptr)
					sound = sound_Sorcery.Object;
				if (dead_Sorcery.Object != nullptr)
					deathsound = dead_Sorcery.Object;
				break;
			case 5: 
				if (AnimFinder_Staff.Object != nullptr)
				{
					anim = AnimFinder_Staff.Object;
				}
				if (animmontage_Staff.Object != nullptr)
					montage = animmontage_Staff.Object;
				if (deathmontage_Staff.Object != nullptr)
					deathmontage = deathmontage_Staff.Object;
				if (sound_Staff.Object != nullptr)
					sound = sound_Staff.Object;
				if (dead_Staff.Object != nullptr)
					deathsound = dead_Staff.Object;
				break;
			case 6: 
				if (AnimFinder_Sword.Object != nullptr)
				{
					anim = AnimFinder_Sword.Object;
				}
				if (animmontage_Sword.Object != nullptr)
					montage = animmontage_Sword.Object;
				if (deathmontage_Sword.Object != nullptr)
					deathmontage = deathmontage_Sword.Object;
				if (sound_Sword.Object != nullptr)
					sound = sound_Sword.Object;
				if (dead_Sword.Object != nullptr)
					deathsound = dead_Sword.Object;
				break;
			}
			//anim = (*EnemyTableRow).AnimPath.Get();
			AttackSound.Add(sound);
			DeathSoundPath.Add(deathsound);
			AnimPath.Add(anim);
			MontagePath.Add(montage);
			DeathMontagePath.Add(deathmontage);
			Size.Add((*EnemyTableRow).Size);
			Type.Add((*EnemyTableRow).Type);
			Location.Add((*EnemyTableRow).Location);
		}
	}
	envitr = 0;
	MaxEnemyNum = 99;
	EnemyRate = 0.4;
}

// Called when the game starts or when spawned
void ARogEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARogEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
int ARogEnemyActor::Getenvitr()
{
	return envitr;
}
void ARogEnemyActor::Setenvitr(int itr)
{
	envitr = itr;
}
int ARogEnemyActor::GetMaxEnemy()
{
	return MaxEnemyNum;
}
void ARogEnemyActor::SetMaxEnemy(int num)
{
	MaxEnemyNum = num;
}
float ARogEnemyActor::GetEnemyRate()
{
	return EnemyRate;
}
void ARogEnemyActor::SetEnemyRate(float f)
{
	EnemyRate = f;
}

