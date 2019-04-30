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
#if 0
extern "C" {
#define DEBUG DEBUG_NONE
#include <net/ip/uip-debug.h>
}

#include "ClientSocket.h"
#include "ServerSocket.h"

ClientSocket ServerSocket::null_client(0);

ServerSocket::ServerSocket(uint16_t port_)
{
  port = port_;
}

void ServerSocket::begin()
{
  PRINTF("ServerSocket::begin\n");

  internal_client.listen(port);
}

ClientSocket& ServerSocket::available()
{
  //printf("ServerSocket::available\n");
  uint8_t s = internal_client.status();
  if (s == TCP_SOCKET_CONNECTED || s == TCP_SOCKET_DATA_SENT) {
    if (internal_client.available()) {
      return internal_client;
    }
  }

  return null_client;
}

size_t ServerSocket::write(uint8_t b) 
{
  return internal_client.write(&b, 1);
}

size_t ServerSocket::write(const uint8_t *buffer, size_t size) 
{
  return internal_client.write(buffer, size);
}
#endif
