/*
 * clarkson_sensor.c
 *
 *  Created on: Jan 20, 2023
 *      Author: tim
 */

#include "clarkson_sensor.h"
#include "peripherals/dac.h"
#include "peripherals/battery.h"

#include "sl_bluetooth.h"
#include "gatt_db.h"

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

  switch (rsp->characteristic)
    {
    case gattdb_battery_level:
      Battery_updatePowerLevel(0);
      millivolts = Battery_getCurrentLevel ();
      sz = sizeof(millivolts);
      p = (uint8_t*) &millivolts;
      break;

    default:
      handled = false;
    }

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
