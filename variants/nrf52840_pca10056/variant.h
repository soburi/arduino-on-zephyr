/*
  Copyright (c) 2015-2018 Tokita, Hiroshi  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _VARIANT_NRF52840PCA10056_
#define _VARIANT_NRF52840PCA10056_

#ifdef __cplusplus
#include "UartDevice.h"
#endif // __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


#define GPIO_PORT_NAMES	{ DT_GPIO_P0_DEV_NAME, DT_GPIO_P1_DEV_NAME }

#define W_PWM_DEV_NAME(x) DT_NORDIC_NRF_PWM_0_LABEL

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

/*
 * digitalPinToTimer(..) is AVR-specific and is not defined for SAMD
 * architecture. If you need to check if a pin supports PWM you must
 * use digitalPinHasPWM(..).
 *
 * https://github.com/arduino/Arduino/issues/1833
 */
// #define digitalPinToTimer(P)

// LEDs
#define PIN_LED1             (13)
#define PIN_LED2             (14)
#define PIN_LED3             (15)
#define PIN_LED4             (16)
#define LED_BUILTIN          PIN_LED1

/*
 * Analog pins
 */
#define PIN_A1 (3)
#define PIN_A2 (4)
#define PIN_A3 (28)
#define PIN_A4 (29)
#define PIN_A5 (30)
#define PIN_A6 (31)

static const uint8_t A0   = PIN_A1;
static const uint8_t A1   = PIN_A2;
static const uint8_t A2   = PIN_A3;
static const uint8_t A3   = PIN_A4;
static const uint8_t A5   = PIN_A5;
static const uint8_t A6   = PIN_A6;

/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 1

#define PIN_SPI_MISO  (21)
#define PIN_SPI_MOSI  (20)
#define PIN_SPI_SCK   (19)
#define PIN_SPI_SS    (17)

static const uint8_t MOSI = PIN_SPI_MOSI ;
static const uint8_t MISO = PIN_SPI_MISO ;
static const uint8_t SCK  = PIN_SPI_SCK ;
static const uint8_t SS   = PIN_SPI_SS ;

extern struct spi_device spi0;
#define SPI_INTERFACE        (&spi0)

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 1

#define PIN_WIRE_SDA  (26)
#define PIN_WIRE_SCL  (27)

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

extern struct i2c_device i2c0;
#define WIRE_INTERFACE       (device_get_binding(DT_I2C_0_NAME))

#define VARIANT_MCK                     84000000


#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus

/*	=========================
 *	===== SERCOM DEFINITION
 *	=========================
*/
#define HAS_UART_0
#define HAS_UART_1

extern Uart& Serial;
#ifdef HAS_UART_0
extern Uart Serial0;
#endif
#ifdef HAS_UART_1
extern Uart Serial1;
#endif

#endif

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
//#define SERIAL_PORT_USBVIRTUAL      SerialUSB
#define SERIAL_PORT_MONITOR         Serial
#define SERIAL_PORT_HARDWARE_OPEN   Serial1
//#define SERIAL_PORT_HARDWARE_OPEN1  Serial2
//#define SERIAL_PORT_HARDWARE_OPEN2  Serial3
#define SERIAL_PORT_HARDWARE        Serial
#define SERIAL_PORT_HARDWARE1       Serial1
//#define SERIAL_PORT_HARDWARE2       Serial2
//#define SERIAL_PORT_HARDWARE3       Serial3

#endif /* _VARIANT_JN516X_ */

