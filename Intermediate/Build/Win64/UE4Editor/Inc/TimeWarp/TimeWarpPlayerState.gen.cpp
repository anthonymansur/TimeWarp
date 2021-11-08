// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TimeWarp/TimeWarpPlayerState.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTimeWarpPlayerState() {}
// Cross Module References
	TIMEWARP_API UClass* Z_Construct_UClass_ATimeWarpPlayerState_NoRegister();
	TIMEWARP_API UClass* Z_Construct_UClass_ATimeWarpPlayerState();
	ENGINE_API UClass* Z_Construct_UClass_APlayerState();
	UPackage* Z_Construct_UPackage__Script_TimeWarp();
// End Cross Module References
	void ATimeWarpPlayerState::StaticRegisterNativesATimeWarpPlayerState()
	{
	}
	UClass* Z_Construct_UClass_ATimeWarpPlayerState_NoRegister()
	{
		return ATimeWarpPlayerState::StaticClass();
	}
	struct Z_Construct_UClass_ATimeWarpPlayerState_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATimeWarpPlayerState_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerState,
		(UObject* (*)())Z_Construct_UPackage__Script_TimeWarp,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATimeWarpPlayerState_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "TimeWarpPlayerState.h" },
		{ "ModuleRelativePath", "TimeWarpPlayerState.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATimeWarpPlayerState_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATimeWarpPlayerState>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ATimeWarpPlayerState_Statics::ClassParams = {
		&ATimeWarpPlayerState::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_ATimeWarpPlayerState_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATimeWarpPlayerState_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATimeWarpPlayerState()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ATimeWarpPlayerState_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ATimeWarpPlayerState, 3404647670);
	template<> TIMEWARP_API UClass* StaticClass<ATimeWarpPlayerState>()
	{
		return ATimeWarpPlayerState::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ATimeWarpPlayerState(Z_Construct_UClass_ATimeWarpPlayerState, &ATimeWarpPlayerState::StaticClass, TEXT("/Script/TimeWarp"), TEXT("ATimeWarpPlayerState"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATimeWarpPlayerState);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
