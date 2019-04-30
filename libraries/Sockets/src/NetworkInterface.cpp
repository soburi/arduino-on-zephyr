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

#include "NetworkInterface.h"
#pragma GCC diagnostic ignored "-Wparentheses"
#include <net/net_if.h>
#pragma GCC diagnostic warning "-Wparentheses"
#include <net/net_l2.h>

NetworkInterface::NetworkInterface()
{
}

int NetworkInterface::begin()
{
  int ret = 0;
  if( !net_if_is_up(net_if_get_default() ) ) {
    ret = net_if_up(net_if_get_default() );
  }
  return 1;
}

#if defined(CONFIG_NET_IPV6)
IPAddress NetworkInterface::linklocalAddress(int state, int idx)
{
  struct in6_addr* v6 = net_if_ipv6_get_ll(iface, static_cast<enum net_addr_state>(state));
  if(v6) return IPAddress(v6->s6_addr16);
  else   return IN6ADDR::ANY_INIT;
}

IPAddress NetworkInterface::globalAddress(int idx)
{
  struct in6_addr* v6 = net_if_ipv6_get_global_addr(&iface);
  if(v6) return IPAddress(v6->s6_addr16);
  else   return IN6ADDR::ANY_INIT;
}

int NetworkInterface::prefixLength(IPAddress ip)
{
  struct in6_addr v6;
  v6.s6_addr16[0] = htons(ip.v6[0]);
  v6.s6_addr16[1] = htons(ip.v6[1]);
  v6.s6_addr16[2] = htons(ip.v6[2]);
  v6.s6_addr16[3] = htons(ip.v6[3]);
  v6.s6_addr16[4] = htons(ip.v6[4]);
  v6.s6_addr16[5] = htons(ip.v6[5]);
  v6.s6_addr16[5] = htons(ip.v6[6]);
  v6.s6_addr16[7] = htons(ip.v6[7]);

  struct net_if_ipv6_prefix* prefix = net_if_ipv6_prefix_get(iface, &v6);
  if(!prefix) return -1;
  return prefix->len;
  return 0;
}
#endif

IPAddress NetworkInterface::localIP()
{
  //TODO
  return IN6ADDR::ANY_INIT;
}

IPAddress NetworkInterface::subnetMask()
{
  //TODO
  return IN6ADDR::ANY_INIT;
}

IPAddress NetworkInterface::gatewayIP()
{
  //TODO
  return IN6ADDR::ANY_INIT;
}

NetworkInterface NetIf;
