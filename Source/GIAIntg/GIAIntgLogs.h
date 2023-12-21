// Copyright (C) 2023 owoDra

#pragma once

#include "Logging/LogMacros.h"

GIAINTG_API DECLARE_LOG_CATEGORY_EXTERN(LogGIAI, Log, All);

#if !UE_BUILD_SHIPPING

#define GIAILOG(FormattedText, ...) UE_LOG(LogGIAI, Log, FormattedText, __VA_ARGS__)

#define GIAIENSURE(InExpression) ensure(InExpression)
#define GIAIENSURE_MSG(InExpression, InFormat, ...) ensureMsgf(InExpression, InFormat, __VA_ARGS__)
#define GIAIENSURE_ALWAYS_MSG(InExpression, InFormat, ...) ensureAlwaysMsgf(InExpression, InFormat, __VA_ARGS__)

#define GIAICHECK(InExpression) check(InExpression)
#define GIAICHECK_MSG(InExpression, InFormat, ...) checkf(InExpression, InFormat, __VA_ARGS__)

#else

#define GIAILOG(FormattedText, ...)

#define GIAIENSURE(InExpression) InExpression
#define GIAIENSURE_MSG(InExpression, InFormat, ...) InExpression
#define GIAIENSURE_ALWAYS_MSG(InExpression, InFormat, ...) InExpression

#define GIAICHECK(InExpression) InExpression
#define GIAICHECK_MSG(InExpression, InFormat, ...) InExpression

#endif