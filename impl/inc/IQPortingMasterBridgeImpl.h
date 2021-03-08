/**
 ***********************************************************************************************
 * @file 	IQPortingMasterBridge.h
 * @brief	Prototypes describing the "master" side of the IQ Agent porting layer
 *			master/slave bridge interface
 * @ingroup	MasterPortingModule
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
 * This file describes part of the interface for the @ref MasterPortingModule "Master porting module".
 * An integrator is expected to provide implementations of the functions described by these
 * prototypes.
 * 
 * These functions provide a simple full-duplex bytestream communication bridge that a "master"
 * IQ Agent can use to communicate with a second "slave" agent with which it can cooperate to
 * collect metrics.  This master/slave bridge need only be implemented on systems in which two
 * or more sub-systems need to submit metrics, but no shared memory is available.
 *
 * One intended use case is for dual-processor smartphones on which the application and baseband
 * processors share no RAM but communicate exclusively via a serial mux.  In this case, the
 * application processor would run the master agent and the baseband processor would run the
 * slave agent.
 *
 * This interface represents the "master" side of the master/slave bridge, and thus must be
 * implemented for the master agent only.  The "slave" side of this interface is described in
 * IQPortingSlaveBridge.h.  If the target device does not require a slave agent, these functions
 * must be stubbed out to return ::IQ_PORTING_NOT_IMPLEMENTED.
 * 
 * It is expected that the connection described by this interface be implemented as efficiently
 * as possible.  During normal operation, the agent will take great pains to ensure that as 
 * little data as possible is passed over this interface, and that this data is "bursty" (that
 * is, the agent will favor sending a lot of data all at once and spending the rest of the time
 * idle, rather sending a thin trickle of data over a long period of time).
 * 
 * This connection is expected to be reliable.  For maximum performance, no error checking or 
 * correction is performed by either the slave or master agents.
 *
 * This interface is designed to allow the master and slave agents to have somewhat independent
 * lifecycles.  This is to allow for separate start-up schedules for the application and baseband
 * processors, and (if necessary) to allow the baseband processor to be shut down during 
 * "flight mode" or in other power-saving scenarios.
 *
 **/
 
/**
 * @defgroup	MasterPortingModule	Master porting module
 * @brief		A porting module required by the IQ Agent which provides services required
 *`				by the "master" back-end component in a master/slave configuration.
 *
 * (To be written)
 **/

#ifndef IQPortingMasterBridgeImpl_h
#define IQPortingMasterBridgeImpl_h

#include "IQPortingIO.h"

//================================================================
// This file can be used in C or C++ environments.
//================================================================
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the "master" end of the porting layer master/slave bridge implementation.
 * The integrator must implement this function to initialize any state and allocate any resources
 * required by the porting layer bridge master implementation.  The (master) agent will call this 
 * function before calling any other bridge master functions, during agent initialization.
 * 
 * The IQ Agent uses the return value from this function to determine whether or not a
 * slave agent is present, and thus whether it needs to operate in master/slave bridged mode.
 * Operating in bridged mode changes the behavior of the agent significantly, so it is important
 * to correctly return ::IQ_TARGET_NOT_IMPLEMENTED if the host device has no slave agent.
 *
 * A return value of ::IQ_PORTING_OK does *not* indicate that a connection with the slave agent
 * has been established, only that a bridge is implemented and that a slave agent exists to
 * be connected with.
 * 
 * @return		The result of the attempt to initialize the porting layer bridge master implementation.
 * 		@retval	::IQ_PORTING_OK					initialization was successful
 * 		@retval	::IQ_PORTING_NOT_IMPLEMENTED	no master/slave bridge is implemented; this
 *												target does not require a slave agent
 * 		@retval	::IQ_PORTING_ERROR				there was an error during initialization
 **/
iq_porting_status_t IQPorting_MasterBridgeInitializeImpl( IQ_VOID_PARAMLIST );


/**
 * Open the master/slave bridge, from the master side of the connection.
 * The integrator must implement this function to connect to the slave agent over the master/slave
 * bridge, and to register the provided callback for bridge I/O events.  The agent will call this
 * function soon after a successful call to IQPorting_MasterBridgeInitialize().  If 
 * IQPorting_MasterBridgeInitialize() returns ::IQ_PORTING_NOT_IMPLEMENTED, this (and all other
 * bridge master functions) will never be called.
 * 
 * This function is expected to do any handshaking or other connection management required to
 * establish a bridge to the slave agent.  A connection is considered to have been established
 * with the slave agent if and only if both the master and slave agents are initialized and
 * running, and both have called their respective IQPorting_*BridgeOpen() porting layer functions.
 * Neither the master nor slave agent will attempt to read or write data over the bridge until
 * the bridge has completed opening.
 * 
 * IQPorting_MasterBridgeOpen() may finish opening the connection synchronously, in which case it
 * must return ::IQ_PORTING_OK.  However, if the connection cannot yet be established (for example,
 * if the slave agent has yet to be initialized, or even if the processor on which the slave agent
 * resides is shut down), this function should return ::IQ_PORTING_IO_ASYNC_PENDING to indicate that
 * the request will complete asynchronously, and the porting layer should later call @a callbackFunc
 * with an ::IQ_PORTING_IOEVENT_OPEN_COMPLETE event when the open operation has completed.  A return value 
 * of ::IQ_PORTING_IO_ASYNC_PENDING is a promise that an ::IQ_PORTING_IOEVENT_OPEN_COMPLETE event will be
 * generated on this callback when the open has completed; the agent will not attempt to open the
 * bridge again until it receives a callback.
 *
 * Once a connection is established, the agent will issue a read on this bridge and may at any time
 * begin to write data to be sent to the slave agent.  It is illegal to drop any data sent over the
 * bridge connection, and most data sent over the connection is time sensitive, so it is important not
 * to indicate that the bridge has completed opening until both sides of the bridge have issued an
 * ...Open() call and are thus ready to send and receive data.
 * 
 * If at any time after the bridge has been successfully opened the remote end of the bridge is shut
 * down or the connection is otherwise broken, @a callbackFunc should be called with an 
 * ::IQ_PORTING_IOEVENT_ERROR event and with ::IQ_PORTING_IO_BROKEN as the @a ioError parameter.
 * The agent will respond by closing the bridge with IQPorting_MasterBridgeClose() and resetting it's
 * internal master/slave bridge state.  Unless the agent is shutting down, it will then soon after
 * re-issue a call to IQPorting_MasterBridgeOpen() to attempt to contact the slave agent again.
 * 
 * @param[in]	callbackFunc	the callback function the porting layer implementation should call
 * 								to inform the agent about I/O events related to the master/slave bridge
 * @param[in]	callbackData	a datum that should be passed along with any call to @a callbackFunc
 * 
 * @return		The result of the attempt to open the bridge.
 * 		@retval	::IQ_PORTING_OK					the bridge connection was established
 * 		@retval	::IQ_PORTING_NOT_IMPLEMENTED	no master/slave bridge is implemented; this
 *												target does not require a slave agent
 *		@retval	::IQ_PORTING_IO_ASYNC_PENDING	the connection operation has been queued asynchronously; the
 *												porting layer implementation will call @a callbackFunc with
 * 												an ::IQ_PORTING_IOEVENT_OPEN_COMPLETE event when this operation has
 * 												completed
 * 		@retval	::IQ_PORTING_ERROR				there was some other unspecified error trying
 * 												to open the bridge
 **/
iq_porting_status_t IQPorting_MasterBridgeOpenImpl(iq_io_callback_t callbackFunc, void *callbackData);


/**
 * Read data sent by the slave agent over the bridge.
 * The integrator must implement this function to read data from the master/slave bridge.  The
 * number of bytes requested to be read is indicated by the @a ioLen parameter.  The implementation 
 * is permitted to read any non-zero number of bytes up to @a ioLen.  If any number of bytes 
 * were successfully read (synchronously), @a ioLen must be set to the number of bytes read
 * and the function must return IQ_PORTING_OK.  If an error occurs, a value indicating the 
 * error must be  returned and @a ioLen and the contents of @a ioBuffer will be considered 
 * by the agent to be undefined.
 * 
 * This function can be implemented to respond to the read request synchronously (returning
 * ::IQ_PORTING_OK, as described above), to queue the request for asynchronous I/O (returning 
 * ::IQ_PORTING_IO_ASYNC_PENDING), or to indicate to the caller that no data is available at 
 * this time (returning ::IQ_PORTING_IO_WOULDBLOCK).  A return value of ::IQ_PORTING_IO_WOULDBLOCK 
 * promises that an ::IQ_PORTING_IOEVENT_READABLE I/O event will be generated on the associated 
 * callback (provided in IQPorting_MasterBridgeOpen()) when data becomes available.  A return value 
 * of ::IQ_PORTING_IO_ASYNC_PENDING promises that an ::IQ_PORTING_IOEVENT_READ_COMPLETE I/O event 
 * will be generated on this callback when the requested read operation has completed.  For more 
 * information on the semantics of I/O events and the behaviors expected of I/O interfaces, see 
 * the documentation for the @ref IOPortingModule "I/O porting module".
 * 
 * This function is not permitted to block if no data is currently available, but must instead
 * use one of the two asynchronous response methods.
 * 
 * The agent will call this function soon after successfully opening the bridge via 
 * IQPorting_MasterBridgeOpen() (and waiting for the completion callback, if necessary) to wait for
 * any data coming over the bridge from the slave agent.
 * 
 * The agent will never make more than one outstanding read request on this side of the bridge.  If
 * ::IQ_PORTING_IO_WOULDBLOCK or ::IQ_PORTING_IO_ASYNC_PENDING is returned from this function,
 * the agent will never attempt to read from the bridge again until it receives a callback event
 * (one of ::IQ_PORTING_IOEVENT_READABLE, ::IQ_PORTING_IOEVENT_READ_COMPLETE, or
 * ::IQ_PORTING_IOEVENT_ERROR).
 * 
 * @param[in]		ioBuffer	pointer to the buffer into which the data should be read
 * @param[in,out] 	ioLen		the number of bytes to read; on successful completion of the
 * 								I/O operation (i.e. a return value of ::IQ_PORTING_OK), this
 * 								must be set to the number of bytes actually read
 * 
 * @return		The result of the attempt to read data over the master/slave bridge.
 * 	@retval	::IQ_PORTING_OK					the read operation completed synchronously; the read data
 * 											has been placed into @a ioBuffer and @a ioLen has been set to
 * 											the number of bytes that were read
 * 	@retval	::IQ_PORTING_NOT_IMPLEMENTED	no master/slave bridge is implemented; this
 *											target does not require a slave agent
 *	@retval ::IQ_PORTING_IO_WOULDBLOCK		no new data is yet available on the bridge; the porting layer
 * 											implementation will call the associated callback with an 
 * 											::IQ_PORTING_IOEVENT_READABLE event when this operation should
 * 											be retried
 *	@retval	::IQ_PORTING_IO_ASYNC_PENDING	the requested operation has been queued asynchronously; the
 *											porting layer implementation will call the associated callback with
 * 											an ::IQ_PORTING_IOEVENT_READ_COMPLETE event when this operation has
 * 											completed
 *	@retval	::IQ_PORTING_IO_BROKEN			the bridge was broken in some way; the agent will respond by
 *											closing and attempting to re-open the bridge
 *  @retval	::IQ_PORTING_ERROR				there was some other unspecified error trying to read from the bridge
 **/
iq_porting_status_t IQPorting_MasterBridgeReadImpl( void *ioBuffer, unsigned long *ioLen );


/**
 * Write data to the slave agent over the bridge.
 * The integrator must implement this function to write data over the master/slave bridge.  The
 * number of bytes requested to be written is indicated by the @a ioLen parameter.  The implementation 
 * is permitted to write any non-zero number of bytes up to @a ioLen.  If any number of bytes 
 * were successfully written (synchronously), @a ioLen must be set to the number of bytes written
 * and the function must return IQ_PORTING_OK.  If an error occurs, a value indicating the 
 * error must be returned and @a ioLen will be considered by the agent to be undefined.
 * 
 * This function can be implemented to respond to the write request synchronously (returning
 * ::IQ_PORTING_OK, as described above), to queue the request for asynchronous I/O (returning 
 * ::IQ_PORTING_IO_ASYNC_PENDING), or to indicate to the caller that the bridge cannot accept
 * any more data at this time (returning ::IQ_PORTING_IO_WOULDBLOCK).  A return value of 
 * ::IQ_PORTING_IO_WOULDBLOCK promises that an ::IQ_PORTING_IOEVENT_WRITABLE I/O event will be 
 * generated on the associated callback (provided in IQPorting_MasterBridgeOpen()) when data becomes
 * available.  A return value of ::IQ_PORTING_IO_ASYNC_PENDING promises that an 
 * ::IQ_PORTING_IOEVENT_WRITE_COMPLETE I/O event will be generated on this callback when the 
 * requested write operation has completed.  For more information on the semantics of I/O events
 * and the behaviors expected of I/O interfaces, see the documentation for the 
 * @ref IOPortingModule "I/O porting module".
 * 
 * This function is not permitted to block if the bridge cannot immediately accept the data,
 * but must instead use one of the two asynchronous response methods.
 * 
 * The agent may call this function at any time after successfully opening the bridge via 
 * IQPorting_MasterBridgeOpen() (and waiting for the completion callback, if necessary) to send data
 * to the slave agent.
 * 
 * The agent will never make more than one outstanding write request on this side of the bridge.  If
 * ::IQ_PORTING_IO_WOULDBLOCK or ::IQ_PORTING_IO_ASYNC_PENDING is returned from this function,
 * the agent will never attempt to write to the bridge again until it receives a callback event
 * (one of ::IQ_PORTING_IOEVENT_WRITABLE, ::IQ_PORTING_IOEVENT_WRITE_COMPLETE, or
 * ::IQ_PORTING_IOEVENT_ERROR).
 * 
 * @param[in]		ioBuffer	pointer to the buffer containing the data which should be written
 * @param[in,out] 	ioLen		the number of bytes to write; on successful completion of the
 * 								I/O operation (i.e. a return value of ::IQ_PORTING_OK), this
 * 								must be set to the number of bytes actually written
 * 
 * @return		The result of the attempt to write data over the master/slave bridge.
 * 	@retval	::IQ_PORTING_OK					the write operation completed synchronously; @a ioLen has
 * 											been set to the number of bytes that were written
 * 	@retval	::IQ_PORTING_NOT_IMPLEMENTED	no master/slave bridge is implemented; this
 *											target does not require a slave agent
 *	@retval ::IQ_PORTING_IO_WOULDBLOCK		the bridge is not ready to accept new data; the porting layer
 * 											implementation will call the associated callback with an 
 * 											::IQ_PORTING_IOEVENT_WRITABLE event when this operation should
 * 											be retried
 *	@retval	::IQ_PORTING_IO_ASYNC_PENDING	the requested operation has been queued asynchronously; the
 *											porting layer implementation will call the associated callback with
 * 											an ::IQ_PORTING_IOEVENT_WRITE_COMPLETE event when this operation has
 * 											completed
 *	@retval	::IQ_PORTING_IO_BROKEN			the bridge was broken in some way; the agent will respond by
 *											closing and attempting to re-open the bridge
 *  @retval	::IQ_PORTING_ERROR				there was some other unspecified error trying to write to the bridge
 **/
iq_porting_status_t IQPorting_MasterBridgeWriteImpl(IQ_CONST_PARAM void *ioBuffer, unsigned long *ioLen);


/**
 * Close the master/slave bridge.
 * The integrator must implement this function to close this end of the master/slave bridge.
 * The agent will call this function during shut down before calling IQPorting_MasterBridgeShutdown(),
 * or during normal operation if the porting layer implementation indicates an ::IQ_PORTING_IO_BROKEN error
 * on the bridge.  In the latter case, the agent will attempt to re-open the bridge
 * (via IQPorting_MasterBridgeOpen()) soon after closing it.
 *
 * Note that during the shutdown sequence the master and slave may exchange a significant amount of data, 
 * and will perform final handshaking before closing the connection.  Any data written to the bridge before
 * it is requested to be closed must be properly delivered to the slave agent before the connection is broken.
 * If there is data waiting to be read on the bridge when this function is called, that data should be
 * discarded.
 * 
 * @return		The result of the attempt to close the bridge.
 * 		@retval	::IQ_PORTING_OK					the bridge was successfully closed
 * 		@retval	::IQ_PORTING_NOT_IMPLEMENTED	no master/slave bridge is implemented; this
 *												target does not require a slave agent
 * 		@retval	::IQ_PORTING_ERROR				there was an error closing the bridge
 **/
iq_porting_status_t	IQPorting_MasterBridgeCloseImpl( IQ_VOID_PARAMLIST );


/**
 * Shut down the porting layer master/slave bridge implementation.
 * The integrator must implement this function to shut down the bridge implementation, freeing
 * any resources allocated during IQPorting_MasterBridgeInitialize().  The agent will call this
 * during the agent shut down sequence, after which no further bridge porting layer functions
 * will be called.
 * 
 * @return		The result of the attempt to shut down the porting layer bridge implementation.
 * 		@retval	::IQ_PORTING_OK					shut down was successful
 * 		@retval	::IQ_PORTING_NOT_IMPLEMENTED	no master/slave bridge is implemented; this
 *												target does not require a slave agent
 * 		@retval	::IQ_PORTING_ERROR				there was an error during shut down
 **/
iq_porting_status_t	IQPorting_MasterBridgeShutdownImpl( IQ_VOID_PARAMLIST );


/**
 * For dynamic control the log output
 **/
void IQPorting_LoggingEnabledListenerImpl(bool loggingEnabled);

//================================================================
// This file can be used in C or C++ environments.
//================================================================

#ifdef __cplusplus
}
#endif

#endif	// IQPortingMasterBridge_h
