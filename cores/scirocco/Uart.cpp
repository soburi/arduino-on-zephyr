/*
  Copyright (c) 2015-2019 Tokita, Hiroshi  All right reserved.

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

Uart::Uart(struct device *_s)
{
	uart = _s;
	k_sem_init(&tx_sem, 1, 1);
	k_sem_init(&rx_sem, 1, 1);
}

void Uart::begin(unsigned long baudrate)
{
	begin(baudrate, SERIAL_8N1);
}

void Uart::begin(unsigned long baud, uint16_t conf)
{
	begin_impl(baud, conf);
}

static enum uart_config_parity conf_parity(uint16_t conf)
{
	switch(conf & HARDSER_PARITY_MASK)
	{
	case HARDSER_PARITY_EVEN:
		return UART_CFG_PARITY_EVEN;
	case HARDSER_PARITY_ODD:
		return UART_CFG_PARITY_ODD;
	default:
		return UART_CFG_PARITY_NONE;
	}
}

static enum uart_config_stop_bits conf_stop_bits(uint16_t conf)
{
	switch(conf & HARDSER_STOP_BIT_MASK)
	{
	case HARDSER_STOP_BIT_1_5:
		return UART_CFG_STOP_BITS_1_5;
	case HARDSER_STOP_BIT_2:
		return UART_CFG_STOP_BITS_2;
	default:
		return UART_CFG_STOP_BITS_1;
	}
}

static enum uart_config_data_bits conf_data_bits(uint16_t conf)
{
	switch(conf & HARDSER_DATA_MASK)
	{
	case HARDSER_DATA_5:
		return UART_CFG_DATA_BITS_5;
	case HARDSER_DATA_6:
		return UART_CFG_DATA_BITS_6;
	case HARDSER_DATA_7:
		return UART_CFG_DATA_BITS_7;
	default:
		return UART_CFG_DATA_BITS_8;
	}
}

void Uart::begin_impl(unsigned long baud, uint16_t conf)
{
	struct uart_config config = {
		.baudrate = baud,
		.parity = conf_parity(conf),
		.stop_bits = conf_stop_bits(conf),
		.data_bits = conf_data_bits(conf),
		.flow_ctrl = UART_CFG_FLOW_CTRL_NONE,
	};

	uart_configure(uart, &config);
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
	if(!uart_irq_update(uart)) {
		return;
	}

	if((txcount-txidx) <= 0 && txcount != 0) {
		txcount = 0;
		txidx = 0;
		uart_irq_tx_disable(uart);
	}

	if(uart_irq_rx_ready(uart) > 0) {
		k_sem_take(&rx_sem, K_NO_WAIT);

		uint8_t buf[32];
		int readcount = 1;
		while( (readcount = uart_fifo_read(uart, buf, sizeof(buf) ) ) > 0) {
			for(int i=0; i<readcount; i++) {
				rxBuffer.store_char(buf[i]);
			}
		}

		k_sem_give(&rx_sem);
	}
	else if (uart_irq_tx_ready(uart) ) {
		k_sem_take(&tx_sem, K_NO_WAIT);

		if ( (txcount-txidx) > 0) {
			int written = uart_fifo_fill(uart, const_cast<const u8_t*>(txbuffer)+txidx, txcount-txidx);
			txidx += written;
		}

		k_sem_give(&tx_sem);
	}
}

void Uart::IrqDispatch(void* data)
{
	reinterpret_cast<Uart*>(data)->IrqHandler();
}

int Uart::available()
{
	k_sem_take(&rx_sem, K_FOREVER);
	int ret = (uint32_t)(SERIAL_BUFFER_SIZE + rxBuffer._iHead - rxBuffer._iTail) % SERIAL_BUFFER_SIZE;
	k_sem_give(&rx_sem);

	return ret;
}

int Uart::availableForWrite()
{
	k_sem_take(&tx_sem, K_FOREVER);
	int ret = (sizeof(txbuffer) - txcount);
	k_sem_give(&tx_sem);

	return ret;
}

int Uart::peek()
{
	k_sem_take(&rx_sem, K_FOREVER);
	int ret = rxBuffer.peek();
	k_sem_give(&rx_sem);

	return ret;
}

int Uart::read()
{
	k_sem_take(&rx_sem, K_FOREVER);
	int ret = rxBuffer.read_char();
	k_sem_give(&rx_sem);

	return ret;
}

size_t Uart::write(const uint8_t *buffer, size_t size)
{
	k_sem_take(&tx_sem, K_FOREVER);

	size_t txsz = min(size, sizeof(txbuffer)-txcount);
	memcpy(txbuffer+txcount, buffer, txsz);
	txcount += txsz;

	k_sem_give(&tx_sem);

	uart_irq_tx_enable(uart);

	return txsz;
}

size_t Uart::write(const uint8_t data)
{
	return write(&data, 1);
}
