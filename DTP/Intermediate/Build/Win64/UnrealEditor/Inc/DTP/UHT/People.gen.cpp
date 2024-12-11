// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DTP/Public/People.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePeople() {}

// Begin Cross Module References
DTP_API UClass* Z_Construct_UClass_APeople();
DTP_API UClass* Z_Construct_UClass_APeople_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
UPackage* Z_Construct_UPackage__Script_DTP();
// End Cross Module References

// Begin Class APeople
void APeople::StaticRegisterNativesAPeople()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(APeople);
UClass* Z_Construct_UClass_APeople_NoRegister()
{
	return APeople::StaticClass();
}
struct Z_Construct_UClass_APeople_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "People.h" },
		{ "ModuleRelativePath", "Public/People.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APeople>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_APeople_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_DTP,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APeople_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APeople_Statics::ClassParams = {
	&APeople::StaticClass,
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
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APeople_Statics::Class_MetaDataParams), Z_Construct_UClass_APeople_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APeople()
{
	if (!Z_Registration_Info_UClass_APeople.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APeople.OuterSingleton, Z_Construct_UClass_APeople_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APeople.OuterSingleton;
}
template<> DTP_API UClass* StaticClass<APeople>()
{
	return APeople::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(APeople);
APeople::~APeople() {}
// End Class APeople

// Begin Registration
struct Z_CompiledInDeferFile_FID_DTP_Source_DTP_Public_People_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APeople, APeople::StaticClass, TEXT("APeople"), &Z_Registration_Info_UClass_APeople, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APeople), 3902141269U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DTP_Source_DTP_Public_People_h_2604235232(TEXT("/Script/DTP"),
	Z_CompiledInDeferFile_FID_DTP_Source_DTP_Public_People_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_DTP_Source_DTP_Public_People_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
