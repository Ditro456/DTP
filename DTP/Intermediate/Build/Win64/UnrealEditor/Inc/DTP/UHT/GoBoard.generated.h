// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GoBoard.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef DTP_GoBoard_generated_h
#error "GoBoard.generated.h already included, missing '#pragma once' in GoBoard.h"
#endif
#define DTP_GoBoard_generated_h

#define FID_DTP_Source_DTP_Public_GoBoard_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAGoBoard(); \
	friend struct Z_Construct_UClass_AGoBoard_Statics; \
public: \
	DECLARE_CLASS(AGoBoard, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DTP"), NO_API) \
	DECLARE_SERIALIZER(AGoBoard)


#define FID_DTP_Source_DTP_Public_GoBoard_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AGoBoard(AGoBoard&&); \
	AGoBoard(const AGoBoard&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AGoBoard); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGoBoard); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AGoBoard) \
	NO_API virtual ~AGoBoard();


#define FID_DTP_Source_DTP_Public_GoBoard_h_12_PROLOG
#define FID_DTP_Source_DTP_Public_GoBoard_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_DTP_Source_DTP_Public_GoBoard_h_15_INCLASS_NO_PURE_DECLS \
	FID_DTP_Source_DTP_Public_GoBoard_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DTP_API UClass* StaticClass<class AGoBoard>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_DTP_Source_DTP_Public_GoBoard_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
