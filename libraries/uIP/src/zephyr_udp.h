#include <zephyr.h>
#include <errno.h>
#include <stdio.h>

#include "zephyr_in_addr.h"

#ifndef ZEPHYR_UDP_H__
#define ZEPHYR_UDP_H__

#ifdef __cplusplus
extern "C" {
#endif
  typedef void (*z_udp_receive_callback)(void* thisptr, struct z_in_addr* srcaddr, u16_t srcport,
                struct z_in_addr* dstaddr, u16_t dstport,
                unsigned char* buf, size_t buflen);

  void udp_init_context(void* context, void* thisptr, z_udp_receive_callback callback);
        void udp_start_listen(void* context, int port);
  void udp_connect(void* context, struct z_in_addr* peer, unsigned short peer_port);
  void udp_send(void* context, const unsigned char* buf, size_t buflen);
  void udp_close(void* context);

#ifdef __cplusplus
}
#endif

#endif
