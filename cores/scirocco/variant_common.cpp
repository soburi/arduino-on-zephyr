#if 0
#!/bin/bash
#
# generator script
#
# Copyright (c) 2020 Tokita, Hiroshi  All right reserved.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

N=0
if [ $# -ne 0 ]; then
    N=$1
fi

function ifel() {
	if [ $1 -eq 0 ] ; then echo "#if   "
	else                   echo "#elif "
	fi
}

head -$(grep -n '^#endif.*END_OF_SCRIPT.*' $0 | sed 's/:.*$//') $0

echo
echo "/* START GENERATED SECTION */"
echo

echo "#include \"Arduino.h\""
echo "#include \"UartDevice.h\""
echo "#include <zephyr.h>"
echo "#include <device.h>"
echo
echo "#if defined(CONFIG_UART_INTERRUPT_DRIVEN) && (CONFIG_UART_INTERRUPT_DRIVEN != 0)"
echo

for I in `seq 0 $N` ; do
echo "#if defined(DT_UART_${I}_NAME)"
echo "Uart Serial${I}(device_get_binding(DT_UART_${I}_NAME));"
echo "#endif"
done

echo

for I in `seq 0 $N` ; do
echo "$(ifel ${I}) defined(DT_UART_${I}_NAME)"
echo "Uart& Serial(Serial${I});"
done
echo "#endif"

echo "#endif"

echo
echo "/* END GENERATED SECTION */"
echo
echo "#if 0"
echo "COMMENTOUT"
echo "#endif"

<<COMMENTOUT
#endif /* END_OF_SCRIPT */

/* START GENERATED SECTION */

#include "Arduino.h"
#include "UartDevice.h"
#include <zephyr.h>
#include <device.h>

#if defined(CONFIG_UART_INTERRUPT_DRIVEN) && (CONFIG_UART_INTERRUPT_DRIVEN != 0)

#if defined(DT_UART_0_NAME)
Uart Serial0(device_get_binding(DT_UART_0_NAME));
#endif
#if defined(DT_UART_1_NAME)
Uart Serial1(device_get_binding(DT_UART_1_NAME));
#endif
#if defined(DT_UART_2_NAME)
Uart Serial2(device_get_binding(DT_UART_2_NAME));
#endif
#if defined(DT_UART_3_NAME)
Uart Serial3(device_get_binding(DT_UART_3_NAME));
#endif
#if defined(DT_UART_4_NAME)
Uart Serial4(device_get_binding(DT_UART_4_NAME));
#endif
#if defined(DT_UART_5_NAME)
Uart Serial5(device_get_binding(DT_UART_5_NAME));
#endif
#if defined(DT_UART_6_NAME)
Uart Serial6(device_get_binding(DT_UART_6_NAME));
#endif
#if defined(DT_UART_7_NAME)
Uart Serial7(device_get_binding(DT_UART_7_NAME));
#endif
#if defined(DT_UART_8_NAME)
Uart Serial8(device_get_binding(DT_UART_8_NAME));
#endif
#if defined(DT_UART_9_NAME)
Uart Serial9(device_get_binding(DT_UART_9_NAME));
#endif
#if defined(DT_UART_10_NAME)
Uart Serial10(device_get_binding(DT_UART_10_NAME));
#endif
#if defined(DT_UART_11_NAME)
Uart Serial11(device_get_binding(DT_UART_11_NAME));
#endif
#if defined(DT_UART_12_NAME)
Uart Serial12(device_get_binding(DT_UART_12_NAME));
#endif
#if defined(DT_UART_13_NAME)
Uart Serial13(device_get_binding(DT_UART_13_NAME));
#endif
#if defined(DT_UART_14_NAME)
Uart Serial14(device_get_binding(DT_UART_14_NAME));
#endif
#if defined(DT_UART_15_NAME)
Uart Serial15(device_get_binding(DT_UART_15_NAME));
#endif
#if defined(DT_UART_16_NAME)
Uart Serial16(device_get_binding(DT_UART_16_NAME));
#endif
#if defined(DT_UART_17_NAME)
Uart Serial17(device_get_binding(DT_UART_17_NAME));
#endif
#if defined(DT_UART_18_NAME)
Uart Serial18(device_get_binding(DT_UART_18_NAME));
#endif
#if defined(DT_UART_19_NAME)
Uart Serial19(device_get_binding(DT_UART_19_NAME));
#endif
#if defined(DT_UART_20_NAME)
Uart Serial20(device_get_binding(DT_UART_20_NAME));
#endif
#if defined(DT_UART_21_NAME)
Uart Serial21(device_get_binding(DT_UART_21_NAME));
#endif
#if defined(DT_UART_22_NAME)
Uart Serial22(device_get_binding(DT_UART_22_NAME));
#endif
#if defined(DT_UART_23_NAME)
Uart Serial23(device_get_binding(DT_UART_23_NAME));
#endif
#if defined(DT_UART_24_NAME)
Uart Serial24(device_get_binding(DT_UART_24_NAME));
#endif
#if defined(DT_UART_25_NAME)
Uart Serial25(device_get_binding(DT_UART_25_NAME));
#endif
#if defined(DT_UART_26_NAME)
Uart Serial26(device_get_binding(DT_UART_26_NAME));
#endif
#if defined(DT_UART_27_NAME)
Uart Serial27(device_get_binding(DT_UART_27_NAME));
#endif
#if defined(DT_UART_28_NAME)
Uart Serial28(device_get_binding(DT_UART_28_NAME));
#endif
#if defined(DT_UART_29_NAME)
Uart Serial29(device_get_binding(DT_UART_29_NAME));
#endif
#if defined(DT_UART_30_NAME)
Uart Serial30(device_get_binding(DT_UART_30_NAME));
#endif
#if defined(DT_UART_31_NAME)
Uart Serial31(device_get_binding(DT_UART_31_NAME));
#endif

#if    defined(DT_UART_0_NAME)
Uart& Serial(Serial0);
#elif  defined(DT_UART_1_NAME)
Uart& Serial(Serial1);
#elif  defined(DT_UART_2_NAME)
Uart& Serial(Serial2);
#elif  defined(DT_UART_3_NAME)
Uart& Serial(Serial3);
#elif  defined(DT_UART_4_NAME)
Uart& Serial(Serial4);
#elif  defined(DT_UART_5_NAME)
Uart& Serial(Serial5);
#elif  defined(DT_UART_6_NAME)
Uart& Serial(Serial6);
#elif  defined(DT_UART_7_NAME)
Uart& Serial(Serial7);
#elif  defined(DT_UART_8_NAME)
Uart& Serial(Serial8);
#elif  defined(DT_UART_9_NAME)
Uart& Serial(Serial9);
#elif  defined(DT_UART_10_NAME)
Uart& Serial(Serial10);
#elif  defined(DT_UART_11_NAME)
Uart& Serial(Serial11);
#elif  defined(DT_UART_12_NAME)
Uart& Serial(Serial12);
#elif  defined(DT_UART_13_NAME)
Uart& Serial(Serial13);
#elif  defined(DT_UART_14_NAME)
Uart& Serial(Serial14);
#elif  defined(DT_UART_15_NAME)
Uart& Serial(Serial15);
#elif  defined(DT_UART_16_NAME)
Uart& Serial(Serial16);
#elif  defined(DT_UART_17_NAME)
Uart& Serial(Serial17);
#elif  defined(DT_UART_18_NAME)
Uart& Serial(Serial18);
#elif  defined(DT_UART_19_NAME)
Uart& Serial(Serial19);
#elif  defined(DT_UART_20_NAME)
Uart& Serial(Serial20);
#elif  defined(DT_UART_21_NAME)
Uart& Serial(Serial21);
#elif  defined(DT_UART_22_NAME)
Uart& Serial(Serial22);
#elif  defined(DT_UART_23_NAME)
Uart& Serial(Serial23);
#elif  defined(DT_UART_24_NAME)
Uart& Serial(Serial24);
#elif  defined(DT_UART_25_NAME)
Uart& Serial(Serial25);
#elif  defined(DT_UART_26_NAME)
Uart& Serial(Serial26);
#elif  defined(DT_UART_27_NAME)
Uart& Serial(Serial27);
#elif  defined(DT_UART_28_NAME)
Uart& Serial(Serial28);
#elif  defined(DT_UART_29_NAME)
Uart& Serial(Serial29);
#elif  defined(DT_UART_30_NAME)
Uart& Serial(Serial30);
#elif  defined(DT_UART_31_NAME)
Uart& Serial(Serial31);
#endif
#endif

/* END GENERATED SECTION */

#if 0
COMMENTOUT
#endif
