/*
  Copyright (c) 2015-2017 Tokita, Hiroshi  All right reserved.

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

#include "Arduino.h"
#include "variant.h"
#include "wiring_private.h"
#include <gpio.h>

#ifdef __cplusplus
extern "C" {
#endif


void pinMode( uint32_t ulPin, uint32_t ulMode )
{
	int mode = 0;
	switch(ulMode)
	{
	case INPUT:
		mode = GPIO_DIR_IN;
		break;
	case OUTPUT:
		mode = GPIO_DIR_OUT;
		break;
	case INPUT_PULLUP:
		mode = GPIO_DIR_IN | GPIO_PUD_PULL_UP;
		break;
	}

	gpio_configs[ulPin] = mode;

	gpio_pin_configure(device_get_binding(PIN2PORT(ulPin)), PIN2PORTPIN(ulPin), mode);
}


void digitalWrite( uint32_t ulPin, uint32_t ulVal )
{
	gpio_pin_write(device_get_binding(PIN2PORT(ulPin)), PIN2PORTPIN(ulPin), ulVal ? 1 : 0);
}


int digitalRead( uint32_t ulPin )
{
	u32_t value;
	gpio_pin_read(device_get_binding(PIN2PORT(ulPin)), PIN2PORTPIN(ulPin), &value);
	return value ? 1 : 0;
}

#ifdef __cplusplus
}
#endif


