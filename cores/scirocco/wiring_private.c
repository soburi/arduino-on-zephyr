#include <zephyr.h>
#include <gpio.h>
#include <variant.h>

int gpio_configs[GPIO_PIN_NO];
struct gpio_callback gpio_cb[GPIO_PIN_NO];
