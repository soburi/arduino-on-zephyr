#include "Arduino.h"
#include "Uart.h"
#include <zephyr.h>
#include <device.h>

#ifdef DT_CDC_ACM_PORT_NAME
UartACM SerialACM(device_get_binding(DT_CDC_ACM_PORT_NAME));
#endif
Uart Serial0(device_get_binding(DT_UART_0_NAME));

Uart& Serial = Serial0;
