#include <zephyr.h>
#include <gpio.h>
#include <variant.h>
#include "wiring_digital.h"
#include "wiring_private.h"
#include "WInterrupts.h"

#ifndef W_GPIO_PINS_PER_PORT
#define W_GPIO_PINS_PER_PORT 32
#endif

#ifndef W_GPIO_PORT_NUM
#define W_GPIO_PORT_NUM (sizeof(gpio_port_names)/sizeof(const char*))
#endif

#ifndef W_PIN2PORT
#define W_PIN2PORT(x) (gpio_port_names[x / W_GPIO_PINS_PER_PORT])
#endif

#ifndef W_PIN2PORTPIN
#define W_PIN2PORTPIN(x) (x % W_GPIO_PINS_PER_PORT)
#endif

#ifndef W_GPIO_PIN_NUM
#define W_GPIO_PIN_NUM (W_GPIO_PINS_PER_PORT * W_GPIO_PORT_NUM)
#endif


struct w_gpio_callbacks {
	struct gpio_callback z_callback;
	voidFuncPtr callback;
};

static const char* gpio_port_names[] = W_GPIO_PORT_NAMES;
static int w_pin_mode[W_GPIO_PIN_NUM] = { 0 };
static struct w_gpio_callbacks w_callbacks[W_GPIO_PIN_NUM] = { 0 };

static void gpio_handler(struct device *port, struct gpio_callback *cb, u32_t pins)
{
	for(uint32_t i=0; i<W_GPIO_PIN_NUM; i++)
	{
		if( (&w_callbacks[i].z_callback) == cb) {
			w_callbacks[i].callback();
		}
	}
}

void w_configure_gpio_interrupt(uint32_t pin, voidFuncPtr callback, uint32_t intmode, uint32_t pinmode, uint32_t extraflag)
{
	int pinconf = 0;

	switch(pinmode)
	{
	case INPUT:
		pinconf = GPIO_DIR_IN;
		break;
	case OUTPUT:
		pinconf = GPIO_DIR_OUT;
		break;
	case INPUT_PULLUP:
		pinconf = GPIO_DIR_IN | GPIO_PUD_PULL_UP;
		break;
	case INPUT_PULLDOWN:
		pinconf = GPIO_DIR_IN | GPIO_PUD_PULL_DOWN;
		break;
	}

	if(callback) {
		switch(intmode)
		{
		case LOW:
			pinconf |= (GPIO_INT | GPIO_INT_LEVEL | GPIO_INT_ACTIVE_LOW);
			break;
		case HIGH:
			pinconf |= (GPIO_INT | GPIO_INT_LEVEL | GPIO_INT_ACTIVE_HIGH);
			break;
		case CHANGE:
			pinconf |= (GPIO_INT | GPIO_INT_EDGE  | GPIO_INT_DOUBLE_EDGE);
			break;
		case FALLING:
			pinconf |= (GPIO_INT | GPIO_INT_EDGE  | GPIO_INT_ACTIVE_LOW);
			break;
		case RISING:
			pinconf |= (GPIO_INT | GPIO_INT_EDGE  | GPIO_INT_ACTIVE_HIGH);
			break;
		}
	}

	pinconf |= extraflag;

	w_pin_mode[pin] = pinmode;
	gpio_pin_configure(device_get_binding(W_PIN2PORT(pin)), W_PIN2PORTPIN(pin), pinconf);

	if(callback) {
		w_callbacks[pin].callback = callback;
		gpio_init_callback(&w_callbacks[pin].z_callback, gpio_handler, BIT(W_PIN2PORTPIN(pin)));
		gpio_add_callback(device_get_binding(W_PIN2PORT(pin)), &w_callbacks[pin].z_callback);
		gpio_pin_enable_callback(device_get_binding(W_PIN2PORT(pin)), pin);
	}
	else {
		detachInterrupt(pin);
	}

}

void attachInterrupt(uint32_t pin, voidFuncPtr callback, uint32_t mode)
{
	uint32_t pinmode = w_pin_mode[pin];
	w_configure_gpio_interrupt(pin, callback, mode, pinmode, 0);
}
/*
void attachInterrupt(uint32_t pin, voidFuncPtr callback, uint32_t mode, uint32_t pinmode, uint32_t extraflag)
{
	w_configure_gpio_interrupt(pin, callback, mode, pinmode, extraflag);
}
*/
void detachInterrupt(uint32_t pin)
{
	gpio_pin_disable_callback(device_get_binding(W_PIN2PORT(pin)), pin);
	gpio_remove_callback(device_get_binding(W_PIN2PORT(pin)), &w_callbacks[pin].z_callback);
}

void pinMode( uint32_t dwPin, uint32_t dwMode )
{
	w_configure_gpio_interrupt(dwPin, NULL, -1, dwMode, 0);
}


void digitalWrite( uint32_t ulPin, uint32_t ulVal )
{
	gpio_pin_write(device_get_binding(W_PIN2PORT(ulPin)), W_PIN2PORTPIN(ulPin), ulVal ? 1 : 0);
}

int digitalRead( uint32_t ulPin )
{
	u32_t value;
	gpio_pin_read(device_get_binding(W_PIN2PORT(ulPin)), W_PIN2PORTPIN(ulPin), &value);
	return value ? 1 : 0;
}

