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

#include "wiring_private.h"
#include <zephyr.h>
#include <gpio.h>



static voidFuncPtr callbacks[GPIO_PIN_NO];

void gpio_handler(struct device *port, struct gpio_callback *cb, u32_t pins)
{
	for(int i=0; i<32; i++)
	{
		if(pins & (1<<i)) callbacks[i]();
	}
}

void attachInterrupt(uint32_t pin, voidFuncPtr callback, uint32_t mode)
{
	int pinconf = gpio_configs[pin];
	if(gpio_configs[pin] & 0xF000)
	{
		pinconf = GPIO_DIR_IN;
	}

	pinconf |= GPIO_INT;
	switch(mode)
	{
	case LOW:
		pinconf |= (GPIO_INT_LEVEL | GPIO_INT_ACTIVE_LOW);
	case HIGH:
		pinconf |= (GPIO_INT_LEVEL | GPIO_INT_ACTIVE_HIGH);
	case CHANGE:
		pinconf |= (GPIO_INT_EDGE  | GPIO_INT_DOUBLE_EDGE);
	case FALLING:
		pinconf |= (GPIO_INT_EDGE  | GPIO_INT_ACTIVE_LOW);
	case RISING:
		pinconf |= (GPIO_INT_EDGE  | GPIO_INT_ACTIVE_HIGH);
	}

	gpio_configs[pin] = pinconf;
	callbacks[pin] = callback;

	gpio_pin_configure(device_get_binding(PIN2PORT(pin)), PIN2PORTPIN(pin), pinconf);
	gpio_init_callback(&gpio_cb[pin], gpio_handler, BIT(PIN2PORTPIN(pin)));
	gpio_add_callback(device_get_binding(PIN2PORT(pin)), &gpio_cb[pin]);
	gpio_pin_enable_callback(device_get_binding(PIN2PORT(pin)), pin);

}

void detachInterrupt(uint32_t pin)
{
	gpio_remove_callback(device_get_binding(PIN2PORT(pin)), &gpio_cb[pin]);
	gpio_pin_disable_callback(device_get_binding(PIN2PORT(pin)), pin);
}


