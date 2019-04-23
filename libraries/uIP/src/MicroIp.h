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

#ifndef MICROIP_H
#define MICROIP_H

#include <inttypes.h>
#include "IPAddress.h"

#define IS_NET_L2(type, nif) &NET_L2_GET_NAME(type) == net_if_l2(nif)

#ifdef CONFIG_NET_L2_BT
#define IS_BLUETOOTH_L2(netif) IS_NET_L2(BLUETOOTH, netif)
#else
#define IS_BLUETOOTH_L2(netif) (false)
#endif

#ifdef CONFIG_NET_L2_IEEE802154
#define IS_IEEE802154_L2(netif) IS_NET_L2(IEEE802154, netif)
#else
#define IS_IEEE802154_L2(netif) (false)
#endif

#ifdef CONFIG_NET_L2_OPENTHREAD
#define IS_OPENTHREAD_L2(netif) IS_NET_L2(OPENTHREAD, netif)
#else
#define IS_OPENTHREAD_L2(netif) (false)
#endif

struct net_if;

class MicroIPClass {
public:
  MicroIPClass();

  int begin();
  int maintain();

  IPAddress localIP();
  IPAddress subnetMask();
  IPAddress gatewayIP();
  IPAddress dnsServerIP();

#if defined(CONFIG_NET_IPV6)
  IPAddress linklocalAddress(int state=-1, int idx=0);
  IPAddress globalAddress(int idx=0);
  int prefixLength(IPAddress ip);
#endif

  IPAddress lookup(const char* host);
  void setHostname(const char* hostname);
  void addDNS(const IPAddress& addr, uint32_t lifetime=0xFFFFFFFF);
  void removeDNS(const IPAddress& addr) { addDNS(addr, 0); }

private:
  friend class MicroIPClient;
  friend class MicroIPServer;
protected:
  struct net_if* iface;
};

extern MicroIPClass MicroIP;

#endif
