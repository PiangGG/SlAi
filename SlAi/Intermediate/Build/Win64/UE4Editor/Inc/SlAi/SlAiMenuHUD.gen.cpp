// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SlAi/Public/UI/HUD/SlAiMenuHUD.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSlAiMenuHUD() {}
// Cross Module References
	SLAI_API UClass* Z_Construct_UClass_ASlAiMenuHUD_NoRegister();
	SLAI_API UClass* Z_Construct_UClass_ASlAiMenuHUD();
	ENGINE_API UClass* Z_Construct_UClass_AHUD();
	UPackage* Z_Construct_UPackage__Script_SlAi();
// End Cross Module References
	void ASlAiMenuHUD::StaticRegisterNativesASlAiMenuHUD()
	{
	}
	UClass* Z_Construct_UClass_ASlAiMenuHUD_NoRegister()
	{
		return ASlAiMenuHUD::StaticClass();
	}
	struct Z_Construct_UClass_ASlAiMenuHUD_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASlAiMenuHUD_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AHUD,
		(UObject* (*)())Z_Construct_UPackage__Script_SlAi,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASlAiMenuHUD_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Rendering Actor Input Replication" },
		{ "IncludePath", "UI/HUD/SlAiMenuHUD.h" },
		{ "ModuleRelativePath", "Public/UI/HUD/SlAiMenuHUD.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASlAiMenuHUD_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASlAiMenuHUD>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ASlAiMenuHUD_Statics::ClassParams = {
		&ASlAiMenuHUD::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ASlAiMenuHUD_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ASlAiMenuHUD_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASlAiMenuHUD()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ASlAiMenuHUD_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASlAiMenuHUD, 4182005813);
	template<> SLAI_API UClass* StaticClass<ASlAiMenuHUD>()
	{
		return ASlAiMenuHUD::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASlAiMenuHUD(Z_Construct_UClass_ASlAiMenuHUD, &ASlAiMenuHUD::StaticClass, TEXT("/Script/SlAi"), TEXT("ASlAiMenuHUD"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASlAiMenuHUD);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
