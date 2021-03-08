/*
 ***********************************************************************************************
 * @file 	IQTargetDefOverrides.h
 * @brief 	Override file for target-specific defines needed by the IQ Agent headers.
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
 * This file should be edited by integrators to override any platform or compiler-specific
 * defines needed by the IQ Agent headers that are not properly defined by the "stock"
 * IQTargetDefs.h.
 */

#ifndef IQTargetDefOverrides_h
#define IQTargetDefOverrides_h

//================================================================
// This file can be used in C or C++ environments.
//================================================================
#ifdef __cplusplus
extern "C" {
#endif

//define IQ_INTEGRATION_OVERRIDE_FILE_LINE
//define IQ_FILENAME				< your compiler's filename macro here >
//define IQ_LINENUM				< your compiler's line number macro here >

//=====================================================

//define IQ_INTEGRATION_OVERRIDE_CONST
//define IQ_CONST_PARAM			< your compiler's 'const' param keyword here >
//define IQ_CONST_RESULT			< your compiler's 'const' result keyword here >

//=====================================================

//define IQ_INTEGRATION_OVERRIDE_VOID_PARAMLIST
//define IQ_VOID_PARAMLIST			< your compiler's empty function parameter list keyword here >

//=====================================================

//define IQ_INTEGRATION_OVERRIDE_UNUSED_PARAM
//define IQ_UNUSED_PARAM( x )		< your compiler's unused function parameter macro or trick here >

//=====================================================

//define IQ_PACKED_STRUCT			< your compiler's 1-byte alignment struct packing keyword here >
//define IQ_PACKED_STRUCTEX( x )	< your compiler's 1-byte alignment struct packing keyword here >

//================================================================
// This file can be used in C or C++ environments.
//================================================================
#ifdef __cplusplus
}
#endif

#endif	// IQTargetDefOverrides_h
