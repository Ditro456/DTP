// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PeopleAI.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef DTP_PeopleAI_generated_h
#error "PeopleAI.generated.h already included, missing '#pragma once' in PeopleAI.h"
#endif
#define DTP_PeopleAI_generated_h

#define FID_DTP_Source_DTP_Public_PeopleAI_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPeopleAI(); \
	friend struct Z_Construct_UClass_APeopleAI_Statics; \
public: \
	DECLARE_CLASS(APeopleAI, AAIController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DTP"), NO_API) \
	DECLARE_SERIALIZER(APeopleAI)


#define FID_DTP_Source_DTP_Public_PeopleAI_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API APeopleAI(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	APeopleAI(APeopleAI&&); \
	APeopleAI(const APeopleAI&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APeopleAI); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APeopleAI); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(APeopleAI) \
	NO_API virtual ~APeopleAI();


#define FID_DTP_Source_DTP_Public_PeopleAI_h_12_PROLOG
#define FID_DTP_Source_DTP_Public_PeopleAI_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_DTP_Source_DTP_Public_PeopleAI_h_15_INCLASS_NO_PURE_DECLS \
	FID_DTP_Source_DTP_Public_PeopleAI_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DTP_API UClass* StaticClass<class APeopleAI>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_DTP_Source_DTP_Public_PeopleAI_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
