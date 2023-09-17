// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(UnrealMecha, Log, All);
#define AGLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define AGLOG_S(Verbosity) UE_LOG(UnrealMecha, Verbosity, TEXT("%s"), *AGLOG_CALLINFO)
#define AGLOG(Verbosity, Format, ...) UE_LOG(UnrealMecha, Verbosity, TEXT("%s %s"), *AGLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define AGCHECK(Expr, ...) { if(!(Expr)) { AGLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; } }