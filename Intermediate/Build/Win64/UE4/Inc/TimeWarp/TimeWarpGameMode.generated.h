// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class APlayerController;
#ifdef TIMEWARP_TimeWarpGameMode_generated_h
#error "TimeWarpGameMode.generated.h already included, missing '#pragma once' in TimeWarpGameMode.h"
#endif
#define TIMEWARP_TimeWarpGameMode_generated_h

#define TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_SPARSE_DATA
#define TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_RPC_WRAPPERS \
	virtual void RespawnPlayerEvent_Implementation(APlayerController* NewPlayer); \
 \
	DECLARE_FUNCTION(execRespawnPlayerEvent);


#define TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void RespawnPlayerEvent_Implementation(APlayerController* NewPlayer); \
 \
	DECLARE_FUNCTION(execRespawnPlayerEvent);


#define TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_EVENT_PARMS \
	struct TimeWarpGameMode_eventRespawnPlayerEvent_Parms \
	{ \
		APlayerController* NewPlayer; \
	};


#define TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_CALLBACK_WRAPPERS
#define TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATimeWarpGameMode(); \
	friend struct Z_Construct_UClass_ATimeWarpGameMode_Statics; \
public: \
	DECLARE_CLASS(ATimeWarpGameMode, AGameMode, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/TimeWarp"), TIMEWARP_API) \
	DECLARE_SERIALIZER(ATimeWarpGameMode)


#define TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_INCLASS \
private: \
	static void StaticRegisterNativesATimeWarpGameMode(); \
	friend struct Z_Construct_UClass_ATimeWarpGameMode_Statics; \
public: \
	DECLARE_CLASS(ATimeWarpGameMode, AGameMode, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/TimeWarp"), TIMEWARP_API) \
	DECLARE_SERIALIZER(ATimeWarpGameMode)


#define TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	TIMEWARP_API ATimeWarpGameMode(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATimeWarpGameMode) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(TIMEWARP_API, ATimeWarpGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATimeWarpGameMode); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	TIMEWARP_API ATimeWarpGameMode(ATimeWarpGameMode&&); \
	TIMEWARP_API ATimeWarpGameMode(const ATimeWarpGameMode&); \
public:


#define TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	TIMEWARP_API ATimeWarpGameMode(ATimeWarpGameMode&&); \
	TIMEWARP_API ATimeWarpGameMode(const ATimeWarpGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(TIMEWARP_API, ATimeWarpGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATimeWarpGameMode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ATimeWarpGameMode)


#define TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_PRIVATE_PROPERTY_OFFSET
#define TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_13_PROLOG \
	TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_EVENT_PARMS


#define TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_PRIVATE_PROPERTY_OFFSET \
	TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_SPARSE_DATA \
	TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_RPC_WRAPPERS \
	TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_CALLBACK_WRAPPERS \
	TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_INCLASS \
	TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_PRIVATE_PROPERTY_OFFSET \
	TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_SPARSE_DATA \
	TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_CALLBACK_WRAPPERS \
	TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_INCLASS_NO_PURE_DECLS \
	TimeWarp_Source_TimeWarp_TimeWarpGameMode_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> TIMEWARP_API UClass* StaticClass<class ATimeWarpGameMode>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID TimeWarp_Source_TimeWarp_TimeWarpGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
