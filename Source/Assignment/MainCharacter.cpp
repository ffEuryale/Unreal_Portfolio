// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GamePlayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/Soundcue.h"
#include "AssignmentSaveGame.h"
#include "Enemy.h"
#include "MainPlayerController.h"
#include "Weapon.h"
#include "ItemStorage.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 카메라 붐 생성, 물체와 충돌이 있을 경우 플레이어쪽으로 당김
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;			// 카메라를 해당 거리에 생성
	CameraBoom->bUsePawnControlRotation = true;		// 컨트롤러에 따라 카메라 암을 회전

	// 캡슐 콜리전 사이즈 설정
	GetCapsuleComponent()->SetCapsuleSize(34.f, 88.f);

	// FollowCamera 생성
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// 컨트롤러의 방향에 맞춰 카메라를 붐 끝에 위치시키고, 붐과 카메라가 일치할 수 있도록 조정
	FollowCamera->bUsePawnControlRotation = false;

	// 입력에 따른 회전률을 설정
	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;

	// 컨트롤러가 회전할 때 카메라는 회전하되, 캐릭터는 회전하지 않음
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// 캐릭터의 이동 구성
	GetCharacterMovement()->bOrientRotationToMovement = true;			// 입력한 방향으로 이동
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);	// 해당 회전 속도를 통해서
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.2f;

	MaxHealth = 100.f;		// 최대 체력
	Health = 65.f;			// 현재 체력
	MaxStamina = 150.f;		// 최대 스테미너
	Stamina = 120.f;		// 초기 스테미너
	Coins = 0;				// 초기 소지금

	RunningSpeed = 400.f;	// 달리기 속도
	SprintingSpeed = 650.f;	// 스프린트 속도

	bShiftKeyDown = false;
	bMouseLeftButtonDown = false;
	bWeaponPickupButtonDown = false;
	bESCDown = false;

	// enum 문 초기화
	MovementStatus = EMovementStatus::EMS_Normal;
	StaminaStatus = EStaminaStatus::ESS_Normal;

	StaminaDrainRate = 20.f;	// 스태미너 충전량
	MinSprintStamina = 50.f;	// 달릴 수 있는 최저 스태미너

	InterpSpeed = 15.f;

	bInterpToEnemy = false;

	bHasCombatTarget = false;

	bMovingForward = false;
	bMovingRight = false;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	MainPlayerController = Cast<AMainPlayerController>(GetController());

	FString Map = GetWorld()->GetMapName();
	Map.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	/**
	if (Map != "SunTemple")
	{
		LoadGameSwitch();

		if (MainPlayerController)
		{
			MainPlayerController->GameModeOnly();
		}
	}
	*/
	LoadGameSwitch();
	if (MainPlayerController)
	{
		MainPlayerController->GameModeOnly();
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementStatus == EMovementStatus::EMS_Dead) return;

	float DeltaStamina = StaminaDrainRate * DeltaTime;

	switch (StaminaStatus)
	{
	case EStaminaStatus::ESS_Normal:
		RunningSpeed = 400.f;

		if (bShiftKeyDown)	// 시프트 키를 눌렀을 때
		{
			if (bMovingForward || bMovingRight)
			{
				if (Stamina - DeltaStamina <= MinSprintStamina)
				{
					SetStaminaStatus(EStaminaStatus::ESS_BeloMinimum);
					Stamina -= DeltaStamina;
				}
				else
				{
					Stamina -= DeltaStamina;
				}

				SetMovementStatus(EMovementStatus::EMS_Sprinting);
			}
			else SetMovementStatus(EMovementStatus::EMS_Normal);
		}
		else	// 시프트 키를 뗐을 때
		{
			if (Stamina + DeltaStamina >= MaxStamina)
			{
				Stamina = MaxStamina;
			}
			else
			{
				Stamina += DeltaStamina;
			}

			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
	break;

	case EStaminaStatus::ESS_BeloMinimum:
		if (bShiftKeyDown)	// 시프트 키를 눌렀을 때
		{
			if (Stamina - DeltaStamina <= 0.f)
			{
				SetStaminaStatus(EStaminaStatus::ESS_Exhausted);
				Stamina = 0;
				SetMovementStatus(EMovementStatus::EMS_Normal);

				RunningSpeed = 250.f;
			}
			else
			{
				if (bMovingForward || bMovingRight) SetMovementStatus(EMovementStatus::EMS_Sprinting);
				else
				{
					RunningSpeed = 400.f;

					SetMovementStatus(EMovementStatus::EMS_Normal);
				}

				Stamina -= DeltaStamina;
			}
		}
		else	// 시프트 키를 뗐을 때
		{
			if (Stamina + DeltaStamina >= MinSprintStamina)
			{
				Stamina += DeltaStamina;
				RunningSpeed = 400.f;
				SetStaminaStatus(EStaminaStatus::ESS_Normal);
			}
			else
			{
				Stamina += DeltaStamina;
				RunningSpeed = 400.f;
			}

			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
	break;

	case EStaminaStatus::ESS_Exhausted:

		if (bMovingForward || bMovingRight)
		{
			if (bShiftKeyDown)	// 시프트 키를 눌렀을 때
			{
				Stamina = 0.f;
			}
			else	// 시프트 키를 뗐을 때
			{
				Stamina += DeltaStamina;
				SetStaminaStatus(EStaminaStatus::ESS_ExhaustedRecovering);
			}

			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
	break;

	case EStaminaStatus::ESS_ExhaustedRecovering:

		if (bMovingForward || bMovingRight)
		{
			if (Stamina + DeltaStamina >= MinSprintStamina)
			{
				Stamina += DeltaStamina;
				SetStaminaStatus(EStaminaStatus::ESS_Normal);
			}
			else
			{
				Stamina += DeltaStamina;
			}

			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
	break;
	}

	if (bInterpToEnemy && CombatTarget)
	{
		FRotator LookAtYaw = GetLookAtRotationYaw(CombatTarget->GetActorLocation());
		FRotator InterpRotation = FMath::RInterpTo(GetActorRotation(), LookAtYaw, DeltaTime, InterpSpeed);

		SetActorRotation(InterpRotation);
	}

	if (CombatTarget)
	{
		CombatTargetLocation = CombatTarget->GetActorLocation();

		if (MainPlayerController)
		{
			MainPlayerController->EnemyLocation = CombatTargetLocation;
		}
	}
}

FRotator AMainCharacter::GetLookAtRotationYaw(FVector Target)
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target);
	FRotator LookAtRotationYaw(0.f, LookAtRotation.Yaw, 0.f);

	return LookAtRotationYaw;
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::ShiftkeyDown);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::ShiftkeyUp);

	PlayerInputComponent->BindAction("ESC", IE_Pressed, this, &AMainCharacter::ESCDown);
	PlayerInputComponent->BindAction("ESC", IE_Released, this, &AMainCharacter::ESCUp);

	PlayerInputComponent->BindAction("WeaponPickup", IE_Pressed, this, &AMainCharacter::WeaponPickupButtonDown);
	PlayerInputComponent->BindAction("WeaponPickup", IE_Released, this, &AMainCharacter::WeaponPickupButtonUp);

	PlayerInputComponent->BindAction("LeftMouseButtonDown", IE_Pressed, this, &AMainCharacter::MouseLeftButtonDown);
	PlayerInputComponent->BindAction("LeftMouseButtonDown", IE_Released, this, &AMainCharacter::MouseLeftButtonUp);

	PlayerInputComponent->BindAction("RightMouseButtonDown", IE_Pressed, this, &AMainCharacter::MouseRightButtonDown);
	PlayerInputComponent->BindAction("RightMouseButtonDown", IE_Released, this, &AMainCharacter::MouseRightButtonUp);

	/*
	PlayerInputComponent->BindAction("CameraBoomInit", IE_Pressed, this, &AMainCharacter::LeftTriggerDown);
	PlayerInputComponent->BindAction("CameraBoomInit", IE_Released, this, &AMainCharacter::LeftTriggerUp);
	*/

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AMainCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMainCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainCharacter::LookUpAtRate);

	PlayerInputComponent->BindAxis("Zoom", this, &AMainCharacter::OnZoom);

}

bool AMainCharacter::CanMove(float value)
{
	if (MainPlayerController)
	{
		return	value != 0.0f && 
				!bAttacking &&
				MovementStatus != EMovementStatus::EMS_Dead &&
				!MainPlayerController->bPauseMenuVisible;
	}
	return false;
}

void AMainCharacter::Turn(float value)
{
	if (CanMove(value))
	{
		AddControllerYawInput(value);
	}
}

void AMainCharacter::LookUp(float value)
{
	if (CanMove(value))
	{
		AddControllerPitchInput(value);
	}
}

void AMainCharacter::MoveForward(float value)
{
	bMovingForward = false;

	if (CanMove(value))
	{
		// 앞으로 갈 방향 확인
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);


		bMovingForward = true;
	}
}

void AMainCharacter::MoveRight(float value)
{
	bMovingRight = false;

	if (CanMove(value))
	{
		// 옆으로 갈 방향 확인
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);

		bMovingRight = true;
	}
}

void AMainCharacter::TurnAtRate(float rate)
{
	AddControllerYawInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());

}

void AMainCharacter::LookUpAtRate(float rate)
{
	AddControllerPitchInput(rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());

}

void AMainCharacter::OnZoom(float axis)
{
	CameraBoom->TargetArmLength -= (10 * axis);

	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength, 80.f, 650.f);
}

void AMainCharacter::WeaponPickupButtonDown()
{
	if (MainPlayerController)
	{
		if (MainPlayerController->bPauseMenuVisible) return;
	}

	bWeaponPickupButtonDown = true;

	if (ActiveOverlappingItem)
	{
		AWeapon* Weapon = Cast<AWeapon>(ActiveOverlappingItem);

		if (Weapon)
		{
			Weapon->Equip(this);
			SetActiveOverlappingItem(nullptr);
		}
	}
}

void AMainCharacter::WeaponPickupButtonUp()
{
	bWeaponPickupButtonDown = false;
}

void AMainCharacter::ESCDown()
{
	bESCDown = true;

	if (MainPlayerController)
	{
		MainPlayerController->TogglePauseMenu();
	}
}

void AMainCharacter::ESCUp()
{
	bESCDown = false;
}

void AMainCharacter::MouseLeftButtonDown()
{
	bMouseLeftButtonDown = true;

	if (MovementStatus == EMovementStatus::EMS_Dead) return;

	if (MainPlayerController)
	{
		if (MainPlayerController->bPauseMenuVisible) return;
	}

	if (EquippedWeapon)
	{
		Attack();
	}

}

void AMainCharacter::MouseLeftButtonUp()
{
	bMouseLeftButtonDown = false;
}

void AMainCharacter::MouseRightButtonDown()
{
	bMouseRightButtonDown = true;

	if (MovementStatus == EMovementStatus::EMS_Dead) return;

	if (EquippedWeapon)
	{
		AttackKick();
	}

}

void AMainCharacter::MouseRightButtonUp()
{
	bMouseRightButtonDown = false;
}

/*
void AMainCharacter::LeftTriggerDown()
{
	bLeftTriggerDown = true;

	LTrigger();
}

void AMainCharacter::LeftTriggerUp()
{
	bLeftTriggerDown = false;
}
*/

void AMainCharacter::SetEquippedWeapon(AWeapon* WeaponToSet)
{
	if (EquippedWeapon)
	{
		EquippedWeapon->Destroy();
	}

	EquippedWeapon = WeaponToSet;
}

void AMainCharacter::DecrementHealth(float Amount)
{
	if (Health - Amount <= 0)
	{
		Health -= Amount;
		Die();
	}
	else
	{
		Health -= Amount;
	}
}

void AMainCharacter::IncrementCoins(int32 Amount)
{
	Coins += Amount;
}

void AMainCharacter::IncrementHealth(float Amount)
{
	if (Health + Amount >= MaxHealth)
	{
		Health = MaxHealth;
	}
	else
	{
		Health += Amount;
	}
}

void AMainCharacter::IncrementStamina(float Amount)
{
	if (Stamina + Amount >= MaxStamina)
	{
		Stamina = MaxStamina;
	}
	else
	{
		Stamina += Amount;
	}
}

void AMainCharacter::Die()
{
	if (MovementStatus == EMovementStatus::EMS_Dead) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (AnimInstance && CombatMontage)
	{
		AnimInstance->Montage_Play(CombatMontage);
		AnimInstance->Montage_JumpToSection(FName("Death"));
	}

	SetMovementStatus(EMovementStatus::EMS_Dead);
}

void AMainCharacter::Jump()
{
	if (MainPlayerController)
	{
		if (MainPlayerController->bPauseMenuVisible) return;
	}

	if (MovementStatus != EMovementStatus::EMS_Dead)
	{
		Super::Jump();
	}
}

void AMainCharacter::SetMovementStatus(EMovementStatus status)
{
	AMainCharacter::MovementStatus = status;
	if (MovementStatus == EMovementStatus::EMS_Sprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}

}

void AMainCharacter::ShiftkeyDown()
{
	bShiftKeyDown = true;
}

void AMainCharacter::ShiftkeyUp()
{
	bShiftKeyDown = false;
}

void AMainCharacter::ShowPickupLocations()
{
	for (FVector Location : PickupLocations)
	{
		UKismetSystemLibrary::DrawDebugSphere(this, Location, 25.f, 8, FLinearColor::Green, 10.f, 0.5f);
	}

}

void AMainCharacter::Attack()
{
	if (!bAttacking && MovementStatus != EMovementStatus::EMS_Dead)
	{
		bAttacking = true;
		SetInterpToEnemy(true);

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if (AnimInstance && CombatMontage)
		{
			int32 Section = FMath::RandRange(0, 1);

			switch (Section)
			{
			case 0:
				AnimInstance->Montage_Play(CombatMontage, 1.2f);
				AnimInstance->Montage_JumpToSection(FName("Attack_1"), CombatMontage);
				break;
			case 1:
				AnimInstance->Montage_Play(CombatMontage, 1.5f);
				AnimInstance->Montage_JumpToSection(FName("Attack_2"), CombatMontage);
				break;
			}
		}

		if (EquippedWeapon->SwingSward)
		{
			//UGameplayStatics::PlaySound2D(this, EquippedWeapon->SwingSward);
		}
	}
}

void AMainCharacter::AttackKick()
{
	if (!bAttacking)
	{
		bAttacking = true;

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if (AnimInstance && CombatMontage)
		{
			AnimInstance->Montage_Play(CombatMontage, 1.f);
			AnimInstance->Montage_JumpToSection(FName("Attack_3"), CombatMontage);
		}
	}
}

void AMainCharacter::AttackEnd()
{
	bAttacking = false;
	SetInterpToEnemy(false);

	if (bMouseLeftButtonDown)
	{
		Attack();
	}

	if (bMouseRightButtonDown)
	{
		AttackKick();
	}
}

void AMainCharacter::PlaySwingSound()
{
	if (EquippedWeapon->SwingSward)
	{
		UGameplayStatics::PlaySound2D(this, EquippedWeapon->SwingSward);
	}

}

void AMainCharacter::SetInterpToEnemy(bool Interp)
{
	bInterpToEnemy = Interp;
}

float AMainCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Health - DamageAmount <= 0)
	{
		Health -= DamageAmount;
		Die();

		if (DamageCauser)
		{
			AEnemy* Enemy = Cast<AEnemy>(DamageCauser);

			if (Enemy)
			{
				Enemy->bHasValidTarget = false;
			}
		}
	}
	else
	{
		Health -= DamageAmount;
	}

	return DamageAmount;
}

void AMainCharacter::DeathEnd()
{
	GetMesh()->bPauseAnims = true;
	GetMesh()->bNoSkeletonUpdate = true;
}

void AMainCharacter::UpdateCombatTarget()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, EnemyFilter);

	if (OverlappingActors.Num() == 0)
	{
		if (MainPlayerController)
		{
			MainPlayerController->RemoveEnemyHealthBar();
		}

		return;
	}

	AEnemy* ClosetEnemy = Cast<AEnemy>(OverlappingActors[0]);

	if (ClosetEnemy)
	{
		FVector Location = GetActorLocation();
		float MinDistance = (ClosetEnemy->GetActorLocation() - Location).Size();

		for (auto Actor : OverlappingActors)
		{
			AEnemy* Enemy = Cast<AEnemy>(Actor);

			if (Enemy)
			{
				float DistanceToActor = (Enemy->GetActorLocation() - Location).Size();

				if (DistanceToActor < MinDistance)
				{
					MinDistance = DistanceToActor;
					ClosetEnemy = Enemy;
				}
			}
		}

		if (MainPlayerController)
		{
			MainPlayerController->DisplayEnemyHealthBar();
		}
		
		SetCombatTarget(ClosetEnemy);
		bHasCombatTarget = true;
	}
}

void AMainCharacter::SwitchLevel(FName LevelName)
{
	UWorld* World = GetWorld();
	
	if (World)
	{
		FString CurrentLevel = World->GetMapName();
		FName CurrentLevelName(*CurrentLevel);

		if (CurrentLevelName != LevelName)
		{
			UGameplayStatics::OpenLevel(World, LevelName);
		}
	}
}

void AMainCharacter::SaveGame()
{
	UAssignmentSaveGame* SaveGameInstance = Cast<UAssignmentSaveGame>(UGameplayStatics::CreateSaveGameObject(UAssignmentSaveGame::StaticClass()));
	
	SaveGameInstance->CharacterStats.Health			= Health;
	SaveGameInstance->CharacterStats.MaxHealth		= MaxHealth;
	SaveGameInstance->CharacterStats.Stamina		= Stamina;
	SaveGameInstance->CharacterStats.MaxStamina		= MaxStamina;
	SaveGameInstance->CharacterStats.Coins			= Coins;

	FString MapName = GetWorld()->GetMapName();
	MapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	SaveGameInstance->CharacterStats.LevelName = MapName;

	if (EquippedWeapon)
	{
		SaveGameInstance->CharacterStats.WeaponName = EquippedWeapon->Name;
	}

	SaveGameInstance->CharacterStats.Location = GetActorLocation();
	SaveGameInstance->CharacterStats.Rotation = GetActorRotation();

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->PlayerName, SaveGameInstance->UserIndex);
}

void AMainCharacter::LoadGame(bool SetPosition)
{
	UAssignmentSaveGame* LoadGameInstance = Cast<UAssignmentSaveGame>(UGameplayStatics::CreateSaveGameObject(UAssignmentSaveGame::StaticClass()));

 	LoadGameInstance = Cast<UAssignmentSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->PlayerName, LoadGameInstance->UserIndex));
	
	Health		= LoadGameInstance->CharacterStats.Health;
	MaxHealth	= LoadGameInstance->CharacterStats.MaxHealth;
	Stamina		= LoadGameInstance->CharacterStats.Stamina;
	MaxStamina	= LoadGameInstance->CharacterStats.MaxStamina;
	Coins		= LoadGameInstance->CharacterStats.Coins;

	if (WeaponStorage)
	{
		AItemStorage* Weapons = GetWorld()->SpawnActor<AItemStorage>(WeaponStorage);

		if (Weapons)
		{
			FString WeaponName = LoadGameInstance->CharacterStats.WeaponName;
			 
			if (WeaponName != TEXT(""))
			{
				AWeapon* WeaponToEquip = GetWorld()->SpawnActor<AWeapon>(Weapons->WeaponMap[WeaponName]);
				WeaponToEquip->Equip(this);
			}
		}
	}

	if (SetPosition)
	{
		SetActorLocation(LoadGameInstance->CharacterStats.Location);
		SetActorRotation(LoadGameInstance->CharacterStats.Rotation);
	}

	SetMovementStatus(EMovementStatus::EMS_Normal);
	GetMesh()->bPauseAnims = false;
	GetMesh()->bNoSkeletonUpdate = false;

	if (LoadGameInstance->CharacterStats.LevelName != TEXT(""))
	{
		FName LevelName(*LoadGameInstance->CharacterStats.LevelName);

		SwitchLevel(LevelName);
	}
}

void AMainCharacter::LoadGameSwitch()
{
	UAssignmentSaveGame* LoadGameInstance = Cast<UAssignmentSaveGame>(UGameplayStatics::CreateSaveGameObject(UAssignmentSaveGame::StaticClass()));

	LoadGameInstance = Cast<UAssignmentSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->PlayerName, LoadGameInstance->UserIndex));

	Health = LoadGameInstance->CharacterStats.Health;
	MaxHealth = LoadGameInstance->CharacterStats.MaxHealth;
	Stamina = LoadGameInstance->CharacterStats.Stamina;
	MaxStamina = LoadGameInstance->CharacterStats.MaxStamina;
	Coins = LoadGameInstance->CharacterStats.Coins;

	if (WeaponStorage)
	{
		AItemStorage* Weapons = GetWorld()->SpawnActor<AItemStorage>(WeaponStorage);

		if (Weapons)
		{
			FString WeaponName = LoadGameInstance->CharacterStats.WeaponName;

			if (WeaponName != TEXT(""))
			{
				AWeapon* WeaponToEquip = GetWorld()->SpawnActor<AWeapon>(Weapons->WeaponMap[WeaponName]);
				WeaponToEquip->Equip(this);
			}
		}
	}

	SetMovementStatus(EMovementStatus::EMS_Normal);
	GetMesh()->bPauseAnims = false;
	GetMesh()->bNoSkeletonUpdate = false;
}

/*
void AMainCharacter::LTrigger()
{
	if (!bCameraLocationInit)
	{
		bCameraLocationInit = true;


	}

}
*/

