// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TimeWarp/TimeWarpGameInstance.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTimeWarpGameInstance() {}
// Cross Module References
	TIMEWARP_API UClass* Z_Construct_UClass_UTimeWarpGameInstance_NoRegister();
	TIMEWARP_API UClass* Z_Construct_UClass_UTimeWarpGameInstance();
	ENGINE_API UClass* Z_Construct_UClass_UGameInstance();
	UPackage* Z_Construct_UPackage__Script_TimeWarp();
// End Cross Module References
	void UTimeWarpGameInstance::StaticRegisterNativesUTimeWarpGameInstance()
	{
	}
	UClass* Z_Construct_UClass_UTimeWarpGameInstance_NoRegister()
	{
		return UTimeWarpGameInstance::StaticClass();
	}
	struct Z_Construct_UClass_UTimeWarpGameInstance_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UTimeWarpGameInstance_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UGameInstance,
		(UObject* (*)())Z_Construct_UPackage__Script_TimeWarp,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTimeWarpGameInstance_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "TimeWarpGameInstance.h" },
		{ "ModuleRelativePath", "TimeWarpGameInstance.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UTimeWarpGameInstance_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTimeWarpGameInstance>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UTimeWarpGameInstance_Statics::ClassParams = {
		&UTimeWarpGameInstance::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A8u,
		METADATA_PARAMS(Z_Construct_UClass_UTimeWarpGameInstance_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UTimeWarpGameInstance_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UTimeWarpGameInstance()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UTimeWarpGameInstance_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UTimeWarpGameInstance, 3873135354);
	template<> TIMEWARP_API UClass* StaticClass<UTimeWarpGameInstance>()
	{
		return UTimeWarpGameInstance::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UTimeWarpGameInstance(Z_Construct_UClass_UTimeWarpGameInstance, &UTimeWarpGameInstance::StaticClass, TEXT("/Script/TimeWarp"), TEXT("UTimeWarpGameInstance"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UTimeWarpGameInstance);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
