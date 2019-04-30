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

#ifndef SOCKET_UDPSOCKET_H
#define SOCKET_UDPSOCKET_H

#include <zephyr.h>
#include <net/socket.h>

#include "Udp.h"
#include "RingBuffer.h"

struct sockaddr_storage;

class UDPSocket : public UDP {
friend class Dispatcher;
private:
  IPAddress destIP; 
  uint16_t destPort; 
  IPAddress _remoteIP; 
  uint16_t _remotePort; 
  uint16_t remaining; 

  RingBufferN<1024> txbuf;
  RingBufferN<1024> rxbuf;

  struct zsock_pollfd pollfd;
  uint8_t recv_buffer[128];
  struct udp_work {
	struct k_work Work;
	UDPSocket* This;
  } work;

  int sock;

public:
  UDPSocket();  
  virtual uint8_t begin(uint16_t);	
  virtual void stop();  
  virtual int beginPacket(IPAddress ip, uint16_t port);
  virtual int beginPacket(const char *host, uint16_t port);
  virtual int endPacket();
  virtual size_t write(uint8_t);
  virtual size_t write(const uint8_t *buffer, size_t size);
  using Print::write;
  virtual int parsePacket();
  
  virtual int available();
  virtual int read();
  virtual int read(unsigned char* buffer, size_t len);
  virtual int read(char* buffer, size_t len) { return read((unsigned char*)buffer, len); };
  virtual int peek();
  virtual void flush();	
  
  virtual IPAddress remoteIP() { return _remoteIP; };
  virtual uint16_t remotePort() { return _remotePort; };

private:
  int raw_read();
  int raw_read(unsigned char* buffer, size_t len);

  void receive(struct sockaddr_storage* addr, unsigned char* buffer, size_t len);

  void dispatch();
  static void Task(struct k_work *kwork);
};

#endif
