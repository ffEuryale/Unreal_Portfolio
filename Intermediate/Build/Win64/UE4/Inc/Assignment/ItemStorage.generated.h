// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ASSIGNMENT_ItemStorage_generated_h
#error "ItemStorage.generated.h already included, missing '#pragma once' in ItemStorage.h"
#endif
#define ASSIGNMENT_ItemStorage_generated_h

#define Assignment_Source_Assignment_ItemStorage_h_12_SPARSE_DATA
#define Assignment_Source_Assignment_ItemStorage_h_12_RPC_WRAPPERS
#define Assignment_Source_Assignment_ItemStorage_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define Assignment_Source_Assignment_ItemStorage_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAItemStorage(); \
	friend struct Z_Construct_UClass_AItemStorage_Statics; \
public: \
	DECLARE_CLASS(AItemStorage, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Assignment"), NO_API) \
	DECLARE_SERIALIZER(AItemStorage)


#define Assignment_Source_Assignment_ItemStorage_h_12_INCLASS \
private: \
	static void StaticRegisterNativesAItemStorage(); \
	friend struct Z_Construct_UClass_AItemStorage_Statics; \
public: \
	DECLARE_CLASS(AItemStorage, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Assignment"), NO_API) \
	DECLARE_SERIALIZER(AItemStorage)


#define Assignment_Source_Assignment_ItemStorage_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AItemStorage(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AItemStorage) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AItemStorage); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AItemStorage); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AItemStorage(AItemStorage&&); \
	NO_API AItemStorage(const AItemStorage&); \
public:


#define Assignment_Source_Assignment_ItemStorage_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AItemStorage(AItemStorage&&); \
	NO_API AItemStorage(const AItemStorage&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AItemStorage); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AItemStorage); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AItemStorage)


#define Assignment_Source_Assignment_ItemStorage_h_12_PRIVATE_PROPERTY_OFFSET
#define Assignment_Source_Assignment_ItemStorage_h_9_PROLOG
#define Assignment_Source_Assignment_ItemStorage_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Assignment_Source_Assignment_ItemStorage_h_12_PRIVATE_PROPERTY_OFFSET \
	Assignment_Source_Assignment_ItemStorage_h_12_SPARSE_DATA \
	Assignment_Source_Assignment_ItemStorage_h_12_RPC_WRAPPERS \
	Assignment_Source_Assignment_ItemStorage_h_12_INCLASS \
	Assignment_Source_Assignment_ItemStorage_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Assignment_Source_Assignment_ItemStorage_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Assignment_Source_Assignment_ItemStorage_h_12_PRIVATE_PROPERTY_OFFSET \
	Assignment_Source_Assignment_ItemStorage_h_12_SPARSE_DATA \
	Assignment_Source_Assignment_ItemStorage_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	Assignment_Source_Assignment_ItemStorage_h_12_INCLASS_NO_PURE_DECLS \
	Assignment_Source_Assignment_ItemStorage_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ASSIGNMENT_API UClass* StaticClass<class AItemStorage>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Assignment_Source_Assignment_ItemStorage_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
