// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DTP/Public/GoBoard.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGoBoard() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
DTP_API UClass* Z_Construct_UClass_AGoBoard();
DTP_API UClass* Z_Construct_UClass_AGoBoard_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_ACameraActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_APawn();
ENGINE_API UClass* Z_Construct_UClass_UAudioComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UBoxComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_DTP();
// End Cross Module References

// Begin Class AGoBoard
void AGoBoard::StaticRegisterNativesAGoBoard()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AGoBoard);
UClass* Z_Construct_UClass_AGoBoard_NoRegister()
{
	return AGoBoard::StaticClass();
}
struct Z_Construct_UClass_AGoBoard_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "GoBoard.h" },
		{ "ModuleRelativePath", "Public/GoBoard.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_boxComponent_MetaData[] = {
		{ "Category", "GoBoard" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GoBoard.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_goBoardMesh_MetaData[] = {
		{ "Category", "GoBoard" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GoBoard.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_arrow_MetaData[] = {
		{ "Category", "GoBoard" },
		{ "ModuleRelativePath", "Public/GoBoard.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_whiteStone_MetaData[] = {
		{ "Category", "GoBoard" },
		{ "ModuleRelativePath", "Public/GoBoard.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_blackStone_MetaData[] = {
		{ "Category", "GoBoard" },
		{ "ModuleRelativePath", "Public/GoBoard.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_startCamera_MetaData[] = {
		{ "Category", "State" },
		{ "ModuleRelativePath", "Public/GoBoard.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_audioComponent_MetaData[] = {
		{ "Category", "State" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc4\xab\xef\xbf\xbd\xde\xb6\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GoBoard.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc4\xab\xef\xbf\xbd\xde\xb6\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_interactionDistance_MetaData[] = {
		{ "Category", "Interaction" },
		{ "ModuleRelativePath", "Public/GoBoard.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_isPlay_MetaData[] = {
		{ "Category", "Interaction" },
		{ "ModuleRelativePath", "Public/GoBoard.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_hasClosePlayer_MetaData[] = {
		{ "Category", "Interaction" },
		{ "ModuleRelativePath", "Public/GoBoard.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_boxComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_goBoardMesh;
	static const UECodeGen_Private::FClassPropertyParams NewProp_arrow;
	static const UECodeGen_Private::FClassPropertyParams NewProp_whiteStone;
	static const UECodeGen_Private::FClassPropertyParams NewProp_blackStone;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_startCamera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_audioComponent;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_interactionDistance;
	static void NewProp_isPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_isPlay;
	static void NewProp_hasClosePlayer_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_hasClosePlayer;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGoBoard>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGoBoard_Statics::NewProp_boxComponent = { "boxComponent", nullptr, (EPropertyFlags)0x0010000000080009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGoBoard, boxComponent), Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_boxComponent_MetaData), NewProp_boxComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGoBoard_Statics::NewProp_goBoardMesh = { "goBoardMesh", nullptr, (EPropertyFlags)0x0010000000080009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGoBoard, goBoardMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_goBoardMesh_MetaData), NewProp_goBoardMesh_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AGoBoard_Statics::NewProp_arrow = { "arrow", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGoBoard, arrow), Z_Construct_UClass_UClass, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_arrow_MetaData), NewProp_arrow_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AGoBoard_Statics::NewProp_whiteStone = { "whiteStone", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGoBoard, whiteStone), Z_Construct_UClass_UClass, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_whiteStone_MetaData), NewProp_whiteStone_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AGoBoard_Statics::NewProp_blackStone = { "blackStone", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGoBoard, blackStone), Z_Construct_UClass_UClass, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_blackStone_MetaData), NewProp_blackStone_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGoBoard_Statics::NewProp_startCamera = { "startCamera", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGoBoard, startCamera), Z_Construct_UClass_ACameraActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_startCamera_MetaData), NewProp_startCamera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGoBoard_Statics::NewProp_audioComponent = { "audioComponent", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGoBoard, audioComponent), Z_Construct_UClass_UAudioComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_audioComponent_MetaData), NewProp_audioComponent_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AGoBoard_Statics::NewProp_interactionDistance = { "interactionDistance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGoBoard, interactionDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_interactionDistance_MetaData), NewProp_interactionDistance_MetaData) };
void Z_Construct_UClass_AGoBoard_Statics::NewProp_isPlay_SetBit(void* Obj)
{
	((AGoBoard*)Obj)->isPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AGoBoard_Statics::NewProp_isPlay = { "isPlay", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AGoBoard), &Z_Construct_UClass_AGoBoard_Statics::NewProp_isPlay_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_isPlay_MetaData), NewProp_isPlay_MetaData) };
void Z_Construct_UClass_AGoBoard_Statics::NewProp_hasClosePlayer_SetBit(void* Obj)
{
	((AGoBoard*)Obj)->hasClosePlayer = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AGoBoard_Statics::NewProp_hasClosePlayer = { "hasClosePlayer", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AGoBoard), &Z_Construct_UClass_AGoBoard_Statics::NewProp_hasClosePlayer_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_hasClosePlayer_MetaData), NewProp_hasClosePlayer_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AGoBoard_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGoBoard_Statics::NewProp_boxComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGoBoard_Statics::NewProp_goBoardMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGoBoard_Statics::NewProp_arrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGoBoard_Statics::NewProp_whiteStone,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGoBoard_Statics::NewProp_blackStone,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGoBoard_Statics::NewProp_startCamera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGoBoard_Statics::NewProp_audioComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGoBoard_Statics::NewProp_interactionDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGoBoard_Statics::NewProp_isPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGoBoard_Statics::NewProp_hasClosePlayer,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AGoBoard_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AGoBoard_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APawn,
	(UObject* (*)())Z_Construct_UPackage__Script_DTP,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AGoBoard_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AGoBoard_Statics::ClassParams = {
	&AGoBoard::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AGoBoard_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AGoBoard_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AGoBoard_Statics::Class_MetaDataParams), Z_Construct_UClass_AGoBoard_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AGoBoard()
{
	if (!Z_Registration_Info_UClass_AGoBoard.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AGoBoard.OuterSingleton, Z_Construct_UClass_AGoBoard_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AGoBoard.OuterSingleton;
}
template<> DTP_API UClass* StaticClass<AGoBoard>()
{
	return AGoBoard::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AGoBoard);
AGoBoard::~AGoBoard() {}
// End Class AGoBoard

// Begin Registration
struct Z_CompiledInDeferFile_FID_DTP_Source_DTP_Public_GoBoard_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AGoBoard, AGoBoard::StaticClass, TEXT("AGoBoard"), &Z_Registration_Info_UClass_AGoBoard, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AGoBoard), 2610361215U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DTP_Source_DTP_Public_GoBoard_h_2176415653(TEXT("/Script/DTP"),
	Z_CompiledInDeferFile_FID_DTP_Source_DTP_Public_GoBoard_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_DTP_Source_DTP_Public_GoBoard_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
