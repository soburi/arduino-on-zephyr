#pragma once

#include <stdint.h>
#include "wiring_constants.h"
#include "variant.h"
#include <zephyr/sys/util_loops.h>
#include <zephyr/devicetree.h>

#if !defined(PRIMARY_SERIAL_NO)
#define PRIMARY_SERIAL_NO 0
#endif

#if !defined(PORT_MONITOR_SERIAL_NO)
#define PORT_MONITOR_SERIAL_NO 0
#endif

#if !defined(PORT_HARDWARE_SERIAL_NO)
#define PORT_HARDWARE_SERIAL_NO 0
#endif

#define NUM_UART DT_NUM_INST_STATUS_OKAY(UART_COMPAT)
#define NUM_GPIOPORT DT_NUM_INST_STATUS_OKAY(GPIOPORT_COMPAT)


#define GPIOPORT_PATH_N(n) DEVICE_DT_GET(n),
#define W_GPIO_PORT_DEVICES { DT_FOREACH_STATUS_OKAY(GPIOPORT_COMPAT, GPIOPORT_PATH_N) }

#define GPIOPORT_PROP_NGPIOS_N_SUM(n) DT_PROP(n, ngpios) +
#define W_GPIO_PIN_NUM ( DT_FOREACH_STATUS_OKAY(GPIOPORT_COMPAT, GPIOPORT_PROP_NGPIOS_N_SUM) 0)

#define GPIOPORT_PROP_NGPIOS_N(n) DT_PROP(n, ngpios),
#define W_GPIO_PORT_PINNUMS { DT_FOREACH_STATUS_OKAY(GPIOPORT_COMPAT, GPIOPORT_PROP_NGPIOS_N) }


#ifdef __cplusplus
class Uart;
#define SERIAL_PORT_MONITOR _CONCAT(Serial, PORT_MONITOR_SERIAL_NO)
#define SERIAL_PORT_HARDWARE0 _CONCAT(Serial, PORT_MONITOR_SERIAL_NO)

#define EXTERN_SERIAL_N(n, _) extern Uart _CONCAT(Serial,n)
LISTIFY(NUM_UART, EXTERN_SERIAL_N, (;));
#define SERIAL_N(n, _) Uart _CONCAT(Serial,n)(DEVICE_DT_GET(DT_INST(n, UART_COMPAT)))
#define DECLARE_SERIALPORTS LISTIFY(NUM_UART, SERIAL_N, (;))
extern Uart& Serial;
#define DECLARE_PRIMARY_SERIALPORT Uart& Serial = _CONCAT(Serial, PRIMARY_SERIAL_NO);
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(PIN_A0) && PIN_A0 == 0
static const uint8_t A0 = PIN_A0;
#endif

#define GEN_LED_GPIO_N(n) GPIO_DT_SPEC_GET(n, gpios),


#define LED_TABLE { DT_FOREACH_CHILD(DT_COMPAT_GET_ANY_STATUS_OKAY(gpio_leds), GEN_LED_GPIO_N) }

extern uint32_t w_led_pin(uint32_t);
#if !defined(LED_BUILTIN)
#define LED_BUILTIN w_led_pin(0)
#endif

//#define GEN_PWM_CFG_N(n,_) CODE_COND_1((_CONCAT(PWM_PIN_,n)), ({ DEVICE_DT_GET(_CONCAT(PWM_PIN_NODE_,n)), _CONCAT(PWM_PIN_CH_,n) }), ({NULL,0}))
#define GEN_PWM_CFG_N(n,_) COND_CODE_1(_CONCAT(PWM_PIN_NODE_,n), ({ DEVICE_DT_GET(_CONCAT(PWM_PIN_NODE_,n)), _CONCAT(PWM_PIN_CH_,n) }), ({NULL,0}))
#define PWM_TABLE LISTIFY(NUM_UART, GEN_PWM_CFG_N, (,))

#ifdef __cplusplus
} // extern "C"
#endif
