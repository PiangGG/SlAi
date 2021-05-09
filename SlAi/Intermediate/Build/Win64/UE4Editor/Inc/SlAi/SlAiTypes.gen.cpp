// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SlAi/Public/Data/SlAiTypes.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSlAiTypes() {}
// Cross Module References
	SLAI_API UEnum* Z_Construct_UEnum_SlAi_ECultureTeam();
	UPackage* Z_Construct_UPackage__Script_SlAi();
// End Cross Module References
	static UEnum* ECultureTeam_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_SlAi_ECultureTeam, Z_Construct_UPackage__Script_SlAi(), TEXT("ECultureTeam"));
		}
		return Singleton;
	}
	template<> SLAI_API UEnum* StaticEnum<ECultureTeam>()
	{
		return ECultureTeam_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ECultureTeam(ECultureTeam_StaticEnum, TEXT("/Script/SlAi"), TEXT("ECultureTeam"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_SlAi_ECultureTeam_Hash() { return 502879781U; }
	UEnum* Z_Construct_UEnum_SlAi_ECultureTeam()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_SlAi();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ECultureTeam"), 0, Get_Z_Construct_UEnum_SlAi_ECultureTeam_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ECultureTeam::EN", (int64)ECultureTeam::EN },
				{ "ECultureTeam::CH", (int64)ECultureTeam::CH },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "CH.Name", "ECultureTeam::CH" },
				{ "Comment", "/**\n * \n *///\xe8\xaf\xad\xe8\xa8\x80\xe6\x9e\x9a\xe4\xb8\xbe\n" },
				{ "EN.Name", "ECultureTeam::EN" },
				{ "ModuleRelativePath", "Public/Data/SlAiTypes.h" },
				{ "ToolTip", "//\xe8\xaf\xad\xe8\xa8\x80\xe6\x9e\x9a\xe4\xb8\xbe" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_SlAi,
				nullptr,
				"ECultureTeam",
				"ECultureTeam",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
