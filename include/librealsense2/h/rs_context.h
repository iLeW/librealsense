/* License: Apache 2.0. See LICENSE file in root directory.
   Copyright(c) 2017 Intel Corporation. All Rights Reserved. */

/** \file rs2_context.h
* \brief
* Exposes RealSense context functionality for C compilers
*/


#ifndef LIBREALSENSE_RS2_CONTEXT_H
#define LIBREALSENSE_RS2_CONTEXT_H

#ifdef __cplusplus
extern "C" {
#endif
#include "rs_types.h"

/**
* \brief Creates RealSense context that is required for the rest of the API.
* \param[in] api_version Users are expected to pass their version of \c RS2_API_VERSION to make sure they are running the correct librealsense version.
* \param[out] error  If non-null, receives any error that occurs during this call, otherwise, errors are ignored.
* \return            Context object
*/
rs2_context* rs2_create_context(int api_version, rs2_error** error);

/**
* \brief Frees the relevant context object.
* \param[in] context Object that is no longer needed
*/
void rs2_delete_context(rs2_context* context);

/**
* return the time at specific time point
* \param context     Object representing librealsense session
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
* \return            the time at specific time point, in live and record mode it will return the system time and in playback mode it will return the recorded time
*/
rs2_time_t rs2_get_context_time(const rs2_context* context, rs2_error** error);

/**
* set callback to get devices changed events
* these events will be raised by the context whenever new RealSense device is connected or existing device gets disconnected
* \param context     Object representing librealsense session
* \param[in] callback callback object created from c++ application. ownership over the callback object is moved into the context
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
*/
void rs2_set_devices_changed_callback_cpp(rs2_context* context, rs2_devices_changed_callback* callback, rs2_error** error);

/**
* stop raising events when the devices connected to the computer change.
* additionally, block the calling thread until all in-flight callbacks return.
* \param context     Object representing librealsense session
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
*/
void rs2_context_stop(rs2_context* context, rs2_error** error);

/**
* set callback to get devices changed events
* these events will be raised by the context whenever new RealSense device is connected or existing device gets disconnected
* \param context     Object representing librealsense session
* \param[in] callback function pointer to register as per-notifications callback
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
*/
void rs2_set_devices_changed_callback(rs2_context* context, rs2_devices_changed_callback_ptr callback, rs2_error** error);

/**
 * Create a new device and add it to the context
 * \param ctx   The context to which the new device will be added
 * \param file  The file from which the device should be created
 * \param[out] error     If non-null, receives any error that occurs during this call, otherwise, errors are ignored
 * @return  A pointer to a device that plays data from the file, or null in case of failure
 */
rs2_device* rs2_context_add_device(rs2_context* ctx, const char* file, rs2_error** error);

/**
 * Removes a playback device from the context, if exists
 * \param[in]  ctx       The context from which the device should be removed
 * \param[in]  file      The file name that was used to add the device
 * \param[out] error     If non-null, receives any error that occurs during this call, otherwise, errors are ignored
 */
void rs2_context_remove_device(rs2_context* ctx, const char* file, rs2_error** error);

/**
* create a static snapshot of all connected devices at the time of the call
* \param context     Object representing librealsense session
* \param[out] error  if non-null, receives any error that occurs during this call, otherwise, errors are ignored
* \return            the list of devices, should be released by rs2_delete_device_list
*/
rs2_device_list* rs2_query_devices(const rs2_context* context, rs2_error** error);

#ifdef __cplusplus
}
#endif
#endif
