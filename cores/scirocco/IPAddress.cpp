/*
  Copyright (c) 2014-2018 Tokita, Hiroshi  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Print.h"
#include "IPAddress.h"

#if defined(CONFIG_NET_IPV4) || defined(CONFIG_NET_IPV6)

#include <zephyr.h>
#pragma GCC diagnostic ignored "-Wparentheses"
#include <net/net_ip.h>
#pragma GCC diagnostic warning "-Wparentheses"
#include <net/socket.h>
#include <misc/byteorder.h>

#if defined(CONFIG_NET_IPV6)
#define INIT_IPBYTES(a, b, c, d) {0,0,0,0,  0,0,0,0,  0,0,0xFF,0xFF,  a,b,c,d}
#else
#define INIT_IPBYTES(a, b, c, d) {a,b,c,d}
#endif

static bool parse_ipaddr(const char* addr, uint8_t* buf)
{
    struct sockaddr sa;
    bool ret = net_ipaddr_parse(addr, strlen(addr), &sa);
    if(ret) {
        if(sa.sa_family == AF_INET6) {
#if defined(CONFIG_NET_IPV6)
            memcpy(buf, ((struct sockaddr_in6*)(&sa))->sin6_addr.s6_addr, 16);
#else
	    return false;
#endif
	}
	else if(sa.sa_family == AF_INET) {
#if defined(CONFIG_NET_IPV6)
            uint8_t prefix[12] = { 0,0,0,0,  0,0,0,0, 0,0,0xFF,0xFF};
            memcpy(buf, prefix, 12);
#endif
            memcpy(buf+12, ((struct sockaddr_in*)(&sa))->sin_addr.s4_addr, 4);
	}
    }
    return ret;
}


IPAddress::IPAddress()
    : v6(_address.u16)
{
    uint8_t addrbytes[] = INIT_IPBYTES(0, 0, 0, 0);
    memcpy(_address.u8, addrbytes, sizeof(addrbytes));
}

IPAddress::IPAddress(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3)
    : v6(_address.u16)
{
    uint8_t addrbytes[] = INIT_IPBYTES(b0, b1, b2, b3);
    memcpy(_address.u8, addrbytes, sizeof(addrbytes));
}

#if defined(CONFIG_NET_IPV6)
IPAddress::IPAddress(uint16_t d0, uint16_t d1, uint16_t d2, uint16_t d3,
                     uint16_t d4, uint16_t d5, uint16_t d6, uint16_t d7)
    : v6(_address.u16)
{
    _address.u16[0] = sys_be16_to_cpu(d0); _address.u16[1] = sys_be16_to_cpu(d1);
    _address.u16[2] = sys_be16_to_cpu(d2); _address.u16[3] = sys_be16_to_cpu(d3);
    _address.u16[4] = sys_be16_to_cpu(d4); _address.u16[5] = sys_be16_to_cpu(d5);
    _address.u16[6] = sys_be16_to_cpu(d6); _address.u16[7] = sys_be16_to_cpu(d7);
}

IPAddress::IPAddress(const uint16_t *a)
    : v6(_address.u16)
{
    if(a) {
        memcpy(_address.u16, a, sizeof(_address.u16));
    }
    else {
        memset(_address.u16, 0, sizeof(_address.u16));
    }
}
#endif

IPAddress::IPAddress(uint32_t addr)
    : v6(_address.u16)
{
    uint8_t addrbytes[] = INIT_IPBYTES(
        (uint8_t)((addr & 0xFF000000) >> 24),
        (uint8_t)((addr & 0x00FF0000) >> 16),
        (uint8_t)((addr & 0x0000FF00) >>  8),
        (uint8_t)((addr & 0x000000FF) >>  0) );
    memcpy(_address.u8, addrbytes, sizeof(addrbytes));
}

IPAddress::IPAddress(const uint8_t *addr)
    : v6(_address.u16)
{
    if(addr) {
        const uint8_t addrbytes[] = INIT_IPBYTES(addr[0], addr[1], addr[2], addr[3]);
        memcpy(_address.u8, addrbytes, sizeof(addrbytes));
    }
    else {
        const uint8_t addrbytes[] = INIT_IPBYTES(0, 0, 0, 0);
        memcpy(_address.u8, addrbytes, sizeof(addrbytes));
    }
}

bool IPAddress::fromString(const char *addr)
{
    return parse_ipaddr(addr, _address.u8);
}

IPAddress& IPAddress::operator=(const uint8_t *addr)
{
    if(addr) {
        const uint8_t addrbytes[] = INIT_IPBYTES(addr[0], addr[1], addr[2], addr[3]);
        memcpy(_address.bytes, addrbytes, sizeof(addrbytes));
    }
    else {
        const uint8_t addrbytes[] = INIT_IPBYTES(0, 0, 0, 0);
        memcpy(_address.bytes, addrbytes, sizeof(addrbytes));
    }
    return *this;
}

IPAddress& IPAddress::operator=(uint32_t addr)
{
    uint8_t addrbytes[] = INIT_IPBYTES(
        (uint8_t)((addr & 0xFF000000) >> 24),
        (uint8_t)((addr & 0x00FF0000) >> 16),
        (uint8_t)((addr & 0x0000FF00) >>  8),
        (uint8_t)((addr & 0x000000FF) >>  0) );
    memcpy(_address.u8, addrbytes, sizeof(addrbytes));
    return *this;
}

bool IPAddress::operator==(const uint8_t* addr) const
{
    if(!addr) return false;
    return memcmp(addr, _address.bytes, sizeof(_address.bytes)) == 0;
}

#if defined(CONFIG_NET_IPV6)
bool IPAddress::operator==(const uint16_t* addr) const
{
    if(!addr) return false;
    return memcmp(addr, _address.u16, sizeof(_address.u16)) == 0;
}
#endif

#if defined(CONFIG_NET_IPV6)
IPAddress& IPAddress::operator=(const IPAddress& addr)
{
    *this = addr._address.u16;
    return *this;
}

IPAddress& IPAddress::operator=(const uint16_t *addr)
{
    if(addr) {
        memcpy(_address.u16, addr, sizeof(_address.u16));
    }
    else {
        memset(_address.u16, 0, sizeof(_address.u16));
    }
    return *this;
}
#endif

bool IPAddress::isV6MappedAddress() const
{
#if defined(CONFIG_NET_IPV6)
    if( _address.u16[0] == 0 && _address.u16[1] == 0 &&
        _address.u16[3] == 0 && _address.u16[4] == 0 &&
	_address.u16[5] == 0xFFFF)
    {
        return true;
    }
    else
    {
        return false;
    }
#else
    return false;
#endif
}

size_t IPAddress::printTo(Print& p) const
{
    if( isV6MappedAddress() || sizeof(_address.prefix) == 0) {
        char buf[INET_ADDRSTRLEN];
        zsock_inet_ntop(AF_INET, _address.bytes, buf, sizeof(buf));
        return p.print(buf);
    }
    else
    {
        return p.print(v6);
    }
}

size_t IPAddress::V6RawAccessor::printTo(Print& p) const
{
    char buf[INET6_ADDRSTRLEN];
    zsock_inet_ntop(AF_INET6, addr, buf, sizeof(buf));
    return p.print(buf);
}

const IPAddress INADDR::NONE(0, 0, 0, 0);
const IPAddress INADDR::ANY(0, 0, 0, 0);

const IPAddress IN6ADDR::ANY_INIT(0, 0, 0, 0, 0, 0, 0, 0);
const IPAddress IN6ADDR::LOOPBACK_INIT(0, 0, 0, 0, 0, 0, 0, 1);
const IPAddress IN6ADDR::LINKLOCAL_ALLNODES_INIT(  0xff02,0,0,0, 0,0,0,1);
const IPAddress IN6ADDR::INKLOCAL_ALLROUTERS_INIT(0xff02,0,0,0, 0,0,0,2);
const IPAddress IN6ADDR::INTERFACELOCAL_ALLNODES_INIT(0xff01,0,0,0, 0,0,0,1);
const IPAddress IN6ADDR::INTERFACELOCAL_ALLROUTERS_INIT(0xff01,0,0,0, 0,0,0,2);
const IPAddress IN6ADDR::SITELOCAL_ALLROUTERS_INIT(0xff05,0,0,0, 0,0,0,2);

#endif
