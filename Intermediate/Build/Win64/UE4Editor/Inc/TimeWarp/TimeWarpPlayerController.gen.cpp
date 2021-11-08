// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TimeWarp/TimeWarpPlayerController.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTimeWarpPlayerController() {}
// Cross Module References
	TIMEWARP_API UClass* Z_Construct_UClass_ATimeWarpPlayerController_NoRegister();
	TIMEWARP_API UClass* Z_Construct_UClass_ATimeWarpPlayerController();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	UPackage* Z_Construct_UPackage__Script_TimeWarp();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
// End Cross Module References
	DEFINE_FUNCTION(ATimeWarpPlayerController::execForceControlRotation)
	{
		P_GET_STRUCT_REF(FRotator,Z_Param_Out_NewRotation);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ForceControlRotation(Z_Param_Out_NewRotation);
		P_NATIVE_END;
	}
	void ATimeWarpPlayerController::StaticRegisterNativesATimeWarpPlayerController()
	{
		UClass* Class = ATimeWarpPlayerController::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "ForceControlRotation", &ATimeWarpPlayerController::execForceControlRotation },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ATimeWarpPlayerController_ForceControlRotation_Statics
	{
		struct TimeWarpPlayerController_eventForceControlRotation_Parms
		{
			FRotator NewRotation;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NewRotation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_NewRotation;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATimeWarpPlayerController_ForceControlRotation_Statics::NewProp_NewRotation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ATimeWarpPlayerController_ForceControlRotation_Statics::NewProp_NewRotation = { "NewRotation", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(TimeWarpPlayerController_eventForceControlRotation_Parms, NewRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(Z_Construct_UFunction_ATimeWarpPlayerController_ForceControlRotation_Statics::NewProp_NewRotation_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ATimeWarpPlayerController_ForceControlRotation_Statics::NewProp_NewRotation_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATimeWarpPlayerController_ForceControlRotation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATimeWarpPlayerController_ForceControlRotation_Statics::NewProp_NewRotation,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATimeWarpPlayerController_ForceControlRotation_Statics::Function_MetaDataParams[] = {
		{ "Category", "Pawn" },
		{ "ModuleRelativePath", "TimeWarpPlayerController.h" },
		{ "Tooltip", "Set the control rotation." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATimeWarpPlayerController_ForceControlRotation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATimeWarpPlayerController, nullptr, "ForceControlRotation", nullptr, nullptr, sizeof(TimeWarpPlayerController_eventForceControlRotation_Parms), Z_Construct_UFunction_ATimeWarpPlayerController_ForceControlRotation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATimeWarpPlayerController_ForceControlRotation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20404, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATimeWarpPlayerController_ForceControlRotation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATimeWarpPlayerController_ForceControlRotation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATimeWarpPlayerController_ForceControlRotation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATimeWarpPlayerController_ForceControlRotation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ATimeWarpPlayerController_NoRegister()
	{
		return ATimeWarpPlayerController::StaticClass();
	}
	struct Z_Construct_UClass_ATimeWarpPlayerController_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATimeWarpPlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_TimeWarp,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ATimeWarpPlayerController_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ATimeWarpPlayerController_ForceControlRotation, "ForceControlRotation" }, // 850414116
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATimeWarpPlayerController_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "TimeWarpPlayerController.h" },
		{ "ModuleRelativePath", "TimeWarpPlayerController.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATimeWarpPlayerController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATimeWarpPlayerController>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ATimeWarpPlayerController_Statics::ClassParams = {
		&ATimeWarpPlayerController::StaticClass,
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
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_ATimeWarpPlayerController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATimeWarpPlayerController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATimeWarpPlayerController()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ATimeWarpPlayerController_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ATimeWarpPlayerController, 1442681644);
	template<> TIMEWARP_API UClass* StaticClass<ATimeWarpPlayerController>()
	{
		return ATimeWarpPlayerController::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ATimeWarpPlayerController(Z_Construct_UClass_ATimeWarpPlayerController, &ATimeWarpPlayerController::StaticClass, TEXT("/Script/TimeWarp"), TEXT("ATimeWarpPlayerController"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATimeWarpPlayerController);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
