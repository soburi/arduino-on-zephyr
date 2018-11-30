#include "UartACM.h"

void UartACM::begin_impl(unsigned long baud, uint16_t conf)
{
	u32_t dtr = 0;
	while (1) {
		uart_line_ctrl_get(uart, LINE_CTRL_DTR, &dtr);
		if (dtr)
			break;
	}

#if 0
	/* They are optional, we use them to test the interrupt endpoint */
	ret = uart_line_ctrl_set(uart, LINE_CTRL_DCD, 1);
	if (ret)
		printf("Failed to set DCD, ret code %d\n", ret);

	ret = uart_line_ctrl_set(uart, LINE_CTRL_DSR, 1);
	if (ret)
		printf("Failed to set DSR, ret code %d\n", ret);

	/* Wait 1 sec for the host to do all settings */
	k_busy_wait(1000000);

	ret = uart_line_ctrl_get(uart, LINE_CTRL_BAUD_RATE, &baudrate);
	if (ret)
		printf("Failed to get baudrate, ret code %d\n", ret);
	else
		printf("Baudrate detected: %d\n", baudrate);
#endif

	Uart::begin_impl(baud, conf);
}

