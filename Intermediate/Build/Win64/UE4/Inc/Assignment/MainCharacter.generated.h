// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ASSIGNMENT_MainCharacter_generated_h
#error "MainCharacter.generated.h already included, missing '#pragma once' in MainCharacter.h"
#endif
#define ASSIGNMENT_MainCharacter_generated_h

#define Assignment_Source_Assignment_MainCharacter_h_31_SPARSE_DATA
#define Assignment_Source_Assignment_MainCharacter_h_31_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execLoadGame); \
	DECLARE_FUNCTION(execSaveGame); \
	DECLARE_FUNCTION(execDeathEnd); \
	DECLARE_FUNCTION(execPlaySwingSound); \
	DECLARE_FUNCTION(execAttackEnd); \
	DECLARE_FUNCTION(execIncrementStamina); \
	DECLARE_FUNCTION(execIncrementHealth); \
	DECLARE_FUNCTION(execIncrementCoins); \
	DECLARE_FUNCTION(execShowPickupLocations);


#define Assignment_Source_Assignment_MainCharacter_h_31_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execLoadGame); \
	DECLARE_FUNCTION(execSaveGame); \
	DECLARE_FUNCTION(execDeathEnd); \
	DECLARE_FUNCTION(execPlaySwingSound); \
	DECLARE_FUNCTION(execAttackEnd); \
	DECLARE_FUNCTION(execIncrementStamina); \
	DECLARE_FUNCTION(execIncrementHealth); \
	DECLARE_FUNCTION(execIncrementCoins); \
	DECLARE_FUNCTION(execShowPickupLocations);


#define Assignment_Source_Assignment_MainCharacter_h_31_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMainCharacter(); \
	friend struct Z_Construct_UClass_AMainCharacter_Statics; \
public: \
	DECLARE_CLASS(AMainCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Assignment"), NO_API) \
	DECLARE_SERIALIZER(AMainCharacter)


#define Assignment_Source_Assignment_MainCharacter_h_31_INCLASS \
private: \
	static void StaticRegisterNativesAMainCharacter(); \
	friend struct Z_Construct_UClass_AMainCharacter_Statics; \
public: \
	DECLARE_CLASS(AMainCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Assignment"), NO_API) \
	DECLARE_SERIALIZER(AMainCharacter)


#define Assignment_Source_Assignment_MainCharacter_h_31_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AMainCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AMainCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMainCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMainCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AMainCharacter(AMainCharacter&&); \
	NO_API AMainCharacter(const AMainCharacter&); \
public:


#define Assignment_Source_Assignment_MainCharacter_h_31_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AMainCharacter(AMainCharacter&&); \
	NO_API AMainCharacter(const AMainCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMainCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMainCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMainCharacter)


#define Assignment_Source_Assignment_MainCharacter_h_31_PRIVATE_PROPERTY_OFFSET
#define Assignment_Source_Assignment_MainCharacter_h_28_PROLOG
#define Assignment_Source_Assignment_MainCharacter_h_31_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Assignment_Source_Assignment_MainCharacter_h_31_PRIVATE_PROPERTY_OFFSET \
	Assignment_Source_Assignment_MainCharacter_h_31_SPARSE_DATA \
	Assignment_Source_Assignment_MainCharacter_h_31_RPC_WRAPPERS \
	Assignment_Source_Assignment_MainCharacter_h_31_INCLASS \
	Assignment_Source_Assignment_MainCharacter_h_31_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Assignment_Source_Assignment_MainCharacter_h_31_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Assignment_Source_Assignment_MainCharacter_h_31_PRIVATE_PROPERTY_OFFSET \
	Assignment_Source_Assignment_MainCharacter_h_31_SPARSE_DATA \
	Assignment_Source_Assignment_MainCharacter_h_31_RPC_WRAPPERS_NO_PURE_DECLS \
	Assignment_Source_Assignment_MainCharacter_h_31_INCLASS_NO_PURE_DECLS \
	Assignment_Source_Assignment_MainCharacter_h_31_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ASSIGNMENT_API UClass* StaticClass<class AMainCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Assignment_Source_Assignment_MainCharacter_h


#define FOREACH_ENUM_ESTAMINASTATUS(op) \
	op(EStaminaStatus::ESS_Normal) \
	op(EStaminaStatus::ESS_BeloMinimum) \
	op(EStaminaStatus::ESS_Exhausted) \
	op(EStaminaStatus::ESS_ExhaustedRecovering) \
	op(EStaminaStatus::ESS_Max) 

enum class EStaminaStatus : uint8;
template<> ASSIGNMENT_API UEnum* StaticEnum<EStaminaStatus>();

#define FOREACH_ENUM_EMOVEMENTSTATUS(op) \
	op(EMovementStatus::EMS_Normal) \
	op(EMovementStatus::EMS_Sprinting) \
	op(EMovementStatus::EMS_Dead) 

enum class EMovementStatus : uint8;
template<> ASSIGNMENT_API UEnum* StaticEnum<EMovementStatus>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
