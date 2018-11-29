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

extern "C" {
#include <string.h>
void WIRE_IT_HANDLER();
void WIRE1_IT_HANDLER();
void WIRE2_IT_HANDLER();
void WIRE3_IT_HANDLER();
void WIRE4_IT_HANDLER();
void WIRE5_IT_HANDLER();
}

#include <Arduino.h>
#include <wiring_private.h>

#include "Wire.h"

#include <i2c.h>

#ifndef I2C_STANDARD_CLOCK
#define I2C_STANDARD_CLOCK   100000U
#endif
#ifndef I2C_FAST_CLOCK
#define I2C_FAST_CLOCK       400000U
#endif
#ifndef I2C_FAST_PLUS_CLOCK
#define I2C_FAST_PLUS_CLOCK 1000000U
#endif
#ifndef I2C_HIGH_CLOCK
#define I2C_HIGH_CLOCK      3400000U
#endif
#ifndef I2C_ULTRA_CLOCK
#define I2C_ULTRA_CLOCK     5000000U
#endif

#define I2C_CLOCK2SPEED(clk) (\
	clk <= I2C_STANDARD_CLOCK    ? I2C_SPEED_STANDARD : ( \
         clk <= I2C_FAST_CLOCK       ? I2C_SPEED_FAST : ( \
	  clk <= I2C_FAST_PLUS_CLOCK ? I2C_SPEED_FAST_PLUS : ( \
	   clk <= I2C_HIGH_CLOCK     ? I2C_SPEED_HIGH : ( \
		                       I2C_SPEED_ULTRA) ) ) ) )

#define I2C_CONF(clock, master) (I2C_SPEED_SET(I2C_CLOCK2SPEED(clock)) | (master ? I2C_MODE_MASTER : 0))

static inline int i2c_read_x(struct device *dev, u8_t *buf,
			   u32_t num_bytes, u16_t addr, bool stop)
{
        //printk("i2c_read_x %d\n", num_bytes);
	struct i2c_msg msg;

	msg.buf = buf;
	msg.len = num_bytes;
	msg.flags = I2C_MSG_READ | ( stop ? I2C_MSG_STOP : 0);

	return i2c_transfer(dev, &msg, 1, addr);
}
static inline int i2c_write_x(struct device *dev, u8_t *buf,
			    u32_t num_bytes, u16_t addr, bool stop)
{
        //printk("i2c_write_x %d\n", num_bytes);
	struct i2c_msg msg;

	msg.buf = buf;
	msg.len = num_bytes;
	msg.flags = I2C_MSG_WRITE | (stop ? I2C_MSG_STOP : 0);

        //printk("i2c_write_x i2c_transfer\n");
	return i2c_transfer(dev, &msg, 1, addr);
}

enum
{
  WIRE_WRITE_FLAG = 0x0ul,
  WIRE_READ_FLAG
};

static void nop_reqcb()
{
}
static void nop_recvcb(int x)
{
  (void)x;
}

TwoWire::TwoWire(struct device*_twi)
  : i2c(_twi)
  , clock(TWI_CLOCK)
  , onRequestCallback(nop_reqcb)
  , onReceiveCallback(nop_recvcb)
  , rxBuf()
  , txBuf()
  , request_received(false)
  , data_received(false)
{
}

void TwoWire::begin(void) {
  i2c_configure(i2c, I2C_CONF(clock, true));
  master_mode = true;
}

void TwoWire::begin(uint8_t address, bool enableGeneralCall) {
  slave_config.address = address;
  slave_config.flags = 0;
  i2c_configure(i2c, I2C_CONF(clock, false));
  //i2c_slave_register(i2c, &slave_config);
  master_mode = false;
  transmissionBegun = true;
}

void TwoWire::setClock(uint32_t frequency) {
  clock = frequency;
  if(master_mode)
  {
    i2c_configure(i2c, I2C_CONF(clock, true));
  }
}

void TwoWire::end() {
}

uint8_t TwoWire::requestFrom(uint8_t address, size_t quantity, bool stopBit)
{
  if(quantity == 0)
  {
    return 0;
  }

  size_t byteRead = 0;

  rxBuf.clear();

  // clamp to buffer length
  if(quantity > SERIAL_BUFFER_SIZE)
  {
    quantity = SERIAL_BUFFER_SIZE;
  }

//  if(i2c->master_start(i2c->devinfo, address, WIRE_READ_FLAG))
//  {
    u8_t rbuf[SERIAL_BUFFER_SIZE] = {0};
    //printk("call i2c_read_x\n");
    int ret = i2c_read_x(i2c, rbuf, quantity, address, stopBit);
    //printk("i2c_read_x ret=%d\n", byteRead);
    if(ret){
      return 0;
    }
    byteRead = quantity;
    for(uint32_t i=0; i<byteRead; i++)
    {
      rxBuf.store_char(rbuf[i]);
    }
//    if (stopBit)
//    {
//      i2c->master_stop(i2c->devinfo);   // Send Stop
//    }
//  }

  return byteRead;
}

uint8_t TwoWire::requestFrom(uint8_t address, size_t quantity)
{
  return requestFrom(address, quantity, true);
}

void TwoWire::beginTransmission(uint8_t address) {
  // save address of target and clear buffer
  txAddress = address;
  txBuf.clear();

  transmissionBegun = true;
}

// Errors:
//  0 : Success
//  1 : Data too long
//  2 : NACK on transmit of address
//  3 : NACK on transmit of data
//  4 : Other error
uint8_t TwoWire::endTransmission(bool stopBit)
{
  transmissionBegun = false ;

  // Start I2C transmission
//  if ( !i2c->master_start(i2c->devinfo, txAddress, WIRE_WRITE_FLAG ) )
//  {
//    i2c->master_stop(i2c->devinfo);
//    return 2 ;  // Address error
//  }

  // Send all buffer
  if(txBuf.available() )
  {
    uint8_t buf[SERIAL_BUFFER_SIZE] = {0};
    size_t len = 0;

    while(txBuf.available())
    {
       buf[len++] = txBuf.read_char();
    }

    int ret = i2c_write_x(i2c, buf, len, txAddress, stopBit);
    if(ret)
    {
      return 4;
    }

    //txBuffer always start 0.
//    if( i2c->master_write(i2c->devinfo) )
//    {
//      i2c->master_stop(i2c->devinfo);
//      return 3 ;  // Nack or error
//    }
  }
  
//  if (stopBit)
//  {
//    i2c->master_stop(i2c->devinfo);
//  }   

  return 0;
}

uint8_t TwoWire::endTransmission()
{
  return endTransmission(true);
}

size_t TwoWire::write(uint8_t ucData)
{
  // No writing, without begun transmission or a full buffer
  if ( !transmissionBegun || txBuf.isFull() )
  {
    setWriteError();
    return 0 ;
  }

  txBuf.store_char(ucData);
  
  if(master_mode == false)
  {
    //printk("i2c_write\n");
    i2c_write(i2c, &ucData, 1, slave_config.address);
  }

  return 1 ;
}

size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
  //Try to store all data
  for(size_t i = 0; i < quantity; ++i)
  {
    txBuf.store_char(data[i]);
  }

  if(master_mode == false)
  {
    i2c_write(i2c, const_cast<uint8_t*>(data), quantity, slave_config.address);
  }
  //All data stored
  return quantity;
}

int TwoWire::available(void)
{
  return rxBuf.available();
}

int TwoWire::read(void)
{
  return rxBuf.read_char();
}

int TwoWire::peek(void)
{
  return rxBuf.peek();
}

void TwoWire::flush(void)
{
  // Do nothing, use endTransmission(..) to force
  // data transfer.
}

void TwoWire::onReceive(void(*function)(int))
{
  onReceiveCallback = function;
}

void TwoWire::onRequest(void(*function)(void))
{
  onRequestCallback = function;
}

int TwoWire::onWriteRequested(struct i2c_slave_config *config)
{
  onRequestCallback();
  return 0;
}

int TwoWire::onReadRequested(struct i2c_slave_config *config, u8_t *val)
{
  onRequestCallback();
  return 0;
}

int TwoWire::onWriteReceived(struct i2c_slave_config *config, u8_t *val)
{
  onReceiveCallback(*val);
  return 0;
}

int TwoWire::onReadProcessed(struct i2c_slave_config *config, u8_t *val)
{
  return 0;
}

int TwoWire::onStop(struct i2c_slave_config *config)
{
  return 0;
}

#if WIRE_INTERFACES_COUNT > 0
  TwoWire Wire = TwoWire(WIRE_INTERFACE);
#endif

#if WIRE_INTERFACES_COUNT > 1
  TwoWire Wire1(WIRE_INTERFACE1);
#endif

#if WIRE_INTERFACES_COUNT > 2
  TwoWire Wire2(&PERIPH_WIRE2, PIN_WIRE2_SDA, PIN_WIRE2_SCL);
#endif

#if WIRE_INTERFACES_COUNT > 3
  TwoWire Wire3(&PERIPH_WIRE3, PIN_WIRE3_SDA, PIN_WIRE3_SCL);
#endif

#if WIRE_INTERFACES_COUNT > 4
  TwoWire Wire4(&PERIPH_WIRE4, PIN_WIRE4_SDA, PIN_WIRE4_SCL);
#endif

#if WIRE_INTERFACES_COUNT > 5
  TwoWire Wire5(&PERIPH_WIRE5, PIN_WIRE5_SDA, PIN_WIRE5_SCL);
#endif

int TwoWire::dispatch_write_requested(struct i2c_slave_config *config)
{
#if WIRE_INTERFACES_COUNT > 0
  if(&Wire.slave_config == config)  return Wire.onWriteRequested(config);
#endif
#if WIRE_INTERFACES_COUNT > 1
  if(&Wire1.slave_config == config) return Wire1.onWriteRequested(config);
#endif
#if WIRE_INTERFACES_COUNT > 2
  if(&Wire2.slave_config == config) return Wire2.onWriteRequested(config);
#endif
#if WIRE_INTERFACES_COUNT > 3
  if(&Wire3.slave_config == config) return Wire3.onWriteRequested(config);
#endif
#if WIRE_INTERFACES_COUNT > 4
  if(&Wire4.slave_config == config) return Wire4.onWriteRequested(config);
#endif
#if WIRE_INTERFACES_COUNT > 5
  if(&Wire5.slave_config == config) return Wire5.onWriteRequested(config);
#endif
  return 0;
}

int TwoWire::dispatch_read_requested(struct i2c_slave_config *config, u8_t *val)
{
#if WIRE_INTERFACES_COUNT > 0
  if(&Wire.slave_config == config)  return Wire.onReadRequested(config, val);
#endif
#if WIRE_INTERFACES_COUNT > 1
  if(&Wire1.slave_config == config) return Wire1.onReadRequested(config, val);
#endif
#if WIRE_INTERFACES_COUNT > 2
  if(&Wire2.slave_config == config) return Wire2.onReadRequested(config, val);
#endif
#if WIRE_INTERFACES_COUNT > 3
  if(&Wire3.slave_config == config) return Wire3.onReadRequested(config, val);
#endif
#if WIRE_INTERFACES_COUNT > 4
  if(&Wire4.slave_config == config) return Wire4.onReadRequested(config, val);
#endif
#if WIRE_INTERFACES_COUNT > 5
  if(&Wire5.slave_config == config) return Wire5.onReadRequested(config, val);
#endif
  return 0;

}

int TwoWire::dispatch_write_received(struct i2c_slave_config *config, u8_t* val)
{
#if WIRE_INTERFACES_COUNT > 0
  if(&Wire.slave_config == config)  return Wire.onWriteReceived(config, val);
#endif
#if WIRE_INTERFACES_COUNT > 1
  if(&Wire1.slave_config == config) return Wire1.onWriteReceived(config, val);
#endif
#if WIRE_INTERFACES_COUNT > 2
  if(&Wire2.slave_config == config) return Wire2.onWriteReceived(config, val);
#endif
#if WIRE_INTERFACES_COUNT > 3
  if(&Wire3.slave_config == config) return Wire3.onWriteReceived(config, val);
#endif
#if WIRE_INTERFACES_COUNT > 4
  if(&Wire4.slave_config == config) return Wire4.onWriteReceived(config, val);
#endif
#if WIRE_INTERFACES_COUNT > 5
  if(&Wire5.slave_config == config) return Wire5.onWriteReceived(config, val);
#endif
  return 0;
}
int TwoWire::dispatch_read_processed(struct i2c_slave_config *config, u8_t *val)
{
#if WIRE_INTERFACES_COUNT > 0
  if(&Wire.slave_config == config)  return Wire.onReadProcessed(config, val);
#endif
#if WIRE_INTERFACES_COUNT > 1
  if(&Wire1.slave_config == config) return Wire1.onReadProcessed(config, val);
#endif
#if WIRE_INTERFACES_COUNT > 2
  if(&Wire2.slave_config == config) return Wire2.onReadProcessed(config, val);
#endif
#if WIRE_INTERFACES_COUNT > 3
  if(&Wire3.slave_config == config) return Wire3.onReadProcessed(config, val);
#endif
#if WIRE_INTERFACES_COUNT > 4
  if(&Wire4.slave_config == config) return Wire4.onReadProcessed(config, val);
#endif
#if WIRE_INTERFACES_COUNT > 5
  if(&Wire5.slave_config == config) return Wire5.onReadProcessed(config, val);
#endif
  return 0;

}
int TwoWire::dispatch_stop(struct i2c_slave_config *config)
{
#if WIRE_INTERFACES_COUNT > 0
  if(&Wire.slave_config == config)  return Wire.onStop(config);
#endif
#if WIRE_INTERFACES_COUNT > 1
  if(&Wire1.slave_config == config) return Wire1.onStop(config);
#endif
#if WIRE_INTERFACES_COUNT > 2
  if(&Wire2.slave_config == config) return Wire2.onStop(config);
#endif
#if WIRE_INTERFACES_COUNT > 3
  if(&Wire3.slave_config == config) return Wire3.onStop(config);
#endif
#if WIRE_INTERFACES_COUNT > 4
  if(&Wire4.slave_config == config) return Wire4.onStop(config);
#endif
#if WIRE_INTERFACES_COUNT > 5
  if(&Wire5.slave_config == config) return Wire5.onStop(config);
#endif
  return 0;
}
