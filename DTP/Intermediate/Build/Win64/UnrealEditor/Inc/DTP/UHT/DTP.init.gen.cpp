// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDTP_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_DTP;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_DTP()
	{
		if (!Z_Registration_Info_UPackage__Script_DTP.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/DTP",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0xD05E2A85,
				0x2672EB16,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_DTP.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_DTP.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_DTP(Z_Construct_UPackage__Script_DTP, TEXT("/Script/DTP"), Z_Registration_Info_UPackage__Script_DTP, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xD05E2A85, 0x2672EB16));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
