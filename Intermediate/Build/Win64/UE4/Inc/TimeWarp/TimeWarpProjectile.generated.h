// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FVector;
struct FHitResult;
#ifdef TIMEWARP_TimeWarpProjectile_generated_h
#error "TimeWarpProjectile.generated.h already included, missing '#pragma once' in TimeWarpProjectile.h"
#endif
#define TIMEWARP_TimeWarpProjectile_generated_h

#define TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_SPARSE_DATA
#define TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnHit);


#define TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnHit);


#define TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATimeWarpProjectile(); \
	friend struct Z_Construct_UClass_ATimeWarpProjectile_Statics; \
public: \
	DECLARE_CLASS(ATimeWarpProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TimeWarp"), NO_API) \
	DECLARE_SERIALIZER(ATimeWarpProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_INCLASS \
private: \
	static void StaticRegisterNativesATimeWarpProjectile(); \
	friend struct Z_Construct_UClass_ATimeWarpProjectile_Statics; \
public: \
	DECLARE_CLASS(ATimeWarpProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TimeWarp"), NO_API) \
	DECLARE_SERIALIZER(ATimeWarpProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATimeWarpProjectile(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATimeWarpProjectile) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATimeWarpProjectile); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATimeWarpProjectile); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATimeWarpProjectile(ATimeWarpProjectile&&); \
	NO_API ATimeWarpProjectile(const ATimeWarpProjectile&); \
public:


#define TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATimeWarpProjectile(ATimeWarpProjectile&&); \
	NO_API ATimeWarpProjectile(const ATimeWarpProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATimeWarpProjectile); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATimeWarpProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ATimeWarpProjectile)


#define TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CollisionComp() { return STRUCT_OFFSET(ATimeWarpProjectile, CollisionComp); } \
	FORCEINLINE static uint32 __PPO__ProjectileMovement() { return STRUCT_OFFSET(ATimeWarpProjectile, ProjectileMovement); }


#define TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_10_PROLOG
#define TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_PRIVATE_PROPERTY_OFFSET \
	TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_SPARSE_DATA \
	TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_RPC_WRAPPERS \
	TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_INCLASS \
	TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_PRIVATE_PROPERTY_OFFSET \
	TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_SPARSE_DATA \
	TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_INCLASS_NO_PURE_DECLS \
	TimeWarp_Source_TimeWarp_TimeWarpProjectile_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> TIMEWARP_API UClass* StaticClass<class ATimeWarpProjectile>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID TimeWarp_Source_TimeWarp_TimeWarpProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
