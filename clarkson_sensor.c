/*
 *  clarkson_sensor.c
 *
 *  Created on: January 21, 2023
 *      Author: Timothy C. Sweeney-Fanelli
 *              Affects AI
 *              tim@affects.ai
 *
 *  Utility methods for interfacing with the sensor via BLE.
 */


#include "clarkson_sensor.h"
#include "peripherals/lmp91000_afe.h"
#include "peripherals/dac.h"
#include "peripherals/battery.h"
#include "gatt_db.h"


#include <sl_bluetooth.h>

static uint16_t
parseValue (const uint8_t len, const uint8_t bytes[])
{
  int16_t value = 0;
  for (uint8_t i = len; i > 0; --i)
    {
      value += ((int16_t) bytes[i - 1]) << (8 * (i - 1));
    }

  return value;
}

void
handleUserWriteRequest (const sl_bt_evt_gatt_server_user_write_request_t * const request)
{
  switch (request->characteristic)
    {
    case gattdb_write_to_dac:
      DAC_writeValue (parseValue (request->value.len, request->value.data));
      break;

    case gattdb_device_configuration:
      DAC_writeValue(parseValue(2, &(request->value.data[0])));
      LMP91000_enableSensor(LMP91000_1);
      LMP91000_setTIACN_raw(request->value.data[2]);
      LMP91000_setRefCN_raw(request->value.data[3]);
      LMP91000_setOpMode_raw(request->value.data[4]);
      LMP91000_enableSensor(LMP91000_2);
      LMP91000_setTIACN_raw(request->value.data[5]);
      LMP91000_setRefCN_raw(request->value.data[6]);
      LMP91000_setOpMode_raw(request->value.data[7]);
      break;

    default:
      // Take no action, just let it pass through. There are system-level handlers
      // that the API will call next.
      break;
    }
}

void
handleUserReadRequest (const sl_bt_evt_gatt_server_user_read_request_t * const rsp)
{
  size_t sz = 0;
  uint8_t *p = NULL;
  uint16_t sent;

  uint32_t millivolts = 0;
  bool handled = true;

  uint8_t deviceConfigValue = 0;
  uint8_t deviceConfig[8] = {0};


  switch (rsp->characteristic)
    {
    case gattdb_battery_level:
      Battery_readAndFlushCurrentPowerLevel(0);
      millivolts = Battery_getCurrentLevel ();
      sz = sizeof(millivolts);
      p = (uint8_t*) &millivolts;
      break;

    case gattdb_device_configuration:
      deviceConfig[0] = DAC_getLastValueWritten() & 0x00FF;
      deviceConfig[1] = (DAC_getLastValueWritten() & 0xFF00) >> 8;

      LMP91000_enableSensor(LMP91000_1);
      LMP91000_getTIACN_raw(&deviceConfigValue);
      deviceConfig[2] = deviceConfigValue;
      LMP91000_getRefCN_raw(&deviceConfigValue);
      deviceConfig[3] = deviceConfigValue;
      LMP91000_getOpMode_raw(&deviceConfigValue);
      deviceConfig[4] = deviceConfigValue;

      LMP91000_enableSensor(LMP91000_2);
      LMP91000_getTIACN_raw(&deviceConfigValue);
      deviceConfig[5] = deviceConfigValue;
      LMP91000_getRefCN_raw(&deviceConfigValue);
      deviceConfig[6] = deviceConfigValue;
      LMP91000_getOpMode_raw(&deviceConfigValue);
      deviceConfig[7] = deviceConfigValue;

      sz = sizeof(deviceConfig);
      p = deviceConfig;
      break;

    default:
      // Take no action, just let it pass through. There are system-level handlers
      // that the API will call next.
      handled = false;
      break;
    }

  // If we handled it, then send the read response back to the caller.
  if (handled)
    {
      uint16_t status = 0;
      if (p == NULL)
        {
          status = 2566; // @TODO -- bg_err_application_incorrect_gatt_database;
          sz = 0;
        }

      sl_bt_gatt_server_send_user_read_response (rsp->connection,
                                                 rsp->characteristic, status,
                                                 sz, // size
                                                 p,   // pointer
                                                 &sent);
    }
}
