// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal			UMETA(DisplayName = "Normal"),
	EMS_Sprinting		UMETA(DisplayName = "Sprinting"),
	EMS_Dead			UMETA(DisplayName = "Dead"),
	EMS_MAX				UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal					UMETA(DisplayName = "Normal"),
	ESS_BeloMinimum				UMETA(DisplayName = "_BeloMinimum"),
	ESS_Exhausted				UMETA(DisplayName = "Exhaust"),
	ESS_ExhaustedRecovering		UMETA(DisplayName = "ExhaustedRecovering"),
	ESS_Max						UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class ASSIGNMENT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(EditDefaultsOnly, Category = "SaveData")
	TSubclassOf<class AItemStorage> WeaponStorage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bHasCombatTarget;

	FORCEINLINE void SetHasCombatTarget(bool HasTarget) { bHasCombatTarget = HasTarget; }
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	FVector CombatTargetLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AMainPlayerController* MainPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class USoundCue* HitSound;

	TArray<FVector> PickupLocations;

	UFUNCTION(BlueprintCallable)
	void ShowPickupLocations();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EStaminaStatus StaminaStatus;

	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaDrainRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinSprintStamina;

	float InterpSpeed;
	bool bInterpToEnemy;
	void SetInterpToEnemy(bool Interp);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	class AEnemy* CombatTarget;

	FORCEINLINE void SetCombatTarget(AEnemy* Target) { CombatTarget = Target; }

	FRotator GetLookAtRotationYaw(FVector Target);

	// ������ ���� �� �̵� �ӵ� ����
	void SetMovementStatus(EMovementStatus status);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float SprintingSpeed;

	bool bShiftKeyDown;
	
	// ������Ʈ ���� ����
	void ShiftkeyDown();

	// ������Ʈ ���� ����
	void ShiftkeyUp();

	// ī�޶� ���� �÷��̾� �ڿ� ��ġ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// ī�޶� �÷��̾ ���󰡰�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// ī�޶��� �⺻ ȸ���ӵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	// �÷��̾� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	float MaxHealth;	// �÷��̾��� �ִ� ü��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Health;		// �÷��̾��� ���� ü��

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	float MaxStamina;	// �÷��̾��� �ִ� ���׹̳�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Stamina;		// �÷��̾��� ���� ���׹̳�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	int32 Coins;		// �÷��̾��� ������

	void DecrementHealth(float Amount);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator,
		AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void IncrementCoins(int32 Amount);

	UFUNCTION(BlueprintCallable)
	void IncrementHealth(float Amount);

	void Die();

	virtual void Jump() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ��, �� �Է� ȣ��
	void MoveForward(float value);
	// ��, �� �Է� ȣ��
	void MoveRight(float value);

	// ��, �Ʒ� ȸ�� ȣ��
	void LookUp(float value);
	// ��, �� ȸ�� ȣ��
	void Turn(float value);

	bool bMovingForward;
	bool bMovingRight;

	bool CanMove(float value);

	// �Է��� ���� ������ �ӵ��� ȸ��
	void TurnAtRate(float rate);

	// �Է��� ���� ��, �Ʒ��� ������ �ӵ��� ȸ��
	void LookUpAtRate(float rate);

	// ���콺 �� ��/�ٿ����� ī�޶� �� ����
	void OnZoom(float axis);

	// ���� �ֿ����
	bool bWeaponPickupButtonDown;
	void WeaponPickupButtonDown();
	void WeaponPickupButtonUp();

	// �Ͻ� ����
	bool bESCDown;
	void ESCDown();
	void ESCUp();

	// 1�� ����
	bool bMouseLeftButtonDown;
	void MouseLeftButtonDown();
	void MouseLeftButtonUp();

	// 2�� ����
	bool bMouseRightButtonDown;
	void MouseRightButtonDown();
	void MouseRightButtonUp();

	/*
	// ���� �е�� ī�޶� ��ġ ĳ������ ��������
	bool bLeftTriggerDown;
	void LeftTriggerDown();
	void LeftTriggerUp();
	*/

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items)
	class AWeapon* EquippedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
	class AItem* ActiveOverlappingItem;

	void SetEquippedWeapon(AWeapon* WeaponToSet);
	FORCEINLINE AWeapon* GetEquippedWeapon() { return EquippedWeapon; }
	FORCEINLINE void SetActiveOverlappingItem(AItem* Item) { ActiveOverlappingItem = Item; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Anims")
	bool bAttacking;

	void Attack();		// 1�� ����
	void AttackKick();	// 2�� ����

	UFUNCTION(BlueprintCallable)
	void AttackEnd();	// ���� ����

	/*
	void LTrigger();	// ī�޶� �� ��ġ ��������

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	bool bCameraLocationInit;
	*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Anims")
	class UAnimMontage* CombatMontage;

	UFUNCTION(BlueprintCallable)
	void PlaySwingSound();

	UFUNCTION(BlueprintCallable)
	void DeathEnd();

	void UpdateCombatTarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TSubclassOf<AEnemy> EnemyFilter;

	void SwitchLevel(FName LevelName);

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame(bool SetPosition);

	void LoadGameSwitch();
};
