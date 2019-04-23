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
#pragma GCC diagnostic ignored "-Wparentheses"
#include <net/socket.h>
#pragma GCC diagnostic warning "-Wparentheses"
#include <autoconf.h>

#include "Arduino.h"
#include "wiring_private.h"
#include "Udp.h"
#include "MicroIp.h"
#include "MicroIpUdp.h"

#if defined(CONFIG_NET_IPV6)
#define INIT_SOCKADDR(ip, port) \
{\
    .sin6_family = AF_INET6, \
    .sin6_port = htons(port), \
    .sin6_addr = { \
        .s6_addr16 = { htons(ip.v6[0]), htons(ip.v6[1]), htons(ip.v6[2]), htons(ip.v6[3]), \
                       htons(ip.v6[4]), htons(ip.v6[5]), htons(ip.v6[6]), htons(ip.v6[7]) }, \
    }, \
    .sin6_scope_id = 0 \
}

#define SOCKADDR struct sockaddr_in6
#define ANY_ADDR IN6ADDR.ANY_INIT

#else
#define INIT_SOCKADDR(ip, port) \
{\
    .sin_family = AF_INET, \
    .sin_port = htons(port), \
    .sin_addr = { \
        .s4_addr = { ip[0], ip[1], ip[2], ip[3] } \
    } \
}

#define SOCKADDR struct sockaddr_in
#define ANY_ADDR INADDR.NONE

#endif

static void ss_addr(IPAddress& remoteIP, struct sockaddr_storage* ss)
{
    if(ss->ss_family == AF_INET6) {
      struct sockaddr_in6* sa = reinterpret_cast<struct sockaddr_in6*>(ss);
      remoteIP = sa->sin6_addr.s6_addr16;
    }
    else if(ss->ss_family == AF_INET) {
      struct sockaddr_in* sa = reinterpret_cast<struct sockaddr_in*>(ss);
      remoteIP = sa->sin_addr.s4_addr;
    }
}

static void ss_port(uint16_t& remotePort, struct sockaddr_storage* ss)
{
  if(ss->ss_family == AF_INET6) {
    remotePort = htons(reinterpret_cast<struct sockaddr_in6*>(ss)->sin6_port);
  }
  else if(ss->ss_family == AF_INET) {
    remotePort = htons(reinterpret_cast<struct sockaddr_in*>(ss)->sin_port);
  }
}

#define PRINTF(...)
struct receive_pack {
  uint16_t length;
  struct sockaddr_storage addr;
};

MicroIPUDP::MicroIPUDP()
{
}

uint8_t MicroIPUDP::begin(uint16_t port)
{
  const SOCKADDR sa = INIT_SOCKADDR(ANY_ADDR, port);

  sock = zsock_socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
  zsock_bind(sock, reinterpret_cast<const struct sockaddr*>(&sa), sizeof(sa));
  //Dispatcher::DispatchTask.Append(this);
  k_work_init(&work.Work, Task);
  work.This = this;
  k_work_submit(&work.Work);
  return 1;
}

int MicroIPUDP::available()
{
  return remaining;
}

void MicroIPUDP::stop()
{
  //Dispatcher::DispatchTask.Remove(this);
  zsock_close(sock);
}

int MicroIPUDP::beginPacket(const char *host, uint16_t port)
{
  IPAddress remote = MicroIP.lookup(host);
  if(remote == ANY_ADDR) {
    return 0;
  }
  return beginPacket(remote, port);
}

int MicroIPUDP::beginPacket(IPAddress ip, uint16_t port)
{
  destIP = ip;
  destPort = port;
  return 1;
}

int MicroIPUDP::endPacket()
{
  const SOCKADDR sa = INIT_SOCKADDR(destIP, destPort);

  zsock_sendto(sock, txbuf._aucBuffer, txbuf.available(), 0, reinterpret_cast<const struct sockaddr*>(&sa), sizeof(sa));
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

    ss_addr(_remoteIP, &pack.addr);
    ss_port(_remotePort, &pack.addr);

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

void MicroIPUDP::receive(struct sockaddr_storage *source_addr, unsigned char *data, size_t datalen)
{
  const uint16_t store_size = static_cast<uint16_t>(datalen + sizeof(struct receive_pack));
  struct receive_pack pack = { store_size, *source_addr };
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

void MicroIPUDP::dispatch()
{
  pollfd.fd = sock;
  pollfd.events = ZSOCK_POLLIN;

  zsock_poll(&pollfd, 1, -1);

  if( !(pollfd.revents & ZSOCK_POLLIN) ) {
    return;
  }

  struct sockaddr_storage fromaddr;
  socklen_t addrlen = sizeof(fromaddr);

  ssize_t sz = zsock_recvfrom(this->sock, recv_buffer, sizeof(recv_buffer), 0,
                       reinterpret_cast<struct sockaddr*>(&fromaddr), &addrlen);
  if(sz != 0) {
    //TODO printk("errno = %d\n", errno);
  }
  this->receive(&fromaddr, recv_buffer, sz);
}

void MicroIPUDP::Task(struct k_work *kwork) {
  struct udp_work* uw = reinterpret_cast<struct udp_work*>(kwork);
  uw->This->dispatch();
  k_work_submit(kwork);
}

