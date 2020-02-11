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
#include "variant.h"
#include "wiring_private.h"
#include "wiring_digital.h"

static uint32_t pinConfig(uint32_t pinmode)
{
    switch(pinmode)
    {
    //case OUTPUT:
    case INPUT:
        return GPIO_DIR_IN;
    case INPUT_PULLUP:
        return GPIO_DIR_IN | GPIO_PUD_PULL_UP;
    case INPUT_PULLDOWN:
        return GPIO_DIR_IN | GPIO_PUD_PULL_DOWN;
    }
    return GPIO_DIR_OUT;
}

void pinMode( uint32_t dwPin, uint32_t dwMode )
{
    w_gpio_pin_callback_configure(device_get_binding(w_gpio_port_name(dwPin)), w_gpio_port_pin_no(dwPin), NULL, pinConfig(dwMode), UINT_MAX, UINT_MAX);
}

void digitalWrite( uint32_t ulPin, uint32_t ulVal )
{
    gpio_pin_write(device_get_binding(w_gpio_port_name(ulPin)), w_gpio_port_pin_no(ulPin), ulVal ? 1 : 0);
}

int digitalRead( uint32_t ulPin )
{
    uint32_t value;
    gpio_pin_read(device_get_binding(w_gpio_port_name(ulPin)), w_gpio_port_pin_no(ulPin), &value);
    return value ? 1 : 0;
}

