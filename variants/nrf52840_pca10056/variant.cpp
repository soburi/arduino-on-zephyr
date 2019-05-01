#include "Arduino.h"
#include "UartDevice.h"
#include <zephyr.h>
#include <device.h>

Uart Serial0(device_get_binding(DT_UART_0_NAME));

Uart& Serial = Serial0;
