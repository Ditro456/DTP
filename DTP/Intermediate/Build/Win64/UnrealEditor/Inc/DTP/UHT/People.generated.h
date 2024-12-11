// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "People.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef DTP_People_generated_h
#error "People.generated.h already included, missing '#pragma once' in People.h"
#endif
#define DTP_People_generated_h

#define FID_DTP_Source_DTP_Public_People_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPeople(); \
	friend struct Z_Construct_UClass_APeople_Statics; \
public: \
	DECLARE_CLASS(APeople, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DTP"), NO_API) \
	DECLARE_SERIALIZER(APeople)


#define FID_DTP_Source_DTP_Public_People_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	APeople(APeople&&); \
	APeople(const APeople&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APeople); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APeople); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APeople) \
	NO_API virtual ~APeople();


#define FID_DTP_Source_DTP_Public_People_h_9_PROLOG
#define FID_DTP_Source_DTP_Public_People_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_DTP_Source_DTP_Public_People_h_12_INCLASS_NO_PURE_DECLS \
	FID_DTP_Source_DTP_Public_People_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DTP_API UClass* StaticClass<class APeople>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_DTP_Source_DTP_Public_People_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
