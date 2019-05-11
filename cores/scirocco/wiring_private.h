/*
  Copyright (c) 2014-2018 Tokita, Hiroshi  All right reserved.

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

#pragma once

#include <zephyr.h>
#include <gpio.h>

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "wiring_constants.h"
#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef W_GPIO_PINS_PER_PORT
#define W_GPIO_PINS_PER_PORT 32
#endif

#ifndef W_GPIO_PORT_NUM
#define W_GPIO_PORT_NUM (sizeof(gpio_port_names)/sizeof(const char*))
#endif

#ifndef W_PIN2PORT
#define W_PIN2PORT(x) (gpio_port_names[x / W_GPIO_PINS_PER_PORT])
#endif

#ifndef W_PIN2PORTPIN
#define W_PIN2PORTPIN(x) (x % W_GPIO_PINS_PER_PORT)
#endif

#ifndef W_GPIO_PIN_NUM
#define W_GPIO_PIN_NUM (W_GPIO_PINS_PER_PORT * W_GPIO_PORT_NUM)
#endif

#ifndef W_PWM_DEV_NAME
#define W_PWM_DEV_NAME(x) NULL
#endif

typedef void (*voidFuncPtr)(void);

struct w_gpio_callbacks {
	struct gpio_callback z_callback;
	voidFuncPtr callback;
};

static const char* gpio_port_names[] = GPIO_PORT_NAMES;

extern int w_pin_mode[W_GPIO_PIN_NUM];
extern struct w_gpio_callbacks w_callbacks[W_GPIO_PIN_NUM];

extern void w_digital_write( uint32_t ulPin, uint32_t ulVal );
extern int w_digital_read( uint32_t ulPin );
extern void w_attach_interrupt(uint32_t pin, voidFuncPtr callback, uint32_t mode);
extern void w_detach_interrupt(uint32_t pin);

extern void w_configure_gpio_interrupt(uint32_t pin, voidFuncPtr callback, uint32_t mode, uint32_t pinmode, uint32_t extraflag);


struct spi_device {
	int     (*init)(void*);
	int	(*configure)(void*, bool, bool, bool, uint32_t);
	int	(*start)(void*);
	void	(*stop)(void*);
	uint8_t (*transfer)(void*, uint8_t);
	int	(*mask_interrupt_on_transaction)(void*, int);
	int     (*deinit)(void*);
	void*	devinfo;
};

#ifdef __cplusplus
} // extern "C"
#endif
