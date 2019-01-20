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
#include <uart.h>
#include "Uart.h"
#include "Arduino.h"
#include "wiring_private.h"


Uart::Uart(struct device *_s)
{
  uart = _s;
}

void Uart::begin(unsigned long baudrate)
{
	begin(baudrate, SERIAL_8N1);
}

void Uart::begin(unsigned long baud, uint16_t conf)
{
	begin_impl(baud, conf);
}

void Uart::begin_impl(unsigned long baud, uint16_t conf)
{
	//TODO newapi
	uart_irq_callback_user_data_set(uart, Uart::IrqDispatch, this);
	uart_irq_rx_enable(uart);
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
	uart_irq_update(uart);

	if (uart_irq_tx_ready(uart)) {
		data_transmitted = true;
	}

	int rxcount = uart_irq_rx_ready(uart);
	if(rxcount == 0) return;

	do {
		static uint8_t buf[32];
		int ret = uart_fifo_read(uart, buf, max(rxcount, 32) ); 
		if(ret) {
			for(int i=0; i<max(rxcount, 32); i++) {
				rxBuffer.store_char(buf[i]);
			}
		}
		rxcount = uart_irq_rx_ready(uart);
	} while(rxcount > 0);
}

void Uart::IrqDispatch(void* data)
{
	reinterpret_cast<Uart*>(data)->IrqHandler();
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

size_t Uart::write(const uint8_t *buffer, size_t size)
{
	uart_irq_tx_enable(uart);

	int len = size;
	while (len) {
		int written;

		data_transmitted = false;
		written = uart_fifo_fill(uart, buffer, len);
		while (data_transmitted == false) {
			k_yield();
		}

		len -= written;
		buffer += written;
	}

	uart_irq_tx_disable(uart);
	return 0;
}


size_t Uart::write(const uint8_t data)
{
	write(&data, 1);
	return 1;
}
