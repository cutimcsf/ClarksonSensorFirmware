/*
 *  clarkson_sensor.h
 *
 *  Created on: January 21, 2023
 *      Author: Timothy C. Sweeney-Fanelli
 *              Affects AI
 *              tim@affects.ai
 *
 *  Utility methods for interfacing with the sensor via BLE.
 */


#ifndef CLARKSON_SENSOR_H_
#define CLARKSON_SENSOR_H_

#include <sl_bt_api.h>

/******************************************************************************
 * Handles GATT User Write Requests
 *****************************************************************************/
void handleUserWriteRequest(
    const sl_bt_evt_gatt_server_user_write_request_t * const request);

/******************************************************************************
 * Handles GATT User Read Requests
 *****************************************************************************/
void handleUserReadRequest(
    const sl_bt_evt_gatt_server_user_read_request_t * const request);

#endif /* CLARKSON_SENSOR_H_ */
