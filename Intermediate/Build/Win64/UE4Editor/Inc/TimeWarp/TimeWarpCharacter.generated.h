// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FDamageEvent;
class AController;
class AActor;
#ifdef TIMEWARP_TimeWarpCharacter_generated_h
#error "TimeWarpCharacter.generated.h already included, missing '#pragma once' in TimeWarpCharacter.h"
#endif
#define TIMEWARP_TimeWarpCharacter_generated_h

#define TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_SPARSE_DATA
#define TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_RPC_WRAPPERS \
	virtual void HandleFire_Implementation(); \
 \
	DECLARE_FUNCTION(execTakeDamage); \
	DECLARE_FUNCTION(execSetCurrentAmmo); \
	DECLARE_FUNCTION(execGetCurrentAmmo); \
	DECLARE_FUNCTION(execSetCurrentHealth); \
	DECLARE_FUNCTION(execGetCurrentHealth); \
	DECLARE_FUNCTION(execGetMaxHealth); \
	DECLARE_FUNCTION(execHandleFire); \
	DECLARE_FUNCTION(execOnRep_CurrentHealth);


#define TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void HandleFire_Implementation(); \
 \
	DECLARE_FUNCTION(execTakeDamage); \
	DECLARE_FUNCTION(execSetCurrentAmmo); \
	DECLARE_FUNCTION(execGetCurrentAmmo); \
	DECLARE_FUNCTION(execSetCurrentHealth); \
	DECLARE_FUNCTION(execGetCurrentHealth); \
	DECLARE_FUNCTION(execGetMaxHealth); \
	DECLARE_FUNCTION(execHandleFire); \
	DECLARE_FUNCTION(execOnRep_CurrentHealth);


#define TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_EVENT_PARMS
#define TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_CALLBACK_WRAPPERS
#define TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATimeWarpCharacter(); \
	friend struct Z_Construct_UClass_ATimeWarpCharacter_Statics; \
public: \
	DECLARE_CLASS(ATimeWarpCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TimeWarp"), NO_API) \
	DECLARE_SERIALIZER(ATimeWarpCharacter) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		CurrentHealth=NETFIELD_REP_START, \
		bTranslationEnabled, \
		bRotationEnabled, \
		bCanShoot, \
		NETFIELD_REP_END=bCanShoot	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_INCLASS \
private: \
	static void StaticRegisterNativesATimeWarpCharacter(); \
	friend struct Z_Construct_UClass_ATimeWarpCharacter_Statics; \
public: \
	DECLARE_CLASS(ATimeWarpCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TimeWarp"), NO_API) \
	DECLARE_SERIALIZER(ATimeWarpCharacter) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		CurrentHealth=NETFIELD_REP_START, \
		bTranslationEnabled, \
		bRotationEnabled, \
		bCanShoot, \
		NETFIELD_REP_END=bCanShoot	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATimeWarpCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATimeWarpCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATimeWarpCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATimeWarpCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATimeWarpCharacter(ATimeWarpCharacter&&); \
	NO_API ATimeWarpCharacter(const ATimeWarpCharacter&); \
public:


#define TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATimeWarpCharacter(ATimeWarpCharacter&&); \
	NO_API ATimeWarpCharacter(const ATimeWarpCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATimeWarpCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATimeWarpCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ATimeWarpCharacter)


#define TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__Mesh1P() { return STRUCT_OFFSET(ATimeWarpCharacter, Mesh1P); } \
	FORCEINLINE static uint32 __PPO__Mesh2P() { return STRUCT_OFFSET(ATimeWarpCharacter, Mesh2P); } \
	FORCEINLINE static uint32 __PPO__FP_Gun() { return STRUCT_OFFSET(ATimeWarpCharacter, FP_Gun); } \
	FORCEINLINE static uint32 __PPO__FP_Gun2P() { return STRUCT_OFFSET(ATimeWarpCharacter, FP_Gun2P); } \
	FORCEINLINE static uint32 __PPO__FP_MuzzleLocation() { return STRUCT_OFFSET(ATimeWarpCharacter, FP_MuzzleLocation); } \
	FORCEINLINE static uint32 __PPO__VR_Gun() { return STRUCT_OFFSET(ATimeWarpCharacter, VR_Gun); } \
	FORCEINLINE static uint32 __PPO__VR_MuzzleLocation() { return STRUCT_OFFSET(ATimeWarpCharacter, VR_MuzzleLocation); } \
	FORCEINLINE static uint32 __PPO__FirstPersonCameraComponent() { return STRUCT_OFFSET(ATimeWarpCharacter, FirstPersonCameraComponent); } \
	FORCEINLINE static uint32 __PPO__R_MotionController() { return STRUCT_OFFSET(ATimeWarpCharacter, R_MotionController); } \
	FORCEINLINE static uint32 __PPO__L_MotionController() { return STRUCT_OFFSET(ATimeWarpCharacter, L_MotionController); } \
	FORCEINLINE static uint32 __PPO__MaxHealth() { return STRUCT_OFFSET(ATimeWarpCharacter, MaxHealth); } \
	FORCEINLINE static uint32 __PPO__CurrentHealth() { return STRUCT_OFFSET(ATimeWarpCharacter, CurrentHealth); } \
	FORCEINLINE static uint32 __PPO__bTranslationEnabled() { return STRUCT_OFFSET(ATimeWarpCharacter, bTranslationEnabled); } \
	FORCEINLINE static uint32 __PPO__bRotationEnabled() { return STRUCT_OFFSET(ATimeWarpCharacter, bRotationEnabled); } \
	FORCEINLINE static uint32 __PPO__bCanShoot() { return STRUCT_OFFSET(ATimeWarpCharacter, bCanShoot); }


#define TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_11_PROLOG \
	TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_EVENT_PARMS


#define TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_SPARSE_DATA \
	TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_RPC_WRAPPERS \
	TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_CALLBACK_WRAPPERS \
	TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_INCLASS \
	TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_SPARSE_DATA \
	TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_CALLBACK_WRAPPERS \
	TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_INCLASS_NO_PURE_DECLS \
	TimeWarp_Source_TimeWarp_TimeWarpCharacter_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> TIMEWARP_API UClass* StaticClass<class ATimeWarpCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID TimeWarp_Source_TimeWarp_TimeWarpCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
