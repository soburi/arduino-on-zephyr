/*
  Copyright (c) 2016-2018 Tokita, Hiroshi  All right reserved.

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

#include <stdint.h>
#include <stdlib.h>
#include <zephyr.h>
#include <kernel.h>
#include <misc/byteorder.h>

#include "Arduino.h"
#include "wiring_private.h"
#include "Udp.h"
#include "MicroIp.h"
#include "MicroIpUdp.h"

#include "zephyr_udp.h"

#define PRINTF printk
struct receive_pack {
  uint16_t length;
  struct z_in_addr in_addr;
  uint16_t port;
};

MicroIPUDP::MicroIPUDP() : remaining(0)
{
  udp_init_context(context, this, MicroIPUDP::dispatch);
}

uint8_t MicroIPUDP::begin(uint16_t port)
{
//  udp_start_listen(context, port);
  return 1;
}

int MicroIPUDP::available()
{
  return remaining;
}

void MicroIPUDP::stop()
{
  udp_close(context);
}

int MicroIPUDP::beginPacket(const char *host, uint16_t port)
{
  IPAddress remote = MicroIP.lookup(host);
  if(remote == IN6ADDR_ANY_INIT) {
    return 0;
  }
  return beginPacket(remote, port);
}

int MicroIPUDP::beginPacket(IPAddress ip, uint16_t port)
{
  udp_connect(context, raw_in_addr(ip), __bswap_16(port));
  return 1;
}

int MicroIPUDP::endPacket()
{
  udp_send(context, txbuf._aucBuffer, txbuf.available());
  txbuf.clear();
  return 1;
}

size_t MicroIPUDP::write(uint8_t byte)
{
  if( !txbuf.isFull() ) {
    txbuf.store_char(byte);
    return 1;
  }
  else {
    return 0;
  }
}

size_t MicroIPUDP::write(const uint8_t *buffer, size_t size)
{
  for(uint32_t i=0; i<size; i++) {
    int r = write(buffer[i]);
    if(r == -1) {
      return i;
    }
  }
  return size;
}

int MicroIPUDP::parsePacket()
{
  PRINTF("MicroIPUDP::parsePacket %d %d\n", rxbuf.available(), available());
  if( available() ) {
    //notify
    //discard current data
    while( available() ) {
      (void) read();
    }
  }

  // garbage cleanup.
  if( rxbuf.available() < static_cast<int>(sizeof(struct receive_pack)) ) {
    while( raw_read() != -1);
    remaining = 0;
  }
  else {
    struct receive_pack pack;
    raw_read(reinterpret_cast<uint8_t*>(&pack) ,sizeof(struct receive_pack));

    remaining = pack.length - sizeof(struct receive_pack);
    _remoteIP = IPAddress(sys_be16_to_cpu(pack.in_addr.u16[0]),
                          sys_be16_to_cpu(pack.in_addr.u16[1]),
                          sys_be16_to_cpu(pack.in_addr.u16[2]),
                          sys_be16_to_cpu(pack.in_addr.u16[3]),
                          sys_be16_to_cpu(pack.in_addr.u16[4]),
                          sys_be16_to_cpu(pack.in_addr.u16[5]),
                          sys_be16_to_cpu(pack.in_addr.u16[6]),
                          sys_be16_to_cpu(pack.in_addr.u16[7]));
    _remotePort = pack.port;

    PRINTF("return MicroIPUDP::parsePacket %d\n", available());
  }
  return available();
}

int MicroIPUDP::read()
{
  if(remaining) {
    remaining--;
    return raw_read();
  }
  else {
    return -1;
  }
}

int MicroIPUDP::read(unsigned char* buf, size_t size)
{
  for(uint32_t i=0; i<size; i++) {
    int r = read();
    if(r == -1) {
      return i;
    }
    buf[i] = (uint8_t)r;
  }
  return size;
}

int MicroIPUDP::peek()
{
  return rxbuf.peek();
}

void MicroIPUDP::flush()
{
  //???
}

int MicroIPUDP::raw_read()
{
  return rxbuf.read_char();
}

int MicroIPUDP::raw_read(unsigned char* buf, size_t size)
{
  for(uint32_t i=0; i<size; i++) {
    int r = raw_read();
    if(r == -1) {
      return i;
    }
    buf[i] = (uint8_t)r;
  }
  return size;
}

void MicroIPUDP::receive(struct z_in_addr *source_addr, uint16_t source_port,
                         struct z_in_addr *dest_addr, uint16_t dest_port,
                         unsigned char *data, size_t datalen)
{
  const uint16_t store_size = static_cast<uint16_t>(datalen + sizeof(struct receive_pack));
  struct receive_pack pack = { store_size, *source_addr, source_port };
  (void) dest_addr;
  (void) dest_port;
  PRINTF("MicroIPUDP::receive %d %d %d\n", sizeof(struct receive_pack), store_size, datalen );

  if( store_size > sizeof(rxbuf._aucBuffer) ) {
    //too large packet.
    return;
  }

  if( store_size > rxbuf.available() ) {
    PRINTF("MicroIPUDP::receive available() %d %d\n", available(), remaining );
    if( available() ) {
      //notify discard
      //discard current data
      while( available() ) {
        (void) raw_read();
        remaining--;
      }
    }
  }

  PRINTF("MicroIPUDP::receive ringbuf_size() %d ringbuf_elements() %d\n", sizeof(rxbuf._aucBuffer), rxbuf.available() );
//  while( store_size < rxbuf.availableForStore() ) {
//    // discard old packet.
//    parsePacket();
//  }

  for(size_t i=0; i<sizeof(struct receive_pack); i++) {
    rxbuf.store_char(((uint8_t*)&pack)[i]);
  }

  for(size_t i=0; i<datalen; i++) {
    rxbuf.store_char(data[i]);
  }
  PRINTF("MicroIPUDP::receive ringbuf_size() %d ringbuf_elements() %d\n", sizeof(rxbuf._aucBuffer) , rxbuf.available() );

}

void MicroIPUDP::dispatch(void* thisptr, struct z_in_addr* srcaddr, uint16_t srcport,
                                         struct z_in_addr* dstaddr, uint16_t dstport,
                          unsigned char* buffer, size_t len)
{
  PRINTF("MicroIPUDP::dispatch\n");
  reinterpret_cast<MicroIPUDP*>(thisptr)->receive(srcaddr, srcport, dstaddr, dstport, buffer, len);
}

