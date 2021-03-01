// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AMainCharacter;
#ifdef ASSIGNMENT_Pickup_generated_h
#error "Pickup.generated.h already included, missing '#pragma once' in Pickup.h"
#endif
#define ASSIGNMENT_Pickup_generated_h

#define Assignment_Source_Assignment_Pickup_h_15_SPARSE_DATA
#define Assignment_Source_Assignment_Pickup_h_15_RPC_WRAPPERS
#define Assignment_Source_Assignment_Pickup_h_15_RPC_WRAPPERS_NO_PURE_DECLS
#define Assignment_Source_Assignment_Pickup_h_15_EVENT_PARMS \
	struct Pickup_eventOnPickupBP_Parms \
	{ \
		AMainCharacter* Target; \
	};


#define Assignment_Source_Assignment_Pickup_h_15_CALLBACK_WRAPPERS
#define Assignment_Source_Assignment_Pickup_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPickup(); \
	friend struct Z_Construct_UClass_APickup_Statics; \
public: \
	DECLARE_CLASS(APickup, AItem, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Assignment"), NO_API) \
	DECLARE_SERIALIZER(APickup)


#define Assignment_Source_Assignment_Pickup_h_15_INCLASS \
private: \
	static void StaticRegisterNativesAPickup(); \
	friend struct Z_Construct_UClass_APickup_Statics; \
public: \
	DECLARE_CLASS(APickup, AItem, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Assignment"), NO_API) \
	DECLARE_SERIALIZER(APickup)


#define Assignment_Source_Assignment_Pickup_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API APickup(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(APickup) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APickup); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APickup); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API APickup(APickup&&); \
	NO_API APickup(const APickup&); \
public:


#define Assignment_Source_Assignment_Pickup_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API APickup(APickup&&); \
	NO_API APickup(const APickup&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APickup); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APickup); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APickup)


#define Assignment_Source_Assignment_Pickup_h_15_PRIVATE_PROPERTY_OFFSET
#define Assignment_Source_Assignment_Pickup_h_12_PROLOG \
	Assignment_Source_Assignment_Pickup_h_15_EVENT_PARMS


#define Assignment_Source_Assignment_Pickup_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Assignment_Source_Assignment_Pickup_h_15_PRIVATE_PROPERTY_OFFSET \
	Assignment_Source_Assignment_Pickup_h_15_SPARSE_DATA \
	Assignment_Source_Assignment_Pickup_h_15_RPC_WRAPPERS \
	Assignment_Source_Assignment_Pickup_h_15_CALLBACK_WRAPPERS \
	Assignment_Source_Assignment_Pickup_h_15_INCLASS \
	Assignment_Source_Assignment_Pickup_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Assignment_Source_Assignment_Pickup_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Assignment_Source_Assignment_Pickup_h_15_PRIVATE_PROPERTY_OFFSET \
	Assignment_Source_Assignment_Pickup_h_15_SPARSE_DATA \
	Assignment_Source_Assignment_Pickup_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	Assignment_Source_Assignment_Pickup_h_15_CALLBACK_WRAPPERS \
	Assignment_Source_Assignment_Pickup_h_15_INCLASS_NO_PURE_DECLS \
	Assignment_Source_Assignment_Pickup_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ASSIGNMENT_API UClass* StaticClass<class APickup>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Assignment_Source_Assignment_Pickup_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
