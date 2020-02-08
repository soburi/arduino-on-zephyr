/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.
  Copyright (c) 2015-2019 Tokita, Hiroshi

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

#include <zephyr.h>
#include <uart.h>
#include "HardwareSerial.h"
#include "RingBuffer.h"

#include <stddef.h>

class Uart : public HardwareSerial
{
  public:
    Uart(struct device *_s);
    void begin(unsigned long baudRate);
    void begin(unsigned long baudrate, uint16_t config);
    void end();
    int available();
    int availableForWrite();
    int peek();
    int read();
    void flush();
    size_t write(const uint8_t data);
    size_t write(const uint8_t *buffer, size_t size);

    using Print::write; // pull in write(str) and write(buf, size) from Print

    void IrqHandler();

    operator bool() { return true; }

  protected:
    virtual void begin_impl(unsigned long baudrate, uint16_t config);
    static void IrqDispatch(void* data);
    struct device *uart;

  private:
    RingBuffer rxBuffer;
    uint8_t txbuffer[255];
    int txidx;
    int txcount;

    struct k_sem tx_sem;
    struct k_sem rx_sem;
#if 0

    uint8_t uc_pinRX;
    uint8_t uc_pinTX;
    SercomRXPad uc_padRX;
    SercomUartTXPad uc_padTX;

    SercomNumberStopBit extractNbStopBit(uint8_t config);
    SercomUartCharSize extractCharSize(uint8_t config);
    SercomParityMode extractParity(uint8_t config);
#endif
};

#endif
