/**
 ***********************************************************************************************
 * @file 	IQPortingIO.h
 * @brief	Prototypes describing the IQ Agent's I/O porting module
 * @ingroup	IOPortingModule
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
 * This file describes the interface that defines common types and values needed by the
 * @ref IOPortingModule "I/O porting module".
 **/

/**
 * @defgroup	IOPortingModule	I/O porting module
 * @brief		A porting module required by the IQ Agent which provides I/O services.
 * 
 * The I/O porting module must be implemented by integrators.  It provides functions to
 * perform operations on the local Flash- or disk-based filesystem, to perform network I/O,
 * and to read and write information over a local serial link to a PC.  The prototypes
 * for the functions that must be implemented by the I/O porting module are described by the
 * headers in the <b>headers/port/io/</b> directory.
 * 
 * The I/O porting module must be linked with the back-end IQ Agent component only,
 * and it's functions need @e not be safe for access from multiple threads, as they will only
 * be called by a single thread at a time.  The IQ Agent will perform any locking necessary to
 * protect I/O porting module APIs from simultaneous access from multiple threads.
 * 
 * The documentation of each individual I/O function descibes the specific semantics of that
 * function.  The rest of this section provides a brief overview for how I/O works in the
 * IQ Agent.
 * 
 * @section io_overview Overview of I/O styles
 * 
 * I/O porting module functions that perform I/O on some resource (like a file or a network
 * connection) may choose from several styles of implementations, depending on the style of
 * I/O that is best supported by the host software platform and how critical performance
 * and battery life is on the target device product.
 * 
 * From the point of view of a some thread making a request to an I/O subsystem to perform I/O,
 * a given I/O operation can be executed in one of three general ways:
 * 
 * 	<ol>
 * 		<li>	With <b>synchronous blocking I/O</b>, the I/O operation executes synchronously, blocking
 * 				the calling thread until the operation completes.  If the resource is not yet ready to
 * 				accept data (in the case of a write) or provide data (in the case of a read), or is
 * 				otherwise unprepared for the operation, the calling thread will block until the resource
 * 				becomes available and will then block until the operation completes.
 * 
 * 				This is the simplest style of I/O to use and to implement, but it has obvious drawbacks in
 * 				that the calling thread is blocked and thus unusable until the resource becomes available.
 * 				Blocking I/O also makes it very difficult or impossible to perform I/O on multiple resources
 * 				at once (or on one resource while remaining responsive to other incoming events) without
 * 				creating additional threads to perform each task.
 * 
 * 		<li>	With <b>synchronous non-blocking I/O</b>, the I/O operation still executes synchronously, and still
 * 				blocks the calling thread until the operation completes.  However, unlike synchronous @e blocking
 * 				I/O, if the resource is not available at the time the call is made the thread will not block.
 * 				Instead, a special result value is returned to indicate to the caller that the operation cannot be
 * 				performed at this time and that the caller should try the request again later.  In order to
 * 				prevent the need for the caller to poll the resource until it becomes available, there is usually
 * 				some platform-specific synchronization or callback mechanism provided to allow the caller to be
 * 				notified when the operation that was attempted becomes possible (in POSIX, for example, the
 * 				<tt>select()</tt> call provides this functionality).
 * 
 * 				Synchronous non-blocking I/O often provides significantly better performance than synchronous
 * 				blocking I/O for single-threaded tasks, because usually a large percentage of the time spent
 * 				doing I/O is spent waiting for a resource to become ready.  Since in synchronous non-blocking I/O
 * 				the caller is not blocked during this period, it is able to perform other needed functions.
 * 
 * 		<li>	Finally, with <b>asynchronous non-blocking I/O</b>, the caller returns immediately and the I/O
 * 				operation executes asynchronously "in the background".  The caller is then informed once the
 * 				operation has completed via some mechanism similar to that described in #2.  Unlike the "retry"
 * 				semantics of synchronous non-blocking I/O, the caller is informed of the previous operation's
 * 				@e completion rather than being informed of the resource's readiness to accept new operations.
 * 				As a result, usually in asynchronous non-blocking I/O, the buffer passed by the caller is
 * 				"owned" by the I/O subsystem until the operation completes, because I/O is being performed
 * 				directly into or out of that buffer.  The caller must therefore refrain from modifying or
 * 				re-using that I/O buffer until it is informed of the operation's completion.
 * 
 * 				Asynchronous non-blocking I/O generally allows excellent performance of single-threaded
 * 				tasks, because all I/O processing can happen concurrently with the calling thread's continued
 * 				execution, and any unneccessary memory copying or buffering is eliminated.
 * 	</ol>
 * 
 * @section agent_io IQ Agent I/O
 * 
 * I/O porting module functions indicate the style in which they are performing an operation - and thus both
 * the behavior they expect of the agent with respect to the I/O resource and what future porting module
 * behavior they are promising to the agent - by returning the appropriate result value in response to
 * a request:
 * 	<ul>
 * 		<li>	::IQ_PORTING_IO_COMPLETED (which is identical to 
 * 				::IQ_PORTING_OK) indicates that the operation was successful, and that it was 
 * 				completed synchronously within the context of the call.  The request was fufilled,
 * 				and no further action on the part of the agent or the porting module is expected.
 * 				This will be the case for synchronous blocking I/O, or for synchronous non-blocking
 * 				I/O being performed on a resource that was ready to accept the operation.
 * 
 * 				Note that this indicates nothing about how long the calling thread was blocked while this
 * 				operation completed, if at all.  Also, this value only indicates that the
 * 				operation has completed from the agent's perpective; for a write operation, the
 * 				porting layer may have only copied the given I/O data into some internal buffer for
 * 				later asynchronous processing.
 * 
 * 		<li>	::IQ_PORTING_IO_WOULDBLOCK indicates that the
 * 				resource is @e not currently available for I/O, and that the operation was @e not queued.
 * 				This will be the case for synchronous non-blocking I/O being performed on a resource
 * 				that was @b not ready to accept the operation.
 * 
 * 				A function that returns this value is promising to later inform the agent that the 
 * 				resource in question has become available for this operation, at which point the agent 
 * 				can retry it.  This notification must be performed by calling a ::iq_io_callback_t 
 * 				function associated with the resource with a ::iq_io_event_t that indicates the 
 * 				operation that can be retried.  A function that returns this value @b must later call 
 * 				the associated callback function to indicate that the resource has become available 
 * 				for the requested operation or that it has been closed.
 * 
 * 		<li>	::IQ_PORTING_IO_ASYNC_PENDING indicates that the
 * 				requested operation was started, but has not yet completed and will proceed
 * 				asynchronously with respect to the calling thread.  This value indicates a promise
 * 				to later inform the agent once the operation has completed.  This notification must
 * 				be performed by calling a ::iq_io_callback_t function function associated with the
 * 				resource with a ::iq_io_event_t that indicates the operation that has completed.
 * 				A function that returns this value @b must later call the associated callback function
 * 				to indicate completion or an error that occurred during the operation.
 * 	</ul>
 * 
 * @section io_callbacks I/O callbacks
 * 
 * Callbacks invoked to fufill the contracts implied by returning ::IQ_PORTING_IO_WOULDBLOCK or
 * ::IQ_PORTING_IO_ASYNC_PENDING from an I/O operation are described by the ::iq_io_callback_t
 * function pointer typedef.  I/O resources that support this type of callback completion will receive
 * a callback function to use for callbacks when the resource is created or opened, or when the operation
 * is requested.
 * 
 * A ::iq_io_callback_t takes a ::iq_io_event_t argument that describes why the callback is being
 * invoked.  The specific ::iq_io_event_t that will be generated by a particular operation is
 * defined by the function that performs the operation, and specific I/O resources may define
 * additional ::iq_io_event_t values that correspond to resource-specific operations.  There are some
 * generic values that are used by several I/O resource types:
 * 
 * 	<ul>
 * 		<li>	::IQ_PORTING_IOEVENT_WRITABLE will eventually be generated by an I/O @e write operation that
 * 				returns ::IQ_PORTING_IO_WOULDBLOCK.  This event indicates that the resource has become
 * 				ready to accept write operations.
 * 
 * 		<li>	::IQ_PORTING_IOEVENT_READABLE will, similarly, be generated by an I/O @e read operation that
 * 				returns ::IQ_PORTING_IO_WOULDBLOCK.  This event indicates that the resource has become
 * 				ready to accept read operations.
 * 
 * 		<li>	::IQ_PORTING_IOEVENT_WRITE_COMPLETE will eventually be generated by an I/O @e write operation that
 * 				returns ::IQ_PORTING_IO_ASYNC_PENDING.  This event indicates that the resource has finished
 * 				performing the asynchronous write.  In this case, the @a ioParam argument to the iq_io_callback_t
 * 				will indicate the number of bytes written as a result of the request.
 * 
 * 		<li>	::IQ_PORTING_IOEVENT_READ_COMPLETE will likewise be generated by an I/O @e read operation that
 * 				returns ::IQ_PORTING_IO_ASYNC_PENDING.  This event indicates that the resource has finished
 * 				performing the asynchronous read.  In this case, the @a ioParam argument to the iq_io_callback_t
 * 				will indicate the number of bytes read as a result of the request.
 * 
 * 		<li>	::IQ_PORTING_IOEVENT_ERROR will be generated by an I/O operation that returns
 * 				::IQ_PORTING_IO_WOULDBLOCK @e or ::IQ_PORTING_IO_ASYNC_PENDING, but for which an error was
 * 				encountered on the resource before the condition for the callback could be satisfied (for
 * 				example, if a read operation on a socket returns ::IQ_PORTING_IO_WOULDBLOCK but the connection
 * 				is closed before more data becomes available for reading).  If ::IQ_PORTING_IOEVENT_ERROR
 * 				is passed to a ::iq_io_callback_t as the value of the @a ioEvent ::iq_io_event_t argument,
 * 				the @a error ::iq_porting_status_t argument will be set to the error that was encountered.
 * 				Delivery of a ::IQ_PORTING_IOEVENT_ERROR event indicates the termination of any outstanding
 * 				I/O requests on that resource, and no more pending callbacks will be expected for that resource.
 * 	</ul>
 * 
 * The porting module implementation is permitted to invoke pending I/O callbacks from any thread.  The
 * IQ Agent will do the minimal work required to queue processing that is neccessary as the result of
 * the callback, and will return to the caller as soon as possible.  Note that a critical section may be
 * entered within the callback in order to synchronize with the agent's thread, so the caller may block for
 * a very short amount of time if there is contention.  Contention should be rare, however, and the critical
 * section protects only a very small section of code, so it should be acceptable to make direct I/O callbacks
 * even from real-time threads.  This behavior is recommended if it simplifies the I/O porting module implementation.
 * 
 * For example, the socket interface described in IQPortingNetwork.h takes the callback function to use for
 * operations on a particular socket as an argument to IQPorting_Socket_OpenConnect(), which creates the 
 * socket.  Any subsequent read or write operation on that socket which returns ::IQ_PORTING_IO_WOULDBLOCK or
 * ::IQ_PORTING_IO_ASYNC_PENDING will be followed by a callback on that function with the appropriate
 * ::iq_io_event_t.  The socket I/O interface also defines several additional I/O event types:
 * ::IQ_PORTING_IOEVENT_SOCKET_CONNECTED, which indicates completion of a request to connect to a
 * remote address, and ::IQ_PORTING_IOEVENT_SOCKET_SECURED, which indicates completion of a request
 * to encrypt the socket for secure data transmission.  Finally, the IQPorting_Socket_Close() function
 * both closes the socket and terminates any ongoing requests, such that no callbacks for that socket should
 * be made once the close operation (synchronously) completes.
 * 
 * The IQAgent expects one, and only one, callback for each I/O operation that returns ::IQ_PORTING_IO_WOULDBLOCK
 * or ::IQ_PORTING_IO_ASYNC_PENDING.  Unless otherwise specified for a particular API, the porting layer must not
 * make a callback unless it has returned ::IQ_PORTING_IO_WOULDBLOCK or ::IQ_PORTING_IO_ASYNC_PENDING from a
 * previous porting layer API associated with the callback.
 *
 * Note that each type of I/O resource (file, network, and serial port) defines its own initialization
 * and shutdown interfaces, and defines the scope and lifecycle of its own resources and callbacks.
 * For more information on specific I/O resources and the behavior expected of functions that operate on them,
 * see the documentation for individual I/O resource types and their associated functions.
 **/

#ifndef IQPortingIO_h
#define IQPortingIO_h

#include "IQTargetDefs.h"
#include "IQPortingCommon.h"

//================================================================
// This file can be used in C or C++ environments.
//================================================================
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Possible I/O-related result values that may be reported in a ::iq_porting_result_t.
 * These are result values that can be returned from @ref IOPortingModule "I/O porting module"
 * functions that perform I/O operations.
 **/
enum {
	 IQ_PORTING_IO_COMPLETED = 		//!< The requested I/O operation completed successfully.
	 	IQ_PORTING_OK
	 	
	,IQ_PORTING_IO_WOULDBLOCK = 	//!< The requested I/O operation cannot be performed right now.
		IQ_PORTING_IO_ERROR_BASE	//!< A callback will be made to inform the caller when the operation
    								//!< has completed (or failed), as described in the documentation
    								//!< for the @ref IOPortingModule "I/O porting module" interfaces.

    ,IQ_PORTING_IO_ASYNC_PENDING	//!< The requested I/O operation was started, but is not yet complete.
    								//!< A callback will be made to inform the caller when the operation
    								//!< has completed (or failed), as described in the documentation
    								//!< for the @ref IOPortingModule "I/O porting module" interfaces.

	,IQ_PORTING_IO_BROKEN			//!< The requested I/O operation cannot be completed because
									//!< the resource or stream with which it is associated is no
									//!< longer accessible.
};


/**
 * Typedef for an I/O event type;
 **/
typedef unsigned long iq_io_event_t;

/**
 * Generic I/O events that can be reported via I/O callbacks.
 * This is a base set of event types that may be specified as the value of the ::iq_io_event_t parameter to
 * ::iq_io_callback_t callbacks generated by @ref IOPortingModule "I/O porting module" functions that perform
 * non-blocking I/O operations.
 **/
enum {
	IQ_PORTING_IOEVENT_WRITABLE = 1,			/**<	The resource has become ready to accept writes.
														This event is generated if and only if a previous write call on this
														resource returned ::IQ_PORTING_IO_WOULDBLOCK. */

	IQ_PORTING_IOEVENT_WRITE_COMPLETE,			/**<	The previously initiated request to write data to this
														resource has completed.  The @a ioParam parameter of this
														::iq_io_callback_t contains the number of bytes that
														were successfully written from the I/O buffer that was
														specified in the original request.  This event is generated if
														and only if a previous write request on this resource returned
														::IQ_PORTING_IO_ASYNC_PENDING. */
												
	IQ_PORTING_IOEVENT_READABLE,				/**<	The resource has become ready to accept reads.
														This event is generated if and only if a previous read call on this
														resource returned ::IQ_PORTING_IO_WOULDBLOCK. */

	IQ_PORTING_IOEVENT_READ_COMPLETE,			/**<	The previously initiated request to read data from this
														resource has completed.  The @a ioParam parameter of this
														::iq_io_callback_t contains the number of bytes that
														were successfully read into the I/O buffer that was
														specified in the original request.  This event is generated if
														and only if a previous read request on this resource returned
														::IQ_PORTING_IO_ASYNC_PENDING. */
										
	IQ_PORTING_IOEVENT_ERROR,					/**<	The resource has encountered an error that prevents it from
														completing a pending operation, or from ever again becoming ready	
														to accept reads or writes.  If a resource unexpectedly becomes
														unavailable at some point after ::IQ_PORTING_IO_WOULDBLOCK or
														::IQ_PORTING_IO_ASYNC_PENDING is returned from an I/O request
														but before the associated condition is satisfied, this event
														must be generated to inform the agent that the condition will never
														be statisfied and that the agent should cease any further use of
														this resource. */

	IQ_PORTING_IOEVENT_OPEN_COMPLETE,			/**<	The resource has completed a pending open operation.  This event
														must be generated at some point after an "open" operation returns
														::IQ_PORTING_IO_ASYNC_PENDING.  Note that asynchronous opens are
														only permitted for calls to IQPorting_BridgeMasterOpen() and
														IQPorting_BridgeSlaveOpen(). */

	IQ_PORTING_IOEVENT_NETWORK_BASE = 0x800,	/**<	The base I/O event value for network-related events,
														as defined in IQPortingNetwork.h. */
	IQ_PORTING_IOEVENT_SOCKET_BASE = 0x1000,	/**<	The base I/O event value for socket-related events,
														as defined in IQPortingSocket.h. */
	IQ_PORTING_IOEVENT_SMS_BASE		= 0x1800	/**<	The base I/O event value for SMS-related events,
														as defined in IQPortingSMS.h. */
};

/**
 * Prototype for a callback function that indicates an I/O event has occurred.
 * Functions that may perform non-blocking I/O operations use a callback of this type to
 * indicate events related to the associated resource.  For example, each socket created using
 * the functions in IQPortingSocket.h is provided with a callback function of this type to be
 * used to notify the agent of events related to that socket.  Like all other porting layer
 * callbacks, callbacks of this type may be invoked from any thread.
 * 
 * The @a callbackData parameter should be set to whatever @a callbackData was specified as in
 * the function that set up the callback.  The @a ioEvent parameter should be set to one of the
 * IQ_PORTING_IOEVENT_* values (::IQ_PORTING_IOEVENT_WRITABLE, ::IQ_PORTING_IOEVENT_READABLE, etc.)
 * that represents the event which has occurred.
 * 
 * @param	callbackData	the value specified as @a callbackData in the function which
 * 							specified the callback routine
 * @param	ioEvent			the IQ_PORTING_IOEVENT_* value that indicates what event occurred;
 * 							this can be one of the base I/O event values defined in this file
 * 							(IQPortingIO.h) or one of the resource-specific values defined by
 * 							that particular resource (for example, ::IQ_PORTING_IOEVENT_SOCKET_SERVER_CLOSED)
 * @param	ioParam			this value provides additional information about the I/O event that
 *							occurred.  If @a ioEvent is ::IQ_PORTING_IOEVENT_WRITE_COMPLETE or
 * 							::IQ_PORTING_IOEVENT_READ_COMPLETE, this must contain the number of bytes
 * 							that was (respectively) asynchronously written-to or read-from the resource
 * @param	ioError			if @a ioEvent is ::IQ_PORTING_IOEVENT_ERROR, this contains the error
 * 							result value that indicates the error that has occurred in relation to
 * 							the associated resource
 **/
typedef void (*iq_io_callback_t) (	void* callbackData,
									iq_io_event_t ioEvent,
									unsigned long ioParam, 
									iq_porting_status_t ioError );

//================================================================
// This file can be used in C or C++ environments.
//================================================================
#ifdef __cplusplus
}
#endif

#endif	// IQPortingIO_h
