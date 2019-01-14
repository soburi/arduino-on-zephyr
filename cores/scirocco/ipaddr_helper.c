#include <zephyr.h>
#include <net/net_ip.h>

bool parse_ipaddr(const char* addr, uint8_t* buf)
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

