// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ASSIGNMENT_Collider_generated_h
#error "Collider.generated.h already included, missing '#pragma once' in Collider.h"
#endif
#define ASSIGNMENT_Collider_generated_h

#define Assignment_Source_Assignment_Collider_h_12_SPARSE_DATA
#define Assignment_Source_Assignment_Collider_h_12_RPC_WRAPPERS
#define Assignment_Source_Assignment_Collider_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define Assignment_Source_Assignment_Collider_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesACollider(); \
	friend struct Z_Construct_UClass_ACollider_Statics; \
public: \
	DECLARE_CLASS(ACollider, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Assignment"), NO_API) \
	DECLARE_SERIALIZER(ACollider)


#define Assignment_Source_Assignment_Collider_h_12_INCLASS \
private: \
	static void StaticRegisterNativesACollider(); \
	friend struct Z_Construct_UClass_ACollider_Statics; \
public: \
	DECLARE_CLASS(ACollider, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Assignment"), NO_API) \
	DECLARE_SERIALIZER(ACollider)


#define Assignment_Source_Assignment_Collider_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ACollider(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ACollider) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACollider); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACollider); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ACollider(ACollider&&); \
	NO_API ACollider(const ACollider&); \
public:


#define Assignment_Source_Assignment_Collider_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ACollider(ACollider&&); \
	NO_API ACollider(const ACollider&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACollider); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACollider); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ACollider)


#define Assignment_Source_Assignment_Collider_h_12_PRIVATE_PROPERTY_OFFSET
#define Assignment_Source_Assignment_Collider_h_9_PROLOG
#define Assignment_Source_Assignment_Collider_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Assignment_Source_Assignment_Collider_h_12_PRIVATE_PROPERTY_OFFSET \
	Assignment_Source_Assignment_Collider_h_12_SPARSE_DATA \
	Assignment_Source_Assignment_Collider_h_12_RPC_WRAPPERS \
	Assignment_Source_Assignment_Collider_h_12_INCLASS \
	Assignment_Source_Assignment_Collider_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Assignment_Source_Assignment_Collider_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Assignment_Source_Assignment_Collider_h_12_PRIVATE_PROPERTY_OFFSET \
	Assignment_Source_Assignment_Collider_h_12_SPARSE_DATA \
	Assignment_Source_Assignment_Collider_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	Assignment_Source_Assignment_Collider_h_12_INCLASS_NO_PURE_DECLS \
	Assignment_Source_Assignment_Collider_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ASSIGNMENT_API UClass* StaticClass<class ACollider>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Assignment_Source_Assignment_Collider_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
