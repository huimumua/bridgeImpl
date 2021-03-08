/**
 ***********************************************************************************************
 * @file 	IQPortingCommon.h
 * @brief	Common header file providing types and defines needed by
 * 			porting layer headers and implementations.
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
 **/

#ifndef IQPortingCommon_h
#define IQPortingCommon_h

#include "IQPortingVersion.h"
 
//================================================================
// This file can be used in C or C++ environments.
//================================================================
#ifdef __cplusplus
extern "C" {
#endif

#include "IQDefs.h"

#ifndef NULL
#define NULL 0
#endif


/**
 * @name General common types and values
 * @{
 **/

/**
 * Result type returned by any porting layer API that returns a result value.
 **/
typedef long int iq_porting_status_t;

/**
 * Base values for iq_porting_status_t.
 **/
enum {
	IQ_PORTING_OK						= 0,		/**< The operation succeeded */
	IQ_PORTING_ERROR					= -0x10000,	/**< An unspecified error occurred */
	IQ_PORTING_NOT_IMPLEMENTED,						/**< The porting layer does not implement the requested operation */
	IQ_PORTING_INVALID_PARAM,						/**< One of the function parameters was invalid */
	IQ_PORTING_TIMEOUT,								/**< An operation failed to complete in the specified time */
	IQ_PORTING_OUT_OF_MEMORY,						/**< The operation failed because required memory could not be allocated */
	IQ_PORTING_SHUTDOWN_COMPLETE,					/**< The agent has completed shutting down */
	IQ_PORTING_IO_ERROR_BASE			= -0x11000,	/**< Base error return value for porting layer I/O APIs */
	IQ_PORTING_FILE_ERROR_BASE			= -0x12000,	/**< Base error return value for porting layer file APIs */
	IQ_PORTING_SERIAL_ERROR_BASE		= -0x13000,	/**< Base error return value for porting layer serial APIs */
	IQ_PORTING_NET_ERROR_BASE			= -0x14000,	/**< Base error return value for porting layer network APIs */
	IQ_PORTING_CLIENT_ERROR_BASE		= -0x15000,	/**< Base error return value for porting layer client APIs */
	IQ_PORTING_SERVER_ERROR_BASE		= -0x16000	/**< Base error return value for porting layer server APIs */
};

/**
 * Typedef used to specify a time-out in milliseconds.
 **/
typedef unsigned long iq_porting_timeout_t;

/**
 * Value used to indicate an infinite timeout.
 * This value, when returned from IQBackend_Execute(), indicates that the agent
 * does not need to execute again until some outside event occurs (such as a
 * metric submission or an I/O callback).  When used as a timeout to a
 * blocking call, it indicates that the call should wait forever, if necessary.
 **/
#define IQ_INFINITE_TIMEOUT 0xFFFFFFFF
//@}

/**
 * @name Client/server common types and values
 * @{
 **/

/**
 * Typedef used to represent lock IDs.  Lock IDs are used to identify locks
 * system-wide.
 **/
typedef unsigned long iq_porting_lock_id_t;

/**
 * Typedef used to represent a local "handle" to a lock.  Handles are used to
 * refer to locks that have been mapped.
 **/
typedef void * iq_porting_lock_handle_t;

/**
 * Typedef used to represent shared memory region IDs.  IDs with the high bit
 * set are global regions with specific properties.
 **/
typedef unsigned long iq_porting_region_id_t;

/**
 * Typedef used to represent handles to shared memory regions.  Handles are set by the
 * porting layer when a shared memory region is created, and the agent passes this
 * back to the porting layer on subsequent operations on the region.
 **/
typedef void * iq_porting_region_handle_t;

/**
 * Region ID representing the global non-volatile read/write shared memory region.
 * This region should be read/write for the server and for all clients.
 **/
#define IQ_SHM_GLOBAL_NV_RW_REGION (0x80000001UL)
//@}


//================================================================
// This file can be used in C or C++ environments.
//================================================================
#ifdef __cplusplus
}
#endif

#endif	// IQPortingCommon_h

