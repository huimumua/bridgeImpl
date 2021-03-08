/*
 ***********************************************************************************************
 * @file 	IQTargetDefs.h
 * @brief 	Target-specific defines needed by the IQ Agent header files.
 * @if cr   Copyright (c) 2016 AT&T Intellectual Property. ALL RIGHTS RESERVED
 * @if cr
 * @if cr   This code is licensed under a personal license granted to you by AT&T.
 * @if cr
 * @if cr   All use must comply with the terms of such license. No unauthorized use,
 * @if cr   copying, modifying or transfer is permitted without the express permission
 * @if cr   of AT&T. If you do not have a copy of the license, you may obtain a copy
 * @if cr   of such license from AT&T.
 ***********************************************************************************************
 * @endif
 * 
 * This file contains all the default definitions for various macros needed by the IQ
 * Agent headers.  These macros are expected to be compiler and target-platform specific.
 * In order to define them for a particular platform/compiler configuration that is not
 * correctly handled by these defaults, put your new definitions in IQTargetDefOverrides.h.
 **/
 
#ifndef IQTargetDefs_h
#define IQTargetDefs_h

#include "IQTargetDefOverrides.h"

//================================================================
// This file can be used in C or C++ environments.
//================================================================
#ifdef __cplusplus
extern "C" {
#endif

#ifndef IQ_INTEGRATION_OVERRIDE_FILE_LINE
	#ifndef __arm
		#define IQ_FILENAME				__FILE__
	#elif defined( __GNUC__ )
		#define IQ_FILENAME				__FILE__
	#else
		#define IQ_FILENAME				__MODULE__
	#endif
	#define IQ_LINENUM					__LINE__
#endif	// IQ_INTEGRATION_OVERRIDE_FILE_LINE

//=====================================================

#ifndef IQ_INTEGRATION_OVERRIDE_CONST
	#ifdef cplusplus
		#define IQ_CONST_PARAM			const
		#define IQ_CONST_RESULT			const
	#else
		#define IQ_CONST_PARAM			const
		#define IQ_CONST_RESULT			const
	#endif
#endif	// IQ_INTEGRATION_OVERRIDE_CONST

//=====================================================

#ifndef IQ_INTEGRATION_OVERRIDE_VOID_PARAMLIST
	#define IQ_VOID_PARAMLIST			void
#endif	// IQ_INTEGRATION_OVERRIDE_VOID_PARAMLIST

//=====================================================

#ifndef IQ_INTEGRATION_OVERRIDE_UNUSED_PARAM
	#ifdef __arm
		#define IQ_UNUSED_PARAM( x )	(void)x;
	#elif defined( __GNUC__ )
		#define IQ_UNUSED_PARAM( x )	(void)x;
	#else
		#define IQ_UNUSED_PARAM( x )	(x);
	#endif
#endif	// IQ_INTEGRATION_OVERRIDE_UNUSED_PARAM

//=====================================================

#ifndef IQ_INTEGRATION_OVERRIDE_PACKING
	#if defined( __GNUC__ )
		#define IQ_PACKED_STRUCT		struct __attribute__ ((__packed__))
		#define IQ_PACKED_STRUCTEX( x )	struct x __attribute__ ((__packed__))
	#elif defined( __arm )
		#define IQ_PACKED_STRUCT		__packed struct
		#define IQ_PACKED_STRUCTEX( x )	__packed struct x
	#else
		#define IQ_PACKED_STRUCT		struct
		#define IQ_PACKED_STRUCTEX( x )	struct x
	#endif
#endif  // IQ_INTEGRATION_OVERRIDE_PACKING

//================================================================
// This file can be used in C or C++ environments.
//================================================================
#ifdef __cplusplus
}
#endif

#endif	// IQTargetDefs_h
