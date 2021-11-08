// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TimeWarp/TimeWarpGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTimeWarpGameMode() {}
// Cross Module References
	TIMEWARP_API UClass* Z_Construct_UClass_ATimeWarpGameMode_NoRegister();
	TIMEWARP_API UClass* Z_Construct_UClass_ATimeWarpGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameMode();
	UPackage* Z_Construct_UPackage__Script_TimeWarp();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(ATimeWarpGameMode::execRespawnPlayerEvent)
	{
		P_GET_OBJECT(APlayerController,Z_Param_NewPlayer);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->RespawnPlayerEvent_Implementation(Z_Param_NewPlayer);
		P_NATIVE_END;
	}
	static FName NAME_ATimeWarpGameMode_RespawnPlayerEvent = FName(TEXT("RespawnPlayerEvent"));
	void ATimeWarpGameMode::RespawnPlayerEvent(APlayerController* NewPlayer)
	{
		TimeWarpGameMode_eventRespawnPlayerEvent_Parms Parms;
		Parms.NewPlayer=NewPlayer;
		ProcessEvent(FindFunctionChecked(NAME_ATimeWarpGameMode_RespawnPlayerEvent),&Parms);
	}
	void ATimeWarpGameMode::StaticRegisterNativesATimeWarpGameMode()
	{
		UClass* Class = ATimeWarpGameMode::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "RespawnPlayerEvent", &ATimeWarpGameMode::execRespawnPlayerEvent },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ATimeWarpGameMode_RespawnPlayerEvent_Statics
	{
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_NewPlayer;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ATimeWarpGameMode_RespawnPlayerEvent_Statics::NewProp_NewPlayer = { "NewPlayer", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(TimeWarpGameMode_eventRespawnPlayerEvent_Parms, NewPlayer), Z_Construct_UClass_APlayerController_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATimeWarpGameMode_RespawnPlayerEvent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATimeWarpGameMode_RespawnPlayerEvent_Statics::NewProp_NewPlayer,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATimeWarpGameMode_RespawnPlayerEvent_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** Server function for spawning projectiles. */" },
		{ "ModuleRelativePath", "TimeWarpGameMode.h" },
		{ "ToolTip", "Server function for spawning projectiles." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATimeWarpGameMode_RespawnPlayerEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATimeWarpGameMode, nullptr, "RespawnPlayerEvent", nullptr, nullptr, sizeof(TimeWarpGameMode_eventRespawnPlayerEvent_Parms), Z_Construct_UFunction_ATimeWarpGameMode_RespawnPlayerEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATimeWarpGameMode_RespawnPlayerEvent_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00220CC0, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATimeWarpGameMode_RespawnPlayerEvent_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATimeWarpGameMode_RespawnPlayerEvent_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATimeWarpGameMode_RespawnPlayerEvent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATimeWarpGameMode_RespawnPlayerEvent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ATimeWarpGameMode_NoRegister()
	{
		return ATimeWarpGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ATimeWarpGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATimeWarpGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameMode,
		(UObject* (*)())Z_Construct_UPackage__Script_TimeWarp,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ATimeWarpGameMode_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ATimeWarpGameMode_RespawnPlayerEvent, "RespawnPlayerEvent" }, // 111548077
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATimeWarpGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "TimeWarpGameMode.h" },
		{ "ModuleRelativePath", "TimeWarpGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATimeWarpGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATimeWarpGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ATimeWarpGameMode_Statics::ClassParams = {
		&ATimeWarpGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_ATimeWarpGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATimeWarpGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATimeWarpGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ATimeWarpGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ATimeWarpGameMode, 3133053305);
	template<> TIMEWARP_API UClass* StaticClass<ATimeWarpGameMode>()
	{
		return ATimeWarpGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ATimeWarpGameMode(Z_Construct_UClass_ATimeWarpGameMode, &ATimeWarpGameMode::StaticClass, TEXT("/Script/TimeWarp"), TEXT("ATimeWarpGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATimeWarpGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
