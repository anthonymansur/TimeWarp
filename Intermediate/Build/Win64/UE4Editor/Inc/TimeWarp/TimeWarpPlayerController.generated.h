// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FRotator;
#ifdef TIMEWARP_TimeWarpPlayerController_generated_h
#error "TimeWarpPlayerController.generated.h already included, missing '#pragma once' in TimeWarpPlayerController.h"
#endif
#define TIMEWARP_TimeWarpPlayerController_generated_h

#define TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_SPARSE_DATA
#define TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execForceControlRotation);


#define TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execForceControlRotation);


#define TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATimeWarpPlayerController(); \
	friend struct Z_Construct_UClass_ATimeWarpPlayerController_Statics; \
public: \
	DECLARE_CLASS(ATimeWarpPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TimeWarp"), NO_API) \
	DECLARE_SERIALIZER(ATimeWarpPlayerController)


#define TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_INCLASS \
private: \
	static void StaticRegisterNativesATimeWarpPlayerController(); \
	friend struct Z_Construct_UClass_ATimeWarpPlayerController_Statics; \
public: \
	DECLARE_CLASS(ATimeWarpPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TimeWarp"), NO_API) \
	DECLARE_SERIALIZER(ATimeWarpPlayerController)


#define TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATimeWarpPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATimeWarpPlayerController) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATimeWarpPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATimeWarpPlayerController); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATimeWarpPlayerController(ATimeWarpPlayerController&&); \
	NO_API ATimeWarpPlayerController(const ATimeWarpPlayerController&); \
public:


#define TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATimeWarpPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATimeWarpPlayerController(ATimeWarpPlayerController&&); \
	NO_API ATimeWarpPlayerController(const ATimeWarpPlayerController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATimeWarpPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATimeWarpPlayerController); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATimeWarpPlayerController)


#define TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_PRIVATE_PROPERTY_OFFSET
#define TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_12_PROLOG
#define TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_PRIVATE_PROPERTY_OFFSET \
	TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_SPARSE_DATA \
	TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_RPC_WRAPPERS \
	TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_INCLASS \
	TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_PRIVATE_PROPERTY_OFFSET \
	TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_SPARSE_DATA \
	TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_INCLASS_NO_PURE_DECLS \
	TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> TIMEWARP_API UClass* StaticClass<class ATimeWarpPlayerController>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID TimeWarp_Source_TimeWarp_TimeWarpPlayerController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
