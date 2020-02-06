#include "Arduino.h"
#include "UartDevice.h"
#include <zephyr.h>
#include <device.h>

#if defined(CONFIG_UART_INTERRUPT_DRIVEN) && (CONFIG_UART_INTERRUPT_DRIVEN != 0)

Uart Serial0(device_get_binding(DT_UART_0_NAME));
Uart& Serial = Serial0;

#endif
