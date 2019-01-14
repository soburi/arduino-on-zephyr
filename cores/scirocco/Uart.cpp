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

#include <zephyr.h>
#include "include/uart.h"
#include "Uart.h"
#include "Arduino.h"
#include "wiring_private.h"

Uart::Uart(struct device *_s)
{
  uart = device_get_binding("");
}

void Uart::begin(unsigned long baudrate)
{
	begin(baudrate, SERIAL_8N1);
}

void Uart::begin(unsigned long baudrate, uint16_t config)
{
}

void Uart::end()
{
	flush();
	//uart->deinit(uart->portinfo);
}

void Uart::flush()
{
	//while (uart_irq_tx_complete(uart) );
}

void Uart::IrqHandler()
{
	unsigned char c;
	int ret = 0;//uart_fifo_read(uart, &c, 1); 
	if(ret) {
		rxBuffer.store_char(c);
	}
}

int Uart::available()
{
	return (uint32_t)(SERIAL_BUFFER_SIZE + rxBuffer._iHead - rxBuffer._iTail) % SERIAL_BUFFER_SIZE;
}

int Uart::availableForWrite()
{
	return 0;//return uart->txbuffer_availables(uart->portinfo);
}

int Uart::peek()
{
	return rxBuffer.peek();
}

int Uart::read()
{
	return rxBuffer.read_char();
}

size_t Uart::write(const uint8_t data)
{
	//uart_poll_out(uart, data);
	return 1;
}
