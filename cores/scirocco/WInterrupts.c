/*
  Copyright (c) 2020 Tokita, Hiroshi  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <zephyr.h>
#include <gpio.h>
#include <variant.h>
#include "wiring_private.h"
#include "WInterrupts.h"

static uint32_t intConfig(uint32_t intmode)
{
    switch(intmode)
    {
    case LOW:
        return (GPIO_INT | GPIO_INT_LEVEL | GPIO_INT_ACTIVE_LOW);
    case HIGH:
        return (GPIO_INT | GPIO_INT_LEVEL | GPIO_INT_ACTIVE_HIGH);
    case CHANGE:
        return (GPIO_INT | GPIO_INT_EDGE  | GPIO_INT_DOUBLE_EDGE);
    case FALLING:
        return (GPIO_INT | GPIO_INT_EDGE  | GPIO_INT_ACTIVE_LOW);
    case RISING:
        return (GPIO_INT | GPIO_INT_EDGE  | GPIO_INT_ACTIVE_HIGH);
    }
    return 0;
}

void attachInterrupt(uint32_t pin, voidFuncPtr callback, uint32_t intmode)
{
    w_gpio_pin_callback_configure(device_get_binding(w_gpio_port_name(pin)), w_gpio_port_pin_no(pin), callback, UINT_MAX, intConfig(intmode), UINT_MAX);
}

void detachInterrupt(uint32_t pin)
{
    w_gpio_pin_callback_configure(device_get_binding(w_gpio_port_name(pin)), w_gpio_port_pin_no(pin), NULL, UINT_MAX, UINT_MAX, UINT_MAX);
}


