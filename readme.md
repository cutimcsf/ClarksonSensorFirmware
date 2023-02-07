# Clarkson Sensor Firmware

Based on the Bluetooth SoC-Empty example project. To work with this project, be sure you have the following installed:

1) Simplicity Studio v5 (https://www.silabs.com/developers/simplicity-studio)
2) Gecko SDK 4.2.1 (will be installed by Simplicity Studio)
3) GCC Toolchain 10.2.1 (will be installed by Simplicity Studio)

After you have SS5 installed and configured, and have cloned this repository, follow this quick start video to get up and running:

https://user-images.githubusercontent.com/109687210/217389954-88de5d0e-673a-4099-86e3-dc7ea5802ba0.mov

Contact Tim (tfanelli@clarkson.edu) if you need help getting set up. 

## Code Layout
app.h/app.c and clarkson_sensor.h/clarkson_sensor.c contain all the logic for BLE interactions

Code to interface with the ADC, DAC, LMP91000, read the battery voltage, and interact with the accelerometer are all in the peripherals/ subfolder (note, I haven't started the accelerometer code yet, but it's just an SPI interface same as the DAC and the SPI peripheral is already configured)

## Getting Started with Firmware Development for the EFR32 Microcontroller

To learn the Bluetooth technology basics, see [UG103.14: Bluetooth LE Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-14-fundamentals-ble.pdf).

To get started with Silicon Labs Bluetooth and Simplicity Studio, see [QSG169: Bluetooth SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf).

To learn more about programming an SoC application, see [UG434: Silicon Labs Bluetooth ® C Application Developer's Guide for SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug434-bluetooth-c-soc-dev-guide-sdk-v3x.pdf).

To learn how to use the GATT Configurator, see [UG438: GATT Configurator User’s Guide for Bluetooth SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug438-gatt-configurator-users-guide-sdk-v3x.pdf).

## Resources

[LMP91000 AFE DataSheet](https://www.ti.com/lit/ds/symlink/lmp91000.pdf)

[DAC8830 DataSheet](https://www.ti.com/lit/ds/symlink/dac8830.pdf)

[ADXL362 DataSheet](https://www.analog.com/media/en/technical-documentation/data-sheets/ADXL362.pdf)

[QSG169: Bluetooth SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf)

[UG434: Silicon Labs Bluetooth ® C Application Developer's Guide for SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug434-bluetooth-c-soc-dev-guide-sdk-v3x.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)

## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://www.silabs.com/community).




