// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SlAi/Public/UI/Style/SlAiMenuWidgetStyle.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSlAiMenuWidgetStyle() {}
// Cross Module References
	SLAI_API UScriptStruct* Z_Construct_UScriptStruct_FSlAiMenuStyle();
	UPackage* Z_Construct_UPackage__Script_SlAi();
	SLATECORE_API UScriptStruct* Z_Construct_UScriptStruct_FSlateWidgetStyle();
	SLATECORE_API UScriptStruct* Z_Construct_UScriptStruct_FSlateBrush();
	SLAI_API UClass* Z_Construct_UClass_USlAiMenuWidgetStyle_NoRegister();
	SLAI_API UClass* Z_Construct_UClass_USlAiMenuWidgetStyle();
	SLATECORE_API UClass* Z_Construct_UClass_USlateWidgetStyleContainerBase();
// End Cross Module References

static_assert(std::is_polymorphic<FSlAiMenuStyle>() == std::is_polymorphic<FSlateWidgetStyle>(), "USTRUCT FSlAiMenuStyle cannot be polymorphic unless super FSlateWidgetStyle is polymorphic");

class UScriptStruct* FSlAiMenuStyle::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern SLAI_API uint32 Get_Z_Construct_UScriptStruct_FSlAiMenuStyle_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FSlAiMenuStyle, Z_Construct_UPackage__Script_SlAi(), TEXT("SlAiMenuStyle"), sizeof(FSlAiMenuStyle), Get_Z_Construct_UScriptStruct_FSlAiMenuStyle_Hash());
	}
	return Singleton;
}
template<> SLAI_API UScriptStruct* StaticStruct<FSlAiMenuStyle>()
{
	return FSlAiMenuStyle::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FSlAiMenuStyle(FSlAiMenuStyle::StaticStruct, TEXT("/Script/SlAi"), TEXT("SlAiMenuStyle"), false, nullptr, nullptr);
static struct FScriptStruct_SlAi_StaticRegisterNativesFSlAiMenuStyle
{
	FScriptStruct_SlAi_StaticRegisterNativesFSlAiMenuStyle()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("SlAiMenuStyle")),new UScriptStruct::TCppStructOps<FSlAiMenuStyle>);
	}
} ScriptStruct_SlAi_StaticRegisterNativesFSlAiMenuStyle;
	struct Z_Construct_UScriptStruct_FSlAiMenuStyle_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MenuHUDBackgroundBrush_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MenuHUDBackgroundBrush;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSlAiMenuStyle_Statics::Struct_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "ModuleRelativePath", "Public/UI/Style/SlAiMenuWidgetStyle.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FSlAiMenuStyle_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSlAiMenuStyle>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSlAiMenuStyle_Statics::NewProp_MenuHUDBackgroundBrush_MetaData[] = {
		{ "Category", "MenuHUD" },
		{ "ModuleRelativePath", "Public/UI/Style/SlAiMenuWidgetStyle.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FSlAiMenuStyle_Statics::NewProp_MenuHUDBackgroundBrush = { "MenuHUDBackgroundBrush", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSlAiMenuStyle, MenuHUDBackgroundBrush), Z_Construct_UScriptStruct_FSlateBrush, METADATA_PARAMS(Z_Construct_UScriptStruct_FSlAiMenuStyle_Statics::NewProp_MenuHUDBackgroundBrush_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSlAiMenuStyle_Statics::NewProp_MenuHUDBackgroundBrush_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSlAiMenuStyle_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSlAiMenuStyle_Statics::NewProp_MenuHUDBackgroundBrush,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSlAiMenuStyle_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_SlAi,
		Z_Construct_UScriptStruct_FSlateWidgetStyle,
		&NewStructOps,
		"SlAiMenuStyle",
		sizeof(FSlAiMenuStyle),
		alignof(FSlAiMenuStyle),
		Z_Construct_UScriptStruct_FSlAiMenuStyle_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSlAiMenuStyle_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FSlAiMenuStyle_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSlAiMenuStyle_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FSlAiMenuStyle()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FSlAiMenuStyle_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_SlAi();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("SlAiMenuStyle"), sizeof(FSlAiMenuStyle), Get_Z_Construct_UScriptStruct_FSlAiMenuStyle_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FSlAiMenuStyle_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FSlAiMenuStyle_Hash() { return 248307644U; }
	void USlAiMenuWidgetStyle::StaticRegisterNativesUSlAiMenuWidgetStyle()
	{
	}
	UClass* Z_Construct_UClass_USlAiMenuWidgetStyle_NoRegister()
	{
		return USlAiMenuWidgetStyle::StaticClass();
	}
	struct Z_Construct_UClass_USlAiMenuWidgetStyle_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WidgetStyle_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_WidgetStyle;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USlAiMenuWidgetStyle_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USlateWidgetStyleContainerBase,
		(UObject* (*)())Z_Construct_UPackage__Script_SlAi,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USlAiMenuWidgetStyle_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n */" },
		{ "HideCategories", "Object Object" },
		{ "IncludePath", "UI/Style/SlAiMenuWidgetStyle.h" },
		{ "ModuleRelativePath", "Public/UI/Style/SlAiMenuWidgetStyle.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USlAiMenuWidgetStyle_Statics::NewProp_WidgetStyle_MetaData[] = {
		{ "Category", "Appearance" },
		{ "Comment", "/** The actual data describing the widget appearance. */" },
		{ "ModuleRelativePath", "Public/UI/Style/SlAiMenuWidgetStyle.h" },
		{ "ShowOnlyInnerProperties", "" },
		{ "ToolTip", "The actual data describing the widget appearance." },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_USlAiMenuWidgetStyle_Statics::NewProp_WidgetStyle = { "WidgetStyle", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USlAiMenuWidgetStyle, WidgetStyle), Z_Construct_UScriptStruct_FSlAiMenuStyle, METADATA_PARAMS(Z_Construct_UClass_USlAiMenuWidgetStyle_Statics::NewProp_WidgetStyle_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USlAiMenuWidgetStyle_Statics::NewProp_WidgetStyle_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USlAiMenuWidgetStyle_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USlAiMenuWidgetStyle_Statics::NewProp_WidgetStyle,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_USlAiMenuWidgetStyle_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USlAiMenuWidgetStyle>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USlAiMenuWidgetStyle_Statics::ClassParams = {
		&USlAiMenuWidgetStyle::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_USlAiMenuWidgetStyle_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_USlAiMenuWidgetStyle_Statics::PropPointers),
		0,
		0x000800A0u,
		METADATA_PARAMS(Z_Construct_UClass_USlAiMenuWidgetStyle_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USlAiMenuWidgetStyle_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USlAiMenuWidgetStyle()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USlAiMenuWidgetStyle_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USlAiMenuWidgetStyle, 4106118911);
	template<> SLAI_API UClass* StaticClass<USlAiMenuWidgetStyle>()
	{
		return USlAiMenuWidgetStyle::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USlAiMenuWidgetStyle(Z_Construct_UClass_USlAiMenuWidgetStyle, &USlAiMenuWidgetStyle::StaticClass, TEXT("/Script/SlAi"), TEXT("USlAiMenuWidgetStyle"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USlAiMenuWidgetStyle);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
