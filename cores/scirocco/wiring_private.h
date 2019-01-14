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

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <zephyr.h>

#include "WInterrupts.h"
#include "wiring_constants.h"

#include <gpio.h>

extern int* gpio_configs;

extern struct gpio_callback* gpio_cb;

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


struct i2c_device {
	int     (*init)(void*);
	int	(*master_enable)(void*, uint32_t);
	int	(*slave_enable)(void*, uint8_t);
	void    (*disable)(void*);
	int	(*master_start)(void*, uint8_t, int);
	int	(*master_read)(void*, size_t);
	int	(*master_write)(void*);
	void	(*master_stop)(void*);
	int	(*slave_write)(void*);
	int	(*rx_available)(void*);
	void	(*rx_clear)(void*);
	int	(*rx_read)(void*);
	int	(*rx_peek)(void*);
	int	(*tx_available)(void*);
	void	(*tx_clear)(void*);
	int	(*tx_put)(void*, uint8_t);
	int	(*tx_full)(void*);
	int	(*request_received)(void*);
	int	(*data_received)(void*);
	void*	devinfo;
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
