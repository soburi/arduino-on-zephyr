/*
  Copyright (c) 2020 Tokita, Hiroshi  All right reserved.

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

#include "wiring_private.h"
#include "variant.h"

#include <zephyr.h>
#include <gpio.h>

#define W_GPIO_PINMASK_BITS 32

#ifndef W_GPIO_PINS_PER_PORT
#define W_GPIO_PINS_PER_PORT W_GPIO_PINMASK_BITS
#endif

#ifndef W_GPIO_PORT_NUM
#define W_GPIO_PORT_NUM (sizeof(gpio_port_names)/sizeof(const char*))
#endif

#ifndef W_GPIO_PIN_NUM
#define W_GPIO_PIN_NUM (W_GPIO_PINS_PER_PORT * W_GPIO_PORT_NUM)
#endif

struct w_gpio_callbacks {
    struct gpio_callback z_callback;
    voidFuncPtr callbacks[W_GPIO_PINMASK_BITS];
    struct device* port;
};

static const char* gpio_port_names[] = W_GPIO_PORT_NAMES;

static struct w_gpio_callbacks w_callbacks[W_GPIO_PORT_NUM] = { 0 };

static void gpio_handler(struct device *port, struct gpio_callback *cb, u32_t pins)
{
    struct w_gpio_callbacks* port_callbacks = ((struct w_gpio_callbacks*)cb);
    for(unsigned int i=0; i<W_GPIO_PINMASK_BITS; i++) {
        if(((pins>>i) & 0x1) && port_callbacks->callbacks[i]) {
            port_callbacks->callbacks[i]();
        }
    }
}

static struct w_gpio_callbacks* find_port_callbacks(struct device* port)
{
    for(int i=0; i<W_GPIO_PORT_NUM; i++) {
        if(w_callbacks[i].port == port) {
            return &w_callbacks[i];
        }
    }
    for(int i=0; i<W_GPIO_PORT_NUM; i++) {
        if(w_callbacks[i].port == NULL) {
            return &w_callbacks[i];
        }
    }
    return NULL;
}

/*
static bool callback_exists(struct w_gpio_callbacks port_callbacks) {
    for(uint32_t i=0; i<W_GPIO_PINS_PER_PORT; i++) {
        if(port_callbacks->callbacks[i]) return true;
    }
    return false;
}
*/

#ifdef CONFIG_ARDUINO_QUERY_PIN_CONFIG
static inline void w_gpio_pin_configure(struct device* port, uint32_t pin, uint32_t conf) {
    gpio_pin_configure(port, pin, conf);
}

static inline uint32_t w_gpio_pin_query_config(struct device* port, uint32_t pin) {
    return gpio_pin_query_config(port, pin);
}
#else
static int w_pin_conf[W_GPIO_PIN_NUM] = { 0 };
static inline void w_gpio_pin_configure(struct device* port, uint32_t pin, uint32_t conf) {
    w_pin_conf[pin] = conf;
    gpio_pin_configure(port, pin, conf);
}

static inline uint32_t w_gpio_pin_query_config(struct device* port, uint32_t pin) {
    return w_pin_conf[pin];
}
#endif


uint32_t w_gpio_port_pin_no(uint32_t pin)
{
    return  (pin % W_GPIO_PINS_PER_PORT);
}

const char* w_gpio_port_name(uint32_t pin)
{
    if((pin/W_GPIO_PINS_PER_PORT) < W_GPIO_PORT_NUM) {
        return (gpio_port_names[pin / W_GPIO_PINS_PER_PORT]);
    }
    return NULL;
}

void w_gpio_pin_callback_configure(struct device* port, uint32_t pin, voidFuncPtr callback, uint32_t pinconf, uint32_t intconf, uint32_t extconf)
{
    uint32_t current = w_gpio_pin_query_config(port, pin);
    uint32_t config = (((pinconf != UINT_MAX) ? pinconf : current) & (GPIO_DIR_MASK|GPIO_PUD_MASK))
                    | (((intconf != UINT_MAX) ? intconf : current) & 0x00000076)
                    | (((extconf != UINT_MAX) ? extconf : current) & 0x0000FC88);

    if(current != config) {
        w_gpio_pin_configure(port, pin, config);
    }

    if(callback) {
        struct w_gpio_callbacks* port_callbacks = find_port_callbacks(port);

        assert(port_callbacks != NULL);

        if(!port_callbacks->port) {
            gpio_init_callback(&port_callbacks->z_callback, gpio_handler, UINT_MAX);
            gpio_add_callback(port, &port_callbacks->z_callback);
            port_callbacks->port = port;
        }
        port_callbacks->callbacks[pin] = callback;
        gpio_pin_enable_callback(port, pin);
    }
    else {
        gpio_pin_disable_callback(port, pin);
        /*
        struct w_gpio_callbacks* port_callbacks = find_port_callbacks(port);
        port_callbacks->callback[pin] = NULL;
        if(!callback_exists(port_callbacks) ) {
            gpio_remove_callback(port, &port_callbacks->z_callback);
            port_callbacks->port = NULL;
        }
        */
    }
}


