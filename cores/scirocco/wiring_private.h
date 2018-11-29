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

#include "WInterrupts.h"
#include "wiring_constants.h"
#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif
extern int gpio_configs[GPIO_PIN_NO];

extern struct gpio_callback gpio_cb[GPIO_PIN_NO];

struct uart_device {
	int     (*input)( uint8_t c);
	void    (*init)(void*, uint32_t, uint8_t, uint8_t, uint8_t, uint8_t);
	void    (*set_input)(void*, int (*input)(unsigned char));
	void    (*writeb)(void*, unsigned char);
	uint8_t (*busy)(void*);
	int	(*txbuffer_availables)(void*);
	void    (*deinit)(void*);
	void*	portinfo;
	uint8_t received;
};

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
