#include <stdint.h>

#ifndef ZEPHYR_IN_ADDR__
#define ZEPHYR_IN_ADDR__

struct z_v4data {
  union {
    uint8_t bytes[4];
    uint32_t dword;
  };
};

struct z_v4map_addr {
#if defined(CONFIG_NET_IPV6)
  uint8_t prefix[12];
#else
  uint8_t prefix[0];
#endif
  struct z_v4data v4;
};

struct z_in_addr {
  union {
#if defined(CONFIG_NET_IPV6)
    uint16_t u16[8];
    uint8_t u8[16];
#else
    uint16_t u16[2];
    uint8_t u8[4];
#endif
    struct z_v4map_addr v4map;
  };
};

#endif //ZEPHYR_IN_ADDR__

