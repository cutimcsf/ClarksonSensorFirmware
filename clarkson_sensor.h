/*
 * clarkson_sensor.h
 *
 *  Created on: Jan 20, 2023
 *      Author: tim
 */

#ifndef CLARKSON_SENSOR_H_
#define CLARKSON_SENSOR_H_

#include "sl_bt_api.h"

void handleUserWriteRequest(const sl_bt_evt_gatt_server_user_write_request_t * const request);

void handleUserReadRequest(const sl_bt_evt_gatt_server_user_read_request_t * const request);

#endif /* CLARKSON_SENSOR_H_ */
