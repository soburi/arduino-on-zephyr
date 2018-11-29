/*
 * TWI/I2C library for Arduino Zero
 * Copyright (c) 2015 Arduino LLC. All rights reserved.
 * Copyright (c) 2015-2018 Tokita, Hiroshi
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef TwoWire_h
#define TwoWire_h

#include "Stream.h"
#include "variant.h"


#include "RingBuffer.h"

#include <device.h>
#include <i2c.h>

 // WIRE_HAS_END means Wire has end()
#define WIRE_HAS_END 1

class TwoWire : public Stream
{
  public:
    TwoWire(struct device *i2cdev);
    void begin();
    void begin(uint8_t, bool enableGeneralCall = false);
    void end();
    void setClock(uint32_t);

    void beginTransmission(uint8_t);
    uint8_t endTransmission(bool stopBit);
    uint8_t endTransmission(void);

    uint8_t requestFrom(uint8_t address, size_t quantity, bool stopBit);
    uint8_t requestFrom(uint8_t address, size_t quantity);

    size_t write(uint8_t data);
    size_t write(const uint8_t * data, size_t quantity);

    virtual int available(void);
    virtual int read(void);
    virtual int peek(void);
    virtual void flush(void);
    void onReceive(void(*)(int));
    void onRequest(void(*)(void));

    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write;

  private:
    struct device* i2c;
    uint32_t clock;
    bool master_mode;

    bool transmissionBegun;
    uint8_t txAddress;

    // Callback user functions
    void (*onRequestCallback)(void);
    void (*onReceiveCallback)(int);

    RingBufferN<SERIAL_BUFFER_SIZE> rxBuf;
    RingBufferN<SERIAL_BUFFER_SIZE> txBuf;

    bool request_received;
    bool data_received;

    struct i2c_slave_config slave_config;

    static int dispatch_write_requested(struct i2c_slave_config *config);
    static int dispatch_read_requested(struct i2c_slave_config *config, u8_t *val);
    static int dispatch_write_received(struct i2c_slave_config *config, u8_t *val);
    static int dispatch_read_processed(struct i2c_slave_config *config, u8_t *val);
    static int dispatch_stop(struct i2c_slave_config *config); 
    
    int onWriteRequested(struct i2c_slave_config *config);
    int onReadRequested(struct i2c_slave_config *config, u8_t *val);
    int onWriteReceived(struct i2c_slave_config *config, u8_t *val);
    int onReadProcessed(struct i2c_slave_config *config, u8_t *val);
    int onStop(struct i2c_slave_config *config);

    // TWI clock frequency
    static const uint32_t TWI_CLOCK = 100000;
};

#if WIRE_INTERFACES_COUNT > 0
  extern TwoWire Wire;
#endif
#if WIRE_INTERFACES_COUNT > 1
  extern TwoWire Wire1;
#endif
#if WIRE_INTERFACES_COUNT > 2
  extern TwoWire Wire2;
#endif
#if WIRE_INTERFACES_COUNT > 3
  extern TwoWire Wire3;
#endif
#if WIRE_INTERFACES_COUNT > 4
  extern TwoWire Wire4;
#endif
#if WIRE_INTERFACES_COUNT > 5
  extern TwoWire Wire5;
#endif

#endif
