#include <zephyr.h>
#include <zephyr/drivers/gpio.h>
#include <variant.h>
#include "wiring_digital.h"
#include "wiring_private.h"
#include "WInterrupts.h"


struct w_gpio_callback {
	struct gpio_callback z_callback;
	voidFuncPtr callback[16];
};

static const struct device *gpio_port_devices[] = W_GPIO_PORT_DEVICES;
static const uint32_t gpio_port_pinnums[] = W_GPIO_PORT_PINNUMS;
static struct w_gpio_callback w_callbacks[ARRAY_SIZE(gpio_port_devices)] = { 0 };

static struct gpio_dt_spec led_gpio_specs[] = LED_TABLE;

static const struct device* w_pin2port(uint32_t pin)
{
	for(size_t i=0; i<ARRAY_SIZE(gpio_port_devices); i++) {
		if(pin < gpio_port_pinnums[i]) {
			return gpio_port_devices[i];
		};
		pin -= gpio_port_pinnums[i];
	}
	return NULL;
}

static uint32_t w_pin2portidx(uint32_t pin)
{
	for(size_t i=0; i<ARRAY_SIZE(gpio_port_devices); i++) {
		if(pin < gpio_port_pinnums[i]) {
			return i;
		};
		pin -= gpio_port_pinnums[i];
	}
	return UINT32_MAX;
}


static uint32_t w_pin2portpin(uint32_t pin)
{
	for(size_t i=0; i<ARRAY_SIZE(gpio_port_pinnums); i++) {
		if(pin < gpio_port_pinnums[i]) {
			return pin;
		};
		pin -= gpio_port_pinnums[i];
	}
	return UINT32_MAX;
}

static void w_set_gpio_callback(uint32_t pin, voidFuncPtr func)
{
	w_callbacks[w_pin2portidx(pin)].callback[w_pin2portpin(pin)] = func;
}

static uint32_t w_callback_bits(struct w_gpio_callback *wcb)
{
	uint32_t bits = 0;
	for(uint32_t i=0; i<ARRAY_SIZE(wcb->callback); i++) {

		if(wcb->callback[i] != NULL) {	
			bits |= BIT(i);
		}
	}
	return bits;
}


static void w_gpio_handler(const struct device *port, struct gpio_callback *cb, uint32_t pins)
{
	struct w_gpio_callback* wcb = (struct w_gpio_callback*)cb;

	for(uint32_t i=0; i<ARRAY_SIZE(wcb->callback); i++) {
		wcb->callback[BIT(i)]();
	}
}

static uint32_t w_gpio_spec_to_pin(struct gpio_dt_spec *spec) {
	uint32_t pin =0;
	for(size_t i=0; i<ARRAY_SIZE(gpio_port_devices); i++) {
		if(spec->port == gpio_port_devices[i]) {
			return pin + spec->pin;
		}
		pin += gpio_port_pinnums[i];
	}
	return UINT32_MAX;
}

uint32_t w_led_pin(uint32_t led_no)
{
	return w_gpio_spec_to_pin(&led_gpio_specs[led_no]);
}

static void w_configure_gpio_interrupt(uint32_t pin, voidFuncPtr callback, gpio_flags_t intmode, gpio_flags_t pinmode, uint32_t extraflag)
{
	int pinconf = 0;

	switch(pinmode)
	{
	case INPUT:
		pinconf = GPIO_INPUT;
		break;
	case OUTPUT:
		pinconf = GPIO_OUTPUT;
		break;
	case INPUT_PULLUP:
		pinconf = GPIO_INPUT | GPIO_PULL_UP;
		break;
	case INPUT_PULLDOWN:
		pinconf = GPIO_INPUT | GPIO_PULL_DOWN;
		break;
	}

	if(callback) {
		switch(intmode)
		{
		case LOW:
			pinconf |= GPIO_INT_LEVEL_LOW;
			break;
		case HIGH:
			pinconf |= GPIO_INT_LEVEL_HIGH;
			break;
		case CHANGE:
			pinconf |= GPIO_INT_EDGE_BOTH;
			break;
		case FALLING:
			pinconf |= GPIO_INT_EDGE_FALLING;
			break;
		case RISING:
			pinconf |= GPIO_INT_EDGE_RISING;
			break;
		}
	}

	pinconf |= extraflag;

	gpio_pin_configure(w_pin2port(pin), w_pin2portpin(pin), pinconf);

	if(callback) {
		w_set_gpio_callback(pin, callback);
		gpio_init_callback(&w_callbacks[w_pin2portpin(pin)].z_callback, w_gpio_handler, w_callback_bits(&w_callbacks[w_pin2portidx(pin)]));
		gpio_add_callback(w_pin2port(pin), (struct gpio_callback*)&w_callbacks[w_pin2portidx(pin)]);
	}
	else {
		detachInterrupt(pin);
	}

}

void attachInterrupt(uint32_t pin, voidFuncPtr callback, uint32_t mode)
{
	gpio_flags_t pinmode = 0;
	gpio_pin_get_config(w_pin2port(pin), w_pin2portpin(pin), &pinmode);
	w_configure_gpio_interrupt(pin, callback, mode, pinmode, 0);
}

void detachInterrupt(uint32_t pin)
{
	w_set_gpio_callback(pin, NULL);
}

void pinMode( uint32_t dwPin, uint32_t dwMode )
{
	w_configure_gpio_interrupt(dwPin, NULL, -1, dwMode, 0);
}


void digitalWrite( uint32_t ulPin, uint32_t ulVal )
{
	gpio_pin_set(w_pin2port(ulPin), w_pin2portpin(ulPin), ulVal ? 1 : 0);
}

int digitalRead( uint32_t ulPin )
{
	return gpio_pin_get(w_pin2port(ulPin), w_pin2portpin(ulPin)) ? 1 : 0;
}
