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

#include "MicroIp.h"

extern "C" {
int init_vlan(void);
}

int MicroIPClass::begin()
{
  init_vlan();
  return 1;
}

int MicroIPClass::maintain(){
  //Contiki is NOT support DHCPv6.
  return 0;
}

IPAddress MicroIPClass::linklocalAddress()
{
  return IPAddress();
}

IPAddress MicroIPClass::linklocalAddress(int state)
{
  return IPAddress();
}

IPAddress MicroIPClass::globalAddress()
{
  return globalAddress(0);
}

IPAddress MicroIPClass::globalAddress(int state)
{
  return IPAddress();
}

IPAddress MicroIPClass::interfaceID()
{
  //TODO
  IPAddress ret;

  return ret;
}

IPAddress MicroIPClass::gatewayIP()
{
  //TODO
  IPAddress ret;
  return ret;
}

IPAddress MicroIPClass::dnsServerIP()
{
  //TODO
  IPAddress ret;
  return ret;
}

IPAddress MicroIPClass::lookup(const char* host)
{
  return IPAddress();
}

MicroIPClass MicroIP;
