// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DTP/Public/PeopleAI.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePeopleAI() {}

// Begin Cross Module References
AIMODULE_API UClass* Z_Construct_UClass_AAIController();
DTP_API UClass* Z_Construct_UClass_APeopleAI();
DTP_API UClass* Z_Construct_UClass_APeopleAI_NoRegister();
UPackage* Z_Construct_UPackage__Script_DTP();
// End Cross Module References

// Begin Class APeopleAI
void APeopleAI::StaticRegisterNativesAPeopleAI()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(APeopleAI);
UClass* Z_Construct_UClass_APeopleAI_NoRegister()
{
	return APeopleAI::StaticClass();
}
struct Z_Construct_UClass_APeopleAI_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "PeopleAI.h" },
		{ "ModuleRelativePath", "Public/PeopleAI.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_maxWalkSpeed_MetaData[] = {
		{ "Category", "AI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ==============================================================\n//\x09\x09\x09\x09\x09\x09\x09Public Variable\n// ==============================================================\n" },
#endif
		{ "ModuleRelativePath", "Public/PeopleAI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Public Variable" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_minWaitTime_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "Public/PeopleAI.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_maxWaitTime_MetaData[] = {
		{ "Category", "AI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xd6\xbc\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xc3\xb0\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd)\n" },
#endif
		{ "ModuleRelativePath", "Public/PeopleAI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd6\xbc\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xc3\xb0\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_rotationSpeed_MetaData[] = {
		{ "Category", "AI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xd6\xb4\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xc3\xb0\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd)\n" },
#endif
		{ "ModuleRelativePath", "Public/PeopleAI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd6\xb4\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xc3\xb0\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd)" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_maxWalkSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_minWaitTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_maxWaitTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_rotationSpeed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APeopleAI>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APeopleAI_Statics::NewProp_maxWalkSpeed = { "maxWalkSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APeopleAI, maxWalkSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_maxWalkSpeed_MetaData), NewProp_maxWalkSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APeopleAI_Statics::NewProp_minWaitTime = { "minWaitTime", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APeopleAI, minWaitTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_minWaitTime_MetaData), NewProp_minWaitTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APeopleAI_Statics::NewProp_maxWaitTime = { "maxWaitTime", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APeopleAI, maxWaitTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_maxWaitTime_MetaData), NewProp_maxWaitTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APeopleAI_Statics::NewProp_rotationSpeed = { "rotationSpeed", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APeopleAI, rotationSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_rotationSpeed_MetaData), NewProp_rotationSpeed_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APeopleAI_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APeopleAI_Statics::NewProp_maxWalkSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APeopleAI_Statics::NewProp_minWaitTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APeopleAI_Statics::NewProp_maxWaitTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APeopleAI_Statics::NewProp_rotationSpeed,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APeopleAI_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_APeopleAI_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AAIController,
	(UObject* (*)())Z_Construct_UPackage__Script_DTP,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APeopleAI_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APeopleAI_Statics::ClassParams = {
	&APeopleAI::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_APeopleAI_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_APeopleAI_Statics::PropPointers),
	0,
	0x009002A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APeopleAI_Statics::Class_MetaDataParams), Z_Construct_UClass_APeopleAI_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APeopleAI()
{
	if (!Z_Registration_Info_UClass_APeopleAI.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APeopleAI.OuterSingleton, Z_Construct_UClass_APeopleAI_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APeopleAI.OuterSingleton;
}
template<> DTP_API UClass* StaticClass<APeopleAI>()
{
	return APeopleAI::StaticClass();
}
APeopleAI::APeopleAI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(APeopleAI);
APeopleAI::~APeopleAI() {}
// End Class APeopleAI

// Begin Registration
struct Z_CompiledInDeferFile_FID_DTP_Source_DTP_Public_PeopleAI_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APeopleAI, APeopleAI::StaticClass, TEXT("APeopleAI"), &Z_Registration_Info_UClass_APeopleAI, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APeopleAI), 3006600870U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DTP_Source_DTP_Public_PeopleAI_h_1617284361(TEXT("/Script/DTP"),
	Z_CompiledInDeferFile_FID_DTP_Source_DTP_Public_PeopleAI_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_DTP_Source_DTP_Public_PeopleAI_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
