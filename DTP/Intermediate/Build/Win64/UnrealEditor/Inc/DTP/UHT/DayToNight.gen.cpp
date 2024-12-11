// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DTP/Public/DayToNight.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDayToNight() {}

// Begin Cross Module References
DTP_API UClass* Z_Construct_UClass_ADayToNight();
DTP_API UClass* Z_Construct_UClass_ADayToNight_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UBoxComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_DTP();
// End Cross Module References

// Begin Class ADayToNight
void ADayToNight::StaticRegisterNativesADayToNight()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ADayToNight);
UClass* Z_Construct_UClass_ADayToNight_NoRegister()
{
	return ADayToNight::StaticClass();
}
struct Z_Construct_UClass_ADayToNight_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "DayToNight.h" },
		{ "ModuleRelativePath", "Public/DayToNight.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_oldClockMesh_MetaData[] = {
		{ "Category", "DayToNight" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DayToNight.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_boxComponent_MetaData[] = {
		{ "Category", "DayToNight" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/DayToNight.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_interactionDistance_MetaData[] = {
		{ "Category", "Interaction" },
		{ "ModuleRelativePath", "Public/DayToNight.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_isDay_MetaData[] = {
		{ "Category", "Interaction" },
		{ "ModuleRelativePath", "Public/DayToNight.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_isTimeChange_MetaData[] = {
		{ "Category", "Interaction" },
		{ "ModuleRelativePath", "Public/DayToNight.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_hasClosePlayer_MetaData[] = {
		{ "Category", "Interaction" },
		{ "ModuleRelativePath", "Public/DayToNight.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_oldClockMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_boxComponent;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_interactionDistance;
	static void NewProp_isDay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_isDay;
	static void NewProp_isTimeChange_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_isTimeChange;
	static void NewProp_hasClosePlayer_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_hasClosePlayer;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADayToNight>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ADayToNight_Statics::NewProp_oldClockMesh = { "oldClockMesh", nullptr, (EPropertyFlags)0x0010000000080009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADayToNight, oldClockMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_oldClockMesh_MetaData), NewProp_oldClockMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ADayToNight_Statics::NewProp_boxComponent = { "boxComponent", nullptr, (EPropertyFlags)0x0010000000080009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADayToNight, boxComponent), Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_boxComponent_MetaData), NewProp_boxComponent_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ADayToNight_Statics::NewProp_interactionDistance = { "interactionDistance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADayToNight, interactionDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_interactionDistance_MetaData), NewProp_interactionDistance_MetaData) };
void Z_Construct_UClass_ADayToNight_Statics::NewProp_isDay_SetBit(void* Obj)
{
	((ADayToNight*)Obj)->isDay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ADayToNight_Statics::NewProp_isDay = { "isDay", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ADayToNight), &Z_Construct_UClass_ADayToNight_Statics::NewProp_isDay_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_isDay_MetaData), NewProp_isDay_MetaData) };
void Z_Construct_UClass_ADayToNight_Statics::NewProp_isTimeChange_SetBit(void* Obj)
{
	((ADayToNight*)Obj)->isTimeChange = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ADayToNight_Statics::NewProp_isTimeChange = { "isTimeChange", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ADayToNight), &Z_Construct_UClass_ADayToNight_Statics::NewProp_isTimeChange_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_isTimeChange_MetaData), NewProp_isTimeChange_MetaData) };
void Z_Construct_UClass_ADayToNight_Statics::NewProp_hasClosePlayer_SetBit(void* Obj)
{
	((ADayToNight*)Obj)->hasClosePlayer = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ADayToNight_Statics::NewProp_hasClosePlayer = { "hasClosePlayer", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ADayToNight), &Z_Construct_UClass_ADayToNight_Statics::NewProp_hasClosePlayer_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_hasClosePlayer_MetaData), NewProp_hasClosePlayer_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADayToNight_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADayToNight_Statics::NewProp_oldClockMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADayToNight_Statics::NewProp_boxComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADayToNight_Statics::NewProp_interactionDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADayToNight_Statics::NewProp_isDay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADayToNight_Statics::NewProp_isTimeChange,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADayToNight_Statics::NewProp_hasClosePlayer,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ADayToNight_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ADayToNight_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_DTP,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ADayToNight_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ADayToNight_Statics::ClassParams = {
	&ADayToNight::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ADayToNight_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ADayToNight_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADayToNight_Statics::Class_MetaDataParams), Z_Construct_UClass_ADayToNight_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ADayToNight()
{
	if (!Z_Registration_Info_UClass_ADayToNight.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADayToNight.OuterSingleton, Z_Construct_UClass_ADayToNight_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ADayToNight.OuterSingleton;
}
template<> DTP_API UClass* StaticClass<ADayToNight>()
{
	return ADayToNight::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ADayToNight);
ADayToNight::~ADayToNight() {}
// End Class ADayToNight

// Begin Registration
struct Z_CompiledInDeferFile_FID_DTP_Source_DTP_Public_DayToNight_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ADayToNight, ADayToNight::StaticClass, TEXT("ADayToNight"), &Z_Registration_Info_UClass_ADayToNight, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADayToNight), 367806296U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DTP_Source_DTP_Public_DayToNight_h_1744444637(TEXT("/Script/DTP"),
	Z_CompiledInDeferFile_FID_DTP_Source_DTP_Public_DayToNight_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_DTP_Source_DTP_Public_DayToNight_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
