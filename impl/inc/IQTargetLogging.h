/*
 * Copyright (c) 2016-2017 AT&T Intellectual Property. ALL RIGHTS RESERVED
 *
 * This code is licensed under a personal license granted to you by AT&T.
 *
 * All use must comply with the terms of such license. No unauthorized use,
 * copying, modifying or transfer is permitted without the express permission
 * of AT&T. If you do not have a copy of the license, you may obtain a copy
 * of such license from AT&T.
 */

#ifndef IQTargetLogging_h
#define IQTargetLogging_h

//#include "IQPortingUtils.h"

#include <cstring>
#include <string>

#define IQ_PORTING_LOGV(fmt_string, ...)	\
	IQTargetInternalLog(IQ_FILENAME, (unsigned short)IQ_LINENUM, fmt_string, ## __VA_ARGS__ );

#if (CIQ_BUILDTYPE != CIQ_BUILDTYPE_RELEASE)
#define IQ_PORTING_DBG_LOGV(fmt_string, ...)	\
	IQTargetInternalLog(IQ_FILENAME, (unsigned short)IQ_LINENUM, fmt_string, ## __VA_ARGS__ );
#else
#define IQ_PORTING_DBG_LOGV(fmt_string, ...)
#endif

void IQTargetInternalLog(const char *filename, unsigned short linenum, const char *format, ...);

namespace iq
{
    std::string GetThreadId();
}

#endif	// IQTargetLogging_h
