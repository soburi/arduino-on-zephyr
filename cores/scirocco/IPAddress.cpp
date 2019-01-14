#include "IPAddress.h"

IPAddress::IPAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet)
	: v6(NULL)
{
}
#if defined(CONFIG_NET_IPV6)
    IPAddress(uint16_t d1, uint16_t d2, uint16_t d3, uint16_t d4,
              uint16_t d5, uint16_t d6, uint16_t d7, uint16_t d8);
    IPAddress(const uint16_t *address);
#endif

