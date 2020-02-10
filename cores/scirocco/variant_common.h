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

echo "#pragma once"
echo
echo "#include <stdint.h>"
echo "#include \"wiring_constants.h\""
echo
echo "#ifdef __cplusplus"
echo "class Uart;"
echo

for I in `seq 0 $N` ; do
echo "#if defined(DT_UART_${I}_NAME)"
echo "extern Uart Serial${I};"
echo "#endif"
done

echo
echo
for I in `seq 0 $N` ; do
echo "$(ifel ${I}) defined(DT_UART_${I}_NAME)"
echo "extern Uart& Serial;"
done
echo "#endif"

echo
echo "extern \"C\" {"
echo "#endif"
echo
echo "#ifndef SERIAL_PORT_MONITOR"

for I in `seq 0 $N` ; do
echo "$(ifel ${I}) defined(DT_UART_${I}_NAME)"
echo "#define SERIAL_PORT_MONITOR Serial${I};"
done
echo "#endif"

echo "#endif"
echo

for I in `seq 0 $N` ; do
echo "#ifndef SERIAL_PORT_HARDWARE${I}"
echo "#define SERIAL_PORT_HARDWARE${I} Serial${I};"
echo "#endif"
echo "#ifndef SERIAL_PORT_HARDWARE_OPEN${I}"
echo "#define SERIAL_PORT_HARDWARE_OPEN${I} Serial${I};"
echo "#endif"
done

echo

for I in `seq 0 $N`
do
echo "#ifdef PIN_A${I}"
echo "static const uint8_t A${I} = PIN_A${I};"
echo "#endif"
done

echo

for I in `seq 0 $N`
do
echo "#if defined(DT_GPIO_LEDS_LED_${I}_GPIOS_PIN) && !defined(PIN_LED${I})"
echo "#define PIN_LED${I} DT_GPIO_LEDS_LED_${I}_GPIOS_PIN"
echo "#endif"
done

echo

for I in `seq 0 $N` ; do
echo "$(ifel ${I}) defined(PIN_LED${I}) && !defined(LED_BUILTIN)"
echo "#define LED_BUILTIN PIN_LED${I}"
done
echo "#endif"

echo


for I in `seq 0 $N` ; do
echo "#if defined(DT_GPIO_P${I}_DEV_NAME)"
echo "#define W_GPIO_PORT${I}_DECL DT_GPIO_P${I}_DEV_NAME,"
echo "#else"
echo "#define W_GPIO_PORT${I}_DECL"
echo "#endif"
done

echo

echo "#ifndef W_GPIO_PORT_NAMES"
echo "#define W_GPIO_PORT_NAMES {\\"
for I in `seq 0 $N` ; do
echo "W_GPIO_PORT${I}_DECL \\"
done
echo "}"
echo "#endif"

echo

for I in `seq 0 $N` ; do
for J in `seq 0 $N` ; do
echo "#if defined(DT_ALIAS_PWM_${I}_CH${J}_PIN)"
echo "#define W_PWM${I}_PIN${J}_DECL { DT_ALIAS_PWM_${I}_CH${J}_PIN, DT_ALIAS_PWM_${I}_LABEL },"
echo "#else"
echo "#define W_PWM${I}_PIN${J}_DECL"
echo "#endif"
done
done

echo

echo "#ifndef W_PWM_PIN2DEV_MAP"
echo "#define W_PWM_PIN2DEV_MAP {\\"
for I in `seq 0 $N` ; do
for J in `seq 0 $N` ; do
echo "W_PWM${I}_PIN${J}_DECL \\"
done
done
echo "}"
echo "#endif"

echo

echo "#ifdef __cplusplus"
echo "} // extern \"C\""
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

#pragma once

#include <stdint.h>
#include "wiring_constants.h"
#include "variant.h"

#ifdef __cplusplus
class Uart;

#if defined(DT_UART_0_NAME)
extern Uart Serial0;
#endif
#if defined(DT_UART_1_NAME)
extern Uart Serial1;
#endif
#if defined(DT_UART_2_NAME)
extern Uart Serial2;
#endif
#if defined(DT_UART_3_NAME)
extern Uart Serial3;
#endif
#if defined(DT_UART_4_NAME)
extern Uart Serial4;
#endif
#if defined(DT_UART_5_NAME)
extern Uart Serial5;
#endif
#if defined(DT_UART_6_NAME)
extern Uart Serial6;
#endif
#if defined(DT_UART_7_NAME)
extern Uart Serial7;
#endif
#if defined(DT_UART_8_NAME)
extern Uart Serial8;
#endif
#if defined(DT_UART_9_NAME)
extern Uart Serial9;
#endif
#if defined(DT_UART_10_NAME)
extern Uart Serial10;
#endif
#if defined(DT_UART_11_NAME)
extern Uart Serial11;
#endif
#if defined(DT_UART_12_NAME)
extern Uart Serial12;
#endif
#if defined(DT_UART_13_NAME)
extern Uart Serial13;
#endif
#if defined(DT_UART_14_NAME)
extern Uart Serial14;
#endif
#if defined(DT_UART_15_NAME)
extern Uart Serial15;
#endif
#if defined(DT_UART_16_NAME)
extern Uart Serial16;
#endif
#if defined(DT_UART_17_NAME)
extern Uart Serial17;
#endif
#if defined(DT_UART_18_NAME)
extern Uart Serial18;
#endif
#if defined(DT_UART_19_NAME)
extern Uart Serial19;
#endif
#if defined(DT_UART_20_NAME)
extern Uart Serial20;
#endif
#if defined(DT_UART_21_NAME)
extern Uart Serial21;
#endif
#if defined(DT_UART_22_NAME)
extern Uart Serial22;
#endif
#if defined(DT_UART_23_NAME)
extern Uart Serial23;
#endif
#if defined(DT_UART_24_NAME)
extern Uart Serial24;
#endif
#if defined(DT_UART_25_NAME)
extern Uart Serial25;
#endif
#if defined(DT_UART_26_NAME)
extern Uart Serial26;
#endif
#if defined(DT_UART_27_NAME)
extern Uart Serial27;
#endif
#if defined(DT_UART_28_NAME)
extern Uart Serial28;
#endif
#if defined(DT_UART_29_NAME)
extern Uart Serial29;
#endif
#if defined(DT_UART_30_NAME)
extern Uart Serial30;
#endif
#if defined(DT_UART_31_NAME)
extern Uart Serial31;
#endif


#if    defined(DT_UART_0_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_1_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_2_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_3_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_4_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_5_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_6_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_7_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_8_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_9_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_10_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_11_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_12_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_13_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_14_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_15_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_16_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_17_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_18_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_19_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_20_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_21_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_22_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_23_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_24_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_25_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_26_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_27_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_28_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_29_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_30_NAME)
extern Uart& Serial;
#elif  defined(DT_UART_31_NAME)
extern Uart& Serial;
#endif

extern "C" {
#endif

#ifndef SERIAL_PORT_MONITOR
#if    defined(DT_UART_0_NAME)
#define SERIAL_PORT_MONITOR Serial0;
#elif  defined(DT_UART_1_NAME)
#define SERIAL_PORT_MONITOR Serial1;
#elif  defined(DT_UART_2_NAME)
#define SERIAL_PORT_MONITOR Serial2;
#elif  defined(DT_UART_3_NAME)
#define SERIAL_PORT_MONITOR Serial3;
#elif  defined(DT_UART_4_NAME)
#define SERIAL_PORT_MONITOR Serial4;
#elif  defined(DT_UART_5_NAME)
#define SERIAL_PORT_MONITOR Serial5;
#elif  defined(DT_UART_6_NAME)
#define SERIAL_PORT_MONITOR Serial6;
#elif  defined(DT_UART_7_NAME)
#define SERIAL_PORT_MONITOR Serial7;
#elif  defined(DT_UART_8_NAME)
#define SERIAL_PORT_MONITOR Serial8;
#elif  defined(DT_UART_9_NAME)
#define SERIAL_PORT_MONITOR Serial9;
#elif  defined(DT_UART_10_NAME)
#define SERIAL_PORT_MONITOR Serial10;
#elif  defined(DT_UART_11_NAME)
#define SERIAL_PORT_MONITOR Serial11;
#elif  defined(DT_UART_12_NAME)
#define SERIAL_PORT_MONITOR Serial12;
#elif  defined(DT_UART_13_NAME)
#define SERIAL_PORT_MONITOR Serial13;
#elif  defined(DT_UART_14_NAME)
#define SERIAL_PORT_MONITOR Serial14;
#elif  defined(DT_UART_15_NAME)
#define SERIAL_PORT_MONITOR Serial15;
#elif  defined(DT_UART_16_NAME)
#define SERIAL_PORT_MONITOR Serial16;
#elif  defined(DT_UART_17_NAME)
#define SERIAL_PORT_MONITOR Serial17;
#elif  defined(DT_UART_18_NAME)
#define SERIAL_PORT_MONITOR Serial18;
#elif  defined(DT_UART_19_NAME)
#define SERIAL_PORT_MONITOR Serial19;
#elif  defined(DT_UART_20_NAME)
#define SERIAL_PORT_MONITOR Serial20;
#elif  defined(DT_UART_21_NAME)
#define SERIAL_PORT_MONITOR Serial21;
#elif  defined(DT_UART_22_NAME)
#define SERIAL_PORT_MONITOR Serial22;
#elif  defined(DT_UART_23_NAME)
#define SERIAL_PORT_MONITOR Serial23;
#elif  defined(DT_UART_24_NAME)
#define SERIAL_PORT_MONITOR Serial24;
#elif  defined(DT_UART_25_NAME)
#define SERIAL_PORT_MONITOR Serial25;
#elif  defined(DT_UART_26_NAME)
#define SERIAL_PORT_MONITOR Serial26;
#elif  defined(DT_UART_27_NAME)
#define SERIAL_PORT_MONITOR Serial27;
#elif  defined(DT_UART_28_NAME)
#define SERIAL_PORT_MONITOR Serial28;
#elif  defined(DT_UART_29_NAME)
#define SERIAL_PORT_MONITOR Serial29;
#elif  defined(DT_UART_30_NAME)
#define SERIAL_PORT_MONITOR Serial30;
#elif  defined(DT_UART_31_NAME)
#define SERIAL_PORT_MONITOR Serial31;
#endif
#endif

#ifndef SERIAL_PORT_HARDWARE0
#define SERIAL_PORT_HARDWARE0 Serial0;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN0
#define SERIAL_PORT_HARDWARE_OPEN0 Serial0;
#endif
#ifndef SERIAL_PORT_HARDWARE1
#define SERIAL_PORT_HARDWARE1 Serial1;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN1
#define SERIAL_PORT_HARDWARE_OPEN1 Serial1;
#endif
#ifndef SERIAL_PORT_HARDWARE2
#define SERIAL_PORT_HARDWARE2 Serial2;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN2
#define SERIAL_PORT_HARDWARE_OPEN2 Serial2;
#endif
#ifndef SERIAL_PORT_HARDWARE3
#define SERIAL_PORT_HARDWARE3 Serial3;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN3
#define SERIAL_PORT_HARDWARE_OPEN3 Serial3;
#endif
#ifndef SERIAL_PORT_HARDWARE4
#define SERIAL_PORT_HARDWARE4 Serial4;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN4
#define SERIAL_PORT_HARDWARE_OPEN4 Serial4;
#endif
#ifndef SERIAL_PORT_HARDWARE5
#define SERIAL_PORT_HARDWARE5 Serial5;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN5
#define SERIAL_PORT_HARDWARE_OPEN5 Serial5;
#endif
#ifndef SERIAL_PORT_HARDWARE6
#define SERIAL_PORT_HARDWARE6 Serial6;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN6
#define SERIAL_PORT_HARDWARE_OPEN6 Serial6;
#endif
#ifndef SERIAL_PORT_HARDWARE7
#define SERIAL_PORT_HARDWARE7 Serial7;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN7
#define SERIAL_PORT_HARDWARE_OPEN7 Serial7;
#endif
#ifndef SERIAL_PORT_HARDWARE8
#define SERIAL_PORT_HARDWARE8 Serial8;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN8
#define SERIAL_PORT_HARDWARE_OPEN8 Serial8;
#endif
#ifndef SERIAL_PORT_HARDWARE9
#define SERIAL_PORT_HARDWARE9 Serial9;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN9
#define SERIAL_PORT_HARDWARE_OPEN9 Serial9;
#endif
#ifndef SERIAL_PORT_HARDWARE10
#define SERIAL_PORT_HARDWARE10 Serial10;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN10
#define SERIAL_PORT_HARDWARE_OPEN10 Serial10;
#endif
#ifndef SERIAL_PORT_HARDWARE11
#define SERIAL_PORT_HARDWARE11 Serial11;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN11
#define SERIAL_PORT_HARDWARE_OPEN11 Serial11;
#endif
#ifndef SERIAL_PORT_HARDWARE12
#define SERIAL_PORT_HARDWARE12 Serial12;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN12
#define SERIAL_PORT_HARDWARE_OPEN12 Serial12;
#endif
#ifndef SERIAL_PORT_HARDWARE13
#define SERIAL_PORT_HARDWARE13 Serial13;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN13
#define SERIAL_PORT_HARDWARE_OPEN13 Serial13;
#endif
#ifndef SERIAL_PORT_HARDWARE14
#define SERIAL_PORT_HARDWARE14 Serial14;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN14
#define SERIAL_PORT_HARDWARE_OPEN14 Serial14;
#endif
#ifndef SERIAL_PORT_HARDWARE15
#define SERIAL_PORT_HARDWARE15 Serial15;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN15
#define SERIAL_PORT_HARDWARE_OPEN15 Serial15;
#endif
#ifndef SERIAL_PORT_HARDWARE16
#define SERIAL_PORT_HARDWARE16 Serial16;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN16
#define SERIAL_PORT_HARDWARE_OPEN16 Serial16;
#endif
#ifndef SERIAL_PORT_HARDWARE17
#define SERIAL_PORT_HARDWARE17 Serial17;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN17
#define SERIAL_PORT_HARDWARE_OPEN17 Serial17;
#endif
#ifndef SERIAL_PORT_HARDWARE18
#define SERIAL_PORT_HARDWARE18 Serial18;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN18
#define SERIAL_PORT_HARDWARE_OPEN18 Serial18;
#endif
#ifndef SERIAL_PORT_HARDWARE19
#define SERIAL_PORT_HARDWARE19 Serial19;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN19
#define SERIAL_PORT_HARDWARE_OPEN19 Serial19;
#endif
#ifndef SERIAL_PORT_HARDWARE20
#define SERIAL_PORT_HARDWARE20 Serial20;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN20
#define SERIAL_PORT_HARDWARE_OPEN20 Serial20;
#endif
#ifndef SERIAL_PORT_HARDWARE21
#define SERIAL_PORT_HARDWARE21 Serial21;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN21
#define SERIAL_PORT_HARDWARE_OPEN21 Serial21;
#endif
#ifndef SERIAL_PORT_HARDWARE22
#define SERIAL_PORT_HARDWARE22 Serial22;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN22
#define SERIAL_PORT_HARDWARE_OPEN22 Serial22;
#endif
#ifndef SERIAL_PORT_HARDWARE23
#define SERIAL_PORT_HARDWARE23 Serial23;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN23
#define SERIAL_PORT_HARDWARE_OPEN23 Serial23;
#endif
#ifndef SERIAL_PORT_HARDWARE24
#define SERIAL_PORT_HARDWARE24 Serial24;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN24
#define SERIAL_PORT_HARDWARE_OPEN24 Serial24;
#endif
#ifndef SERIAL_PORT_HARDWARE25
#define SERIAL_PORT_HARDWARE25 Serial25;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN25
#define SERIAL_PORT_HARDWARE_OPEN25 Serial25;
#endif
#ifndef SERIAL_PORT_HARDWARE26
#define SERIAL_PORT_HARDWARE26 Serial26;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN26
#define SERIAL_PORT_HARDWARE_OPEN26 Serial26;
#endif
#ifndef SERIAL_PORT_HARDWARE27
#define SERIAL_PORT_HARDWARE27 Serial27;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN27
#define SERIAL_PORT_HARDWARE_OPEN27 Serial27;
#endif
#ifndef SERIAL_PORT_HARDWARE28
#define SERIAL_PORT_HARDWARE28 Serial28;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN28
#define SERIAL_PORT_HARDWARE_OPEN28 Serial28;
#endif
#ifndef SERIAL_PORT_HARDWARE29
#define SERIAL_PORT_HARDWARE29 Serial29;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN29
#define SERIAL_PORT_HARDWARE_OPEN29 Serial29;
#endif
#ifndef SERIAL_PORT_HARDWARE30
#define SERIAL_PORT_HARDWARE30 Serial30;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN30
#define SERIAL_PORT_HARDWARE_OPEN30 Serial30;
#endif
#ifndef SERIAL_PORT_HARDWARE31
#define SERIAL_PORT_HARDWARE31 Serial31;
#endif
#ifndef SERIAL_PORT_HARDWARE_OPEN31
#define SERIAL_PORT_HARDWARE_OPEN31 Serial31;
#endif

#ifdef PIN_A0
static const uint8_t A0 = PIN_A0;
#endif
#ifdef PIN_A1
static const uint8_t A1 = PIN_A1;
#endif
#ifdef PIN_A2
static const uint8_t A2 = PIN_A2;
#endif
#ifdef PIN_A3
static const uint8_t A3 = PIN_A3;
#endif
#ifdef PIN_A4
static const uint8_t A4 = PIN_A4;
#endif
#ifdef PIN_A5
static const uint8_t A5 = PIN_A5;
#endif
#ifdef PIN_A6
static const uint8_t A6 = PIN_A6;
#endif
#ifdef PIN_A7
static const uint8_t A7 = PIN_A7;
#endif
#ifdef PIN_A8
static const uint8_t A8 = PIN_A8;
#endif
#ifdef PIN_A9
static const uint8_t A9 = PIN_A9;
#endif
#ifdef PIN_A10
static const uint8_t A10 = PIN_A10;
#endif
#ifdef PIN_A11
static const uint8_t A11 = PIN_A11;
#endif
#ifdef PIN_A12
static const uint8_t A12 = PIN_A12;
#endif
#ifdef PIN_A13
static const uint8_t A13 = PIN_A13;
#endif
#ifdef PIN_A14
static const uint8_t A14 = PIN_A14;
#endif
#ifdef PIN_A15
static const uint8_t A15 = PIN_A15;
#endif
#ifdef PIN_A16
static const uint8_t A16 = PIN_A16;
#endif
#ifdef PIN_A17
static const uint8_t A17 = PIN_A17;
#endif
#ifdef PIN_A18
static const uint8_t A18 = PIN_A18;
#endif
#ifdef PIN_A19
static const uint8_t A19 = PIN_A19;
#endif
#ifdef PIN_A20
static const uint8_t A20 = PIN_A20;
#endif
#ifdef PIN_A21
static const uint8_t A21 = PIN_A21;
#endif
#ifdef PIN_A22
static const uint8_t A22 = PIN_A22;
#endif
#ifdef PIN_A23
static const uint8_t A23 = PIN_A23;
#endif
#ifdef PIN_A24
static const uint8_t A24 = PIN_A24;
#endif
#ifdef PIN_A25
static const uint8_t A25 = PIN_A25;
#endif
#ifdef PIN_A26
static const uint8_t A26 = PIN_A26;
#endif
#ifdef PIN_A27
static const uint8_t A27 = PIN_A27;
#endif
#ifdef PIN_A28
static const uint8_t A28 = PIN_A28;
#endif
#ifdef PIN_A29
static const uint8_t A29 = PIN_A29;
#endif
#ifdef PIN_A30
static const uint8_t A30 = PIN_A30;
#endif
#ifdef PIN_A31
static const uint8_t A31 = PIN_A31;
#endif

#if defined(DT_GPIO_LEDS_LED_0_GPIOS_PIN) && !defined(PIN_LED0)
#define PIN_LED0 DT_GPIO_LEDS_LED_0_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_1_GPIOS_PIN) && !defined(PIN_LED1)
#define PIN_LED1 DT_GPIO_LEDS_LED_1_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_2_GPIOS_PIN) && !defined(PIN_LED2)
#define PIN_LED2 DT_GPIO_LEDS_LED_2_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_3_GPIOS_PIN) && !defined(PIN_LED3)
#define PIN_LED3 DT_GPIO_LEDS_LED_3_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_4_GPIOS_PIN) && !defined(PIN_LED4)
#define PIN_LED4 DT_GPIO_LEDS_LED_4_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_5_GPIOS_PIN) && !defined(PIN_LED5)
#define PIN_LED5 DT_GPIO_LEDS_LED_5_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_6_GPIOS_PIN) && !defined(PIN_LED6)
#define PIN_LED6 DT_GPIO_LEDS_LED_6_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_7_GPIOS_PIN) && !defined(PIN_LED7)
#define PIN_LED7 DT_GPIO_LEDS_LED_7_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_8_GPIOS_PIN) && !defined(PIN_LED8)
#define PIN_LED8 DT_GPIO_LEDS_LED_8_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_9_GPIOS_PIN) && !defined(PIN_LED9)
#define PIN_LED9 DT_GPIO_LEDS_LED_9_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_10_GPIOS_PIN) && !defined(PIN_LED10)
#define PIN_LED10 DT_GPIO_LEDS_LED_10_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_11_GPIOS_PIN) && !defined(PIN_LED11)
#define PIN_LED11 DT_GPIO_LEDS_LED_11_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_12_GPIOS_PIN) && !defined(PIN_LED12)
#define PIN_LED12 DT_GPIO_LEDS_LED_12_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_13_GPIOS_PIN) && !defined(PIN_LED13)
#define PIN_LED13 DT_GPIO_LEDS_LED_13_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_14_GPIOS_PIN) && !defined(PIN_LED14)
#define PIN_LED14 DT_GPIO_LEDS_LED_14_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_15_GPIOS_PIN) && !defined(PIN_LED15)
#define PIN_LED15 DT_GPIO_LEDS_LED_15_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_16_GPIOS_PIN) && !defined(PIN_LED16)
#define PIN_LED16 DT_GPIO_LEDS_LED_16_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_17_GPIOS_PIN) && !defined(PIN_LED17)
#define PIN_LED17 DT_GPIO_LEDS_LED_17_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_18_GPIOS_PIN) && !defined(PIN_LED18)
#define PIN_LED18 DT_GPIO_LEDS_LED_18_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_19_GPIOS_PIN) && !defined(PIN_LED19)
#define PIN_LED19 DT_GPIO_LEDS_LED_19_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_20_GPIOS_PIN) && !defined(PIN_LED20)
#define PIN_LED20 DT_GPIO_LEDS_LED_20_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_21_GPIOS_PIN) && !defined(PIN_LED21)
#define PIN_LED21 DT_GPIO_LEDS_LED_21_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_22_GPIOS_PIN) && !defined(PIN_LED22)
#define PIN_LED22 DT_GPIO_LEDS_LED_22_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_23_GPIOS_PIN) && !defined(PIN_LED23)
#define PIN_LED23 DT_GPIO_LEDS_LED_23_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_24_GPIOS_PIN) && !defined(PIN_LED24)
#define PIN_LED24 DT_GPIO_LEDS_LED_24_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_25_GPIOS_PIN) && !defined(PIN_LED25)
#define PIN_LED25 DT_GPIO_LEDS_LED_25_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_26_GPIOS_PIN) && !defined(PIN_LED26)
#define PIN_LED26 DT_GPIO_LEDS_LED_26_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_27_GPIOS_PIN) && !defined(PIN_LED27)
#define PIN_LED27 DT_GPIO_LEDS_LED_27_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_28_GPIOS_PIN) && !defined(PIN_LED28)
#define PIN_LED28 DT_GPIO_LEDS_LED_28_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_29_GPIOS_PIN) && !defined(PIN_LED29)
#define PIN_LED29 DT_GPIO_LEDS_LED_29_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_30_GPIOS_PIN) && !defined(PIN_LED30)
#define PIN_LED30 DT_GPIO_LEDS_LED_30_GPIOS_PIN
#endif
#if defined(DT_GPIO_LEDS_LED_31_GPIOS_PIN) && !defined(PIN_LED31)
#define PIN_LED31 DT_GPIO_LEDS_LED_31_GPIOS_PIN
#endif

#if    defined(PIN_LED0) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED0
#elif  defined(PIN_LED1) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED1
#elif  defined(PIN_LED2) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED2
#elif  defined(PIN_LED3) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED3
#elif  defined(PIN_LED4) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED4
#elif  defined(PIN_LED5) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED5
#elif  defined(PIN_LED6) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED6
#elif  defined(PIN_LED7) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED7
#elif  defined(PIN_LED8) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED8
#elif  defined(PIN_LED9) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED9
#elif  defined(PIN_LED10) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED10
#elif  defined(PIN_LED11) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED11
#elif  defined(PIN_LED12) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED12
#elif  defined(PIN_LED13) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED13
#elif  defined(PIN_LED14) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED14
#elif  defined(PIN_LED15) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED15
#elif  defined(PIN_LED16) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED16
#elif  defined(PIN_LED17) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED17
#elif  defined(PIN_LED18) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED18
#elif  defined(PIN_LED19) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED19
#elif  defined(PIN_LED20) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED20
#elif  defined(PIN_LED21) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED21
#elif  defined(PIN_LED22) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED22
#elif  defined(PIN_LED23) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED23
#elif  defined(PIN_LED24) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED24
#elif  defined(PIN_LED25) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED25
#elif  defined(PIN_LED26) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED26
#elif  defined(PIN_LED27) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED27
#elif  defined(PIN_LED28) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED28
#elif  defined(PIN_LED29) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED29
#elif  defined(PIN_LED30) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED30
#elif  defined(PIN_LED31) && !defined(LED_BUILTIN)
#define LED_BUILTIN PIN_LED31
#endif

#if defined(DT_GPIO_P0_DEV_NAME)
#define W_GPIO_PORT0_DECL DT_GPIO_P0_DEV_NAME,
#else
#define W_GPIO_PORT0_DECL
#endif
#if defined(DT_GPIO_P1_DEV_NAME)
#define W_GPIO_PORT1_DECL DT_GPIO_P1_DEV_NAME,
#else
#define W_GPIO_PORT1_DECL
#endif
#if defined(DT_GPIO_P2_DEV_NAME)
#define W_GPIO_PORT2_DECL DT_GPIO_P2_DEV_NAME,
#else
#define W_GPIO_PORT2_DECL
#endif
#if defined(DT_GPIO_P3_DEV_NAME)
#define W_GPIO_PORT3_DECL DT_GPIO_P3_DEV_NAME,
#else
#define W_GPIO_PORT3_DECL
#endif
#if defined(DT_GPIO_P4_DEV_NAME)
#define W_GPIO_PORT4_DECL DT_GPIO_P4_DEV_NAME,
#else
#define W_GPIO_PORT4_DECL
#endif
#if defined(DT_GPIO_P5_DEV_NAME)
#define W_GPIO_PORT5_DECL DT_GPIO_P5_DEV_NAME,
#else
#define W_GPIO_PORT5_DECL
#endif
#if defined(DT_GPIO_P6_DEV_NAME)
#define W_GPIO_PORT6_DECL DT_GPIO_P6_DEV_NAME,
#else
#define W_GPIO_PORT6_DECL
#endif
#if defined(DT_GPIO_P7_DEV_NAME)
#define W_GPIO_PORT7_DECL DT_GPIO_P7_DEV_NAME,
#else
#define W_GPIO_PORT7_DECL
#endif
#if defined(DT_GPIO_P8_DEV_NAME)
#define W_GPIO_PORT8_DECL DT_GPIO_P8_DEV_NAME,
#else
#define W_GPIO_PORT8_DECL
#endif
#if defined(DT_GPIO_P9_DEV_NAME)
#define W_GPIO_PORT9_DECL DT_GPIO_P9_DEV_NAME,
#else
#define W_GPIO_PORT9_DECL
#endif
#if defined(DT_GPIO_P10_DEV_NAME)
#define W_GPIO_PORT10_DECL DT_GPIO_P10_DEV_NAME,
#else
#define W_GPIO_PORT10_DECL
#endif
#if defined(DT_GPIO_P11_DEV_NAME)
#define W_GPIO_PORT11_DECL DT_GPIO_P11_DEV_NAME,
#else
#define W_GPIO_PORT11_DECL
#endif
#if defined(DT_GPIO_P12_DEV_NAME)
#define W_GPIO_PORT12_DECL DT_GPIO_P12_DEV_NAME,
#else
#define W_GPIO_PORT12_DECL
#endif
#if defined(DT_GPIO_P13_DEV_NAME)
#define W_GPIO_PORT13_DECL DT_GPIO_P13_DEV_NAME,
#else
#define W_GPIO_PORT13_DECL
#endif
#if defined(DT_GPIO_P14_DEV_NAME)
#define W_GPIO_PORT14_DECL DT_GPIO_P14_DEV_NAME,
#else
#define W_GPIO_PORT14_DECL
#endif
#if defined(DT_GPIO_P15_DEV_NAME)
#define W_GPIO_PORT15_DECL DT_GPIO_P15_DEV_NAME,
#else
#define W_GPIO_PORT15_DECL
#endif
#if defined(DT_GPIO_P16_DEV_NAME)
#define W_GPIO_PORT16_DECL DT_GPIO_P16_DEV_NAME,
#else
#define W_GPIO_PORT16_DECL
#endif
#if defined(DT_GPIO_P17_DEV_NAME)
#define W_GPIO_PORT17_DECL DT_GPIO_P17_DEV_NAME,
#else
#define W_GPIO_PORT17_DECL
#endif
#if defined(DT_GPIO_P18_DEV_NAME)
#define W_GPIO_PORT18_DECL DT_GPIO_P18_DEV_NAME,
#else
#define W_GPIO_PORT18_DECL
#endif
#if defined(DT_GPIO_P19_DEV_NAME)
#define W_GPIO_PORT19_DECL DT_GPIO_P19_DEV_NAME,
#else
#define W_GPIO_PORT19_DECL
#endif
#if defined(DT_GPIO_P20_DEV_NAME)
#define W_GPIO_PORT20_DECL DT_GPIO_P20_DEV_NAME,
#else
#define W_GPIO_PORT20_DECL
#endif
#if defined(DT_GPIO_P21_DEV_NAME)
#define W_GPIO_PORT21_DECL DT_GPIO_P21_DEV_NAME,
#else
#define W_GPIO_PORT21_DECL
#endif
#if defined(DT_GPIO_P22_DEV_NAME)
#define W_GPIO_PORT22_DECL DT_GPIO_P22_DEV_NAME,
#else
#define W_GPIO_PORT22_DECL
#endif
#if defined(DT_GPIO_P23_DEV_NAME)
#define W_GPIO_PORT23_DECL DT_GPIO_P23_DEV_NAME,
#else
#define W_GPIO_PORT23_DECL
#endif
#if defined(DT_GPIO_P24_DEV_NAME)
#define W_GPIO_PORT24_DECL DT_GPIO_P24_DEV_NAME,
#else
#define W_GPIO_PORT24_DECL
#endif
#if defined(DT_GPIO_P25_DEV_NAME)
#define W_GPIO_PORT25_DECL DT_GPIO_P25_DEV_NAME,
#else
#define W_GPIO_PORT25_DECL
#endif
#if defined(DT_GPIO_P26_DEV_NAME)
#define W_GPIO_PORT26_DECL DT_GPIO_P26_DEV_NAME,
#else
#define W_GPIO_PORT26_DECL
#endif
#if defined(DT_GPIO_P27_DEV_NAME)
#define W_GPIO_PORT27_DECL DT_GPIO_P27_DEV_NAME,
#else
#define W_GPIO_PORT27_DECL
#endif
#if defined(DT_GPIO_P28_DEV_NAME)
#define W_GPIO_PORT28_DECL DT_GPIO_P28_DEV_NAME,
#else
#define W_GPIO_PORT28_DECL
#endif
#if defined(DT_GPIO_P29_DEV_NAME)
#define W_GPIO_PORT29_DECL DT_GPIO_P29_DEV_NAME,
#else
#define W_GPIO_PORT29_DECL
#endif
#if defined(DT_GPIO_P30_DEV_NAME)
#define W_GPIO_PORT30_DECL DT_GPIO_P30_DEV_NAME,
#else
#define W_GPIO_PORT30_DECL
#endif
#if defined(DT_GPIO_P31_DEV_NAME)
#define W_GPIO_PORT31_DECL DT_GPIO_P31_DEV_NAME,
#else
#define W_GPIO_PORT31_DECL
#endif

#ifndef W_GPIO_PORT_NAMES
#define W_GPIO_PORT_NAMES {\
W_GPIO_PORT0_DECL \
W_GPIO_PORT1_DECL \
W_GPIO_PORT2_DECL \
W_GPIO_PORT3_DECL \
W_GPIO_PORT4_DECL \
W_GPIO_PORT5_DECL \
W_GPIO_PORT6_DECL \
W_GPIO_PORT7_DECL \
W_GPIO_PORT8_DECL \
W_GPIO_PORT9_DECL \
W_GPIO_PORT10_DECL \
W_GPIO_PORT11_DECL \
W_GPIO_PORT12_DECL \
W_GPIO_PORT13_DECL \
W_GPIO_PORT14_DECL \
W_GPIO_PORT15_DECL \
W_GPIO_PORT16_DECL \
W_GPIO_PORT17_DECL \
W_GPIO_PORT18_DECL \
W_GPIO_PORT19_DECL \
W_GPIO_PORT20_DECL \
W_GPIO_PORT21_DECL \
W_GPIO_PORT22_DECL \
W_GPIO_PORT23_DECL \
W_GPIO_PORT24_DECL \
W_GPIO_PORT25_DECL \
W_GPIO_PORT26_DECL \
W_GPIO_PORT27_DECL \
W_GPIO_PORT28_DECL \
W_GPIO_PORT29_DECL \
W_GPIO_PORT30_DECL \
W_GPIO_PORT31_DECL \
}
#endif

#if defined(DT_ALIAS_PWM_0_CH0_PIN)
#define W_PWM0_PIN0_DECL { DT_ALIAS_PWM_0_CH0_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH1_PIN)
#define W_PWM0_PIN1_DECL { DT_ALIAS_PWM_0_CH1_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH2_PIN)
#define W_PWM0_PIN2_DECL { DT_ALIAS_PWM_0_CH2_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH3_PIN)
#define W_PWM0_PIN3_DECL { DT_ALIAS_PWM_0_CH3_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH4_PIN)
#define W_PWM0_PIN4_DECL { DT_ALIAS_PWM_0_CH4_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH5_PIN)
#define W_PWM0_PIN5_DECL { DT_ALIAS_PWM_0_CH5_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH6_PIN)
#define W_PWM0_PIN6_DECL { DT_ALIAS_PWM_0_CH6_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH7_PIN)
#define W_PWM0_PIN7_DECL { DT_ALIAS_PWM_0_CH7_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH8_PIN)
#define W_PWM0_PIN8_DECL { DT_ALIAS_PWM_0_CH8_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH9_PIN)
#define W_PWM0_PIN9_DECL { DT_ALIAS_PWM_0_CH9_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH10_PIN)
#define W_PWM0_PIN10_DECL { DT_ALIAS_PWM_0_CH10_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH11_PIN)
#define W_PWM0_PIN11_DECL { DT_ALIAS_PWM_0_CH11_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH12_PIN)
#define W_PWM0_PIN12_DECL { DT_ALIAS_PWM_0_CH12_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH13_PIN)
#define W_PWM0_PIN13_DECL { DT_ALIAS_PWM_0_CH13_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH14_PIN)
#define W_PWM0_PIN14_DECL { DT_ALIAS_PWM_0_CH14_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH15_PIN)
#define W_PWM0_PIN15_DECL { DT_ALIAS_PWM_0_CH15_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH16_PIN)
#define W_PWM0_PIN16_DECL { DT_ALIAS_PWM_0_CH16_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH17_PIN)
#define W_PWM0_PIN17_DECL { DT_ALIAS_PWM_0_CH17_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH18_PIN)
#define W_PWM0_PIN18_DECL { DT_ALIAS_PWM_0_CH18_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH19_PIN)
#define W_PWM0_PIN19_DECL { DT_ALIAS_PWM_0_CH19_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH20_PIN)
#define W_PWM0_PIN20_DECL { DT_ALIAS_PWM_0_CH20_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH21_PIN)
#define W_PWM0_PIN21_DECL { DT_ALIAS_PWM_0_CH21_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH22_PIN)
#define W_PWM0_PIN22_DECL { DT_ALIAS_PWM_0_CH22_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH23_PIN)
#define W_PWM0_PIN23_DECL { DT_ALIAS_PWM_0_CH23_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH24_PIN)
#define W_PWM0_PIN24_DECL { DT_ALIAS_PWM_0_CH24_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH25_PIN)
#define W_PWM0_PIN25_DECL { DT_ALIAS_PWM_0_CH25_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH26_PIN)
#define W_PWM0_PIN26_DECL { DT_ALIAS_PWM_0_CH26_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH27_PIN)
#define W_PWM0_PIN27_DECL { DT_ALIAS_PWM_0_CH27_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH28_PIN)
#define W_PWM0_PIN28_DECL { DT_ALIAS_PWM_0_CH28_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH29_PIN)
#define W_PWM0_PIN29_DECL { DT_ALIAS_PWM_0_CH29_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH30_PIN)
#define W_PWM0_PIN30_DECL { DT_ALIAS_PWM_0_CH30_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_0_CH31_PIN)
#define W_PWM0_PIN31_DECL { DT_ALIAS_PWM_0_CH31_PIN, DT_ALIAS_PWM_0_LABEL },
#else
#define W_PWM0_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH0_PIN)
#define W_PWM1_PIN0_DECL { DT_ALIAS_PWM_1_CH0_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH1_PIN)
#define W_PWM1_PIN1_DECL { DT_ALIAS_PWM_1_CH1_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH2_PIN)
#define W_PWM1_PIN2_DECL { DT_ALIAS_PWM_1_CH2_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH3_PIN)
#define W_PWM1_PIN3_DECL { DT_ALIAS_PWM_1_CH3_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH4_PIN)
#define W_PWM1_PIN4_DECL { DT_ALIAS_PWM_1_CH4_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH5_PIN)
#define W_PWM1_PIN5_DECL { DT_ALIAS_PWM_1_CH5_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH6_PIN)
#define W_PWM1_PIN6_DECL { DT_ALIAS_PWM_1_CH6_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH7_PIN)
#define W_PWM1_PIN7_DECL { DT_ALIAS_PWM_1_CH7_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH8_PIN)
#define W_PWM1_PIN8_DECL { DT_ALIAS_PWM_1_CH8_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH9_PIN)
#define W_PWM1_PIN9_DECL { DT_ALIAS_PWM_1_CH9_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH10_PIN)
#define W_PWM1_PIN10_DECL { DT_ALIAS_PWM_1_CH10_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH11_PIN)
#define W_PWM1_PIN11_DECL { DT_ALIAS_PWM_1_CH11_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH12_PIN)
#define W_PWM1_PIN12_DECL { DT_ALIAS_PWM_1_CH12_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH13_PIN)
#define W_PWM1_PIN13_DECL { DT_ALIAS_PWM_1_CH13_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH14_PIN)
#define W_PWM1_PIN14_DECL { DT_ALIAS_PWM_1_CH14_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH15_PIN)
#define W_PWM1_PIN15_DECL { DT_ALIAS_PWM_1_CH15_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH16_PIN)
#define W_PWM1_PIN16_DECL { DT_ALIAS_PWM_1_CH16_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH17_PIN)
#define W_PWM1_PIN17_DECL { DT_ALIAS_PWM_1_CH17_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH18_PIN)
#define W_PWM1_PIN18_DECL { DT_ALIAS_PWM_1_CH18_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH19_PIN)
#define W_PWM1_PIN19_DECL { DT_ALIAS_PWM_1_CH19_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH20_PIN)
#define W_PWM1_PIN20_DECL { DT_ALIAS_PWM_1_CH20_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH21_PIN)
#define W_PWM1_PIN21_DECL { DT_ALIAS_PWM_1_CH21_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH22_PIN)
#define W_PWM1_PIN22_DECL { DT_ALIAS_PWM_1_CH22_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH23_PIN)
#define W_PWM1_PIN23_DECL { DT_ALIAS_PWM_1_CH23_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH24_PIN)
#define W_PWM1_PIN24_DECL { DT_ALIAS_PWM_1_CH24_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH25_PIN)
#define W_PWM1_PIN25_DECL { DT_ALIAS_PWM_1_CH25_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH26_PIN)
#define W_PWM1_PIN26_DECL { DT_ALIAS_PWM_1_CH26_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH27_PIN)
#define W_PWM1_PIN27_DECL { DT_ALIAS_PWM_1_CH27_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH28_PIN)
#define W_PWM1_PIN28_DECL { DT_ALIAS_PWM_1_CH28_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH29_PIN)
#define W_PWM1_PIN29_DECL { DT_ALIAS_PWM_1_CH29_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH30_PIN)
#define W_PWM1_PIN30_DECL { DT_ALIAS_PWM_1_CH30_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_1_CH31_PIN)
#define W_PWM1_PIN31_DECL { DT_ALIAS_PWM_1_CH31_PIN, DT_ALIAS_PWM_1_LABEL },
#else
#define W_PWM1_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH0_PIN)
#define W_PWM2_PIN0_DECL { DT_ALIAS_PWM_2_CH0_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH1_PIN)
#define W_PWM2_PIN1_DECL { DT_ALIAS_PWM_2_CH1_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH2_PIN)
#define W_PWM2_PIN2_DECL { DT_ALIAS_PWM_2_CH2_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH3_PIN)
#define W_PWM2_PIN3_DECL { DT_ALIAS_PWM_2_CH3_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH4_PIN)
#define W_PWM2_PIN4_DECL { DT_ALIAS_PWM_2_CH4_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH5_PIN)
#define W_PWM2_PIN5_DECL { DT_ALIAS_PWM_2_CH5_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH6_PIN)
#define W_PWM2_PIN6_DECL { DT_ALIAS_PWM_2_CH6_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH7_PIN)
#define W_PWM2_PIN7_DECL { DT_ALIAS_PWM_2_CH7_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH8_PIN)
#define W_PWM2_PIN8_DECL { DT_ALIAS_PWM_2_CH8_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH9_PIN)
#define W_PWM2_PIN9_DECL { DT_ALIAS_PWM_2_CH9_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH10_PIN)
#define W_PWM2_PIN10_DECL { DT_ALIAS_PWM_2_CH10_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH11_PIN)
#define W_PWM2_PIN11_DECL { DT_ALIAS_PWM_2_CH11_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH12_PIN)
#define W_PWM2_PIN12_DECL { DT_ALIAS_PWM_2_CH12_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH13_PIN)
#define W_PWM2_PIN13_DECL { DT_ALIAS_PWM_2_CH13_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH14_PIN)
#define W_PWM2_PIN14_DECL { DT_ALIAS_PWM_2_CH14_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH15_PIN)
#define W_PWM2_PIN15_DECL { DT_ALIAS_PWM_2_CH15_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH16_PIN)
#define W_PWM2_PIN16_DECL { DT_ALIAS_PWM_2_CH16_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH17_PIN)
#define W_PWM2_PIN17_DECL { DT_ALIAS_PWM_2_CH17_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH18_PIN)
#define W_PWM2_PIN18_DECL { DT_ALIAS_PWM_2_CH18_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH19_PIN)
#define W_PWM2_PIN19_DECL { DT_ALIAS_PWM_2_CH19_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH20_PIN)
#define W_PWM2_PIN20_DECL { DT_ALIAS_PWM_2_CH20_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH21_PIN)
#define W_PWM2_PIN21_DECL { DT_ALIAS_PWM_2_CH21_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH22_PIN)
#define W_PWM2_PIN22_DECL { DT_ALIAS_PWM_2_CH22_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH23_PIN)
#define W_PWM2_PIN23_DECL { DT_ALIAS_PWM_2_CH23_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH24_PIN)
#define W_PWM2_PIN24_DECL { DT_ALIAS_PWM_2_CH24_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH25_PIN)
#define W_PWM2_PIN25_DECL { DT_ALIAS_PWM_2_CH25_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH26_PIN)
#define W_PWM2_PIN26_DECL { DT_ALIAS_PWM_2_CH26_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH27_PIN)
#define W_PWM2_PIN27_DECL { DT_ALIAS_PWM_2_CH27_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH28_PIN)
#define W_PWM2_PIN28_DECL { DT_ALIAS_PWM_2_CH28_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH29_PIN)
#define W_PWM2_PIN29_DECL { DT_ALIAS_PWM_2_CH29_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH30_PIN)
#define W_PWM2_PIN30_DECL { DT_ALIAS_PWM_2_CH30_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_2_CH31_PIN)
#define W_PWM2_PIN31_DECL { DT_ALIAS_PWM_2_CH31_PIN, DT_ALIAS_PWM_2_LABEL },
#else
#define W_PWM2_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH0_PIN)
#define W_PWM3_PIN0_DECL { DT_ALIAS_PWM_3_CH0_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH1_PIN)
#define W_PWM3_PIN1_DECL { DT_ALIAS_PWM_3_CH1_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH2_PIN)
#define W_PWM3_PIN2_DECL { DT_ALIAS_PWM_3_CH2_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH3_PIN)
#define W_PWM3_PIN3_DECL { DT_ALIAS_PWM_3_CH3_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH4_PIN)
#define W_PWM3_PIN4_DECL { DT_ALIAS_PWM_3_CH4_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH5_PIN)
#define W_PWM3_PIN5_DECL { DT_ALIAS_PWM_3_CH5_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH6_PIN)
#define W_PWM3_PIN6_DECL { DT_ALIAS_PWM_3_CH6_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH7_PIN)
#define W_PWM3_PIN7_DECL { DT_ALIAS_PWM_3_CH7_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH8_PIN)
#define W_PWM3_PIN8_DECL { DT_ALIAS_PWM_3_CH8_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH9_PIN)
#define W_PWM3_PIN9_DECL { DT_ALIAS_PWM_3_CH9_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH10_PIN)
#define W_PWM3_PIN10_DECL { DT_ALIAS_PWM_3_CH10_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH11_PIN)
#define W_PWM3_PIN11_DECL { DT_ALIAS_PWM_3_CH11_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH12_PIN)
#define W_PWM3_PIN12_DECL { DT_ALIAS_PWM_3_CH12_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH13_PIN)
#define W_PWM3_PIN13_DECL { DT_ALIAS_PWM_3_CH13_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH14_PIN)
#define W_PWM3_PIN14_DECL { DT_ALIAS_PWM_3_CH14_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH15_PIN)
#define W_PWM3_PIN15_DECL { DT_ALIAS_PWM_3_CH15_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH16_PIN)
#define W_PWM3_PIN16_DECL { DT_ALIAS_PWM_3_CH16_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH17_PIN)
#define W_PWM3_PIN17_DECL { DT_ALIAS_PWM_3_CH17_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH18_PIN)
#define W_PWM3_PIN18_DECL { DT_ALIAS_PWM_3_CH18_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH19_PIN)
#define W_PWM3_PIN19_DECL { DT_ALIAS_PWM_3_CH19_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH20_PIN)
#define W_PWM3_PIN20_DECL { DT_ALIAS_PWM_3_CH20_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH21_PIN)
#define W_PWM3_PIN21_DECL { DT_ALIAS_PWM_3_CH21_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH22_PIN)
#define W_PWM3_PIN22_DECL { DT_ALIAS_PWM_3_CH22_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH23_PIN)
#define W_PWM3_PIN23_DECL { DT_ALIAS_PWM_3_CH23_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH24_PIN)
#define W_PWM3_PIN24_DECL { DT_ALIAS_PWM_3_CH24_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH25_PIN)
#define W_PWM3_PIN25_DECL { DT_ALIAS_PWM_3_CH25_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH26_PIN)
#define W_PWM3_PIN26_DECL { DT_ALIAS_PWM_3_CH26_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH27_PIN)
#define W_PWM3_PIN27_DECL { DT_ALIAS_PWM_3_CH27_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH28_PIN)
#define W_PWM3_PIN28_DECL { DT_ALIAS_PWM_3_CH28_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH29_PIN)
#define W_PWM3_PIN29_DECL { DT_ALIAS_PWM_3_CH29_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH30_PIN)
#define W_PWM3_PIN30_DECL { DT_ALIAS_PWM_3_CH30_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_3_CH31_PIN)
#define W_PWM3_PIN31_DECL { DT_ALIAS_PWM_3_CH31_PIN, DT_ALIAS_PWM_3_LABEL },
#else
#define W_PWM3_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH0_PIN)
#define W_PWM4_PIN0_DECL { DT_ALIAS_PWM_4_CH0_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH1_PIN)
#define W_PWM4_PIN1_DECL { DT_ALIAS_PWM_4_CH1_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH2_PIN)
#define W_PWM4_PIN2_DECL { DT_ALIAS_PWM_4_CH2_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH3_PIN)
#define W_PWM4_PIN3_DECL { DT_ALIAS_PWM_4_CH3_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH4_PIN)
#define W_PWM4_PIN4_DECL { DT_ALIAS_PWM_4_CH4_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH5_PIN)
#define W_PWM4_PIN5_DECL { DT_ALIAS_PWM_4_CH5_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH6_PIN)
#define W_PWM4_PIN6_DECL { DT_ALIAS_PWM_4_CH6_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH7_PIN)
#define W_PWM4_PIN7_DECL { DT_ALIAS_PWM_4_CH7_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH8_PIN)
#define W_PWM4_PIN8_DECL { DT_ALIAS_PWM_4_CH8_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH9_PIN)
#define W_PWM4_PIN9_DECL { DT_ALIAS_PWM_4_CH9_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH10_PIN)
#define W_PWM4_PIN10_DECL { DT_ALIAS_PWM_4_CH10_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH11_PIN)
#define W_PWM4_PIN11_DECL { DT_ALIAS_PWM_4_CH11_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH12_PIN)
#define W_PWM4_PIN12_DECL { DT_ALIAS_PWM_4_CH12_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH13_PIN)
#define W_PWM4_PIN13_DECL { DT_ALIAS_PWM_4_CH13_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH14_PIN)
#define W_PWM4_PIN14_DECL { DT_ALIAS_PWM_4_CH14_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH15_PIN)
#define W_PWM4_PIN15_DECL { DT_ALIAS_PWM_4_CH15_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH16_PIN)
#define W_PWM4_PIN16_DECL { DT_ALIAS_PWM_4_CH16_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH17_PIN)
#define W_PWM4_PIN17_DECL { DT_ALIAS_PWM_4_CH17_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH18_PIN)
#define W_PWM4_PIN18_DECL { DT_ALIAS_PWM_4_CH18_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH19_PIN)
#define W_PWM4_PIN19_DECL { DT_ALIAS_PWM_4_CH19_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH20_PIN)
#define W_PWM4_PIN20_DECL { DT_ALIAS_PWM_4_CH20_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH21_PIN)
#define W_PWM4_PIN21_DECL { DT_ALIAS_PWM_4_CH21_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH22_PIN)
#define W_PWM4_PIN22_DECL { DT_ALIAS_PWM_4_CH22_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH23_PIN)
#define W_PWM4_PIN23_DECL { DT_ALIAS_PWM_4_CH23_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH24_PIN)
#define W_PWM4_PIN24_DECL { DT_ALIAS_PWM_4_CH24_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH25_PIN)
#define W_PWM4_PIN25_DECL { DT_ALIAS_PWM_4_CH25_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH26_PIN)
#define W_PWM4_PIN26_DECL { DT_ALIAS_PWM_4_CH26_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH27_PIN)
#define W_PWM4_PIN27_DECL { DT_ALIAS_PWM_4_CH27_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH28_PIN)
#define W_PWM4_PIN28_DECL { DT_ALIAS_PWM_4_CH28_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH29_PIN)
#define W_PWM4_PIN29_DECL { DT_ALIAS_PWM_4_CH29_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH30_PIN)
#define W_PWM4_PIN30_DECL { DT_ALIAS_PWM_4_CH30_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_4_CH31_PIN)
#define W_PWM4_PIN31_DECL { DT_ALIAS_PWM_4_CH31_PIN, DT_ALIAS_PWM_4_LABEL },
#else
#define W_PWM4_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH0_PIN)
#define W_PWM5_PIN0_DECL { DT_ALIAS_PWM_5_CH0_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH1_PIN)
#define W_PWM5_PIN1_DECL { DT_ALIAS_PWM_5_CH1_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH2_PIN)
#define W_PWM5_PIN2_DECL { DT_ALIAS_PWM_5_CH2_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH3_PIN)
#define W_PWM5_PIN3_DECL { DT_ALIAS_PWM_5_CH3_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH4_PIN)
#define W_PWM5_PIN4_DECL { DT_ALIAS_PWM_5_CH4_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH5_PIN)
#define W_PWM5_PIN5_DECL { DT_ALIAS_PWM_5_CH5_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH6_PIN)
#define W_PWM5_PIN6_DECL { DT_ALIAS_PWM_5_CH6_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH7_PIN)
#define W_PWM5_PIN7_DECL { DT_ALIAS_PWM_5_CH7_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH8_PIN)
#define W_PWM5_PIN8_DECL { DT_ALIAS_PWM_5_CH8_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH9_PIN)
#define W_PWM5_PIN9_DECL { DT_ALIAS_PWM_5_CH9_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH10_PIN)
#define W_PWM5_PIN10_DECL { DT_ALIAS_PWM_5_CH10_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH11_PIN)
#define W_PWM5_PIN11_DECL { DT_ALIAS_PWM_5_CH11_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH12_PIN)
#define W_PWM5_PIN12_DECL { DT_ALIAS_PWM_5_CH12_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH13_PIN)
#define W_PWM5_PIN13_DECL { DT_ALIAS_PWM_5_CH13_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH14_PIN)
#define W_PWM5_PIN14_DECL { DT_ALIAS_PWM_5_CH14_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH15_PIN)
#define W_PWM5_PIN15_DECL { DT_ALIAS_PWM_5_CH15_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH16_PIN)
#define W_PWM5_PIN16_DECL { DT_ALIAS_PWM_5_CH16_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH17_PIN)
#define W_PWM5_PIN17_DECL { DT_ALIAS_PWM_5_CH17_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH18_PIN)
#define W_PWM5_PIN18_DECL { DT_ALIAS_PWM_5_CH18_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH19_PIN)
#define W_PWM5_PIN19_DECL { DT_ALIAS_PWM_5_CH19_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH20_PIN)
#define W_PWM5_PIN20_DECL { DT_ALIAS_PWM_5_CH20_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH21_PIN)
#define W_PWM5_PIN21_DECL { DT_ALIAS_PWM_5_CH21_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH22_PIN)
#define W_PWM5_PIN22_DECL { DT_ALIAS_PWM_5_CH22_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH23_PIN)
#define W_PWM5_PIN23_DECL { DT_ALIAS_PWM_5_CH23_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH24_PIN)
#define W_PWM5_PIN24_DECL { DT_ALIAS_PWM_5_CH24_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH25_PIN)
#define W_PWM5_PIN25_DECL { DT_ALIAS_PWM_5_CH25_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH26_PIN)
#define W_PWM5_PIN26_DECL { DT_ALIAS_PWM_5_CH26_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH27_PIN)
#define W_PWM5_PIN27_DECL { DT_ALIAS_PWM_5_CH27_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH28_PIN)
#define W_PWM5_PIN28_DECL { DT_ALIAS_PWM_5_CH28_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH29_PIN)
#define W_PWM5_PIN29_DECL { DT_ALIAS_PWM_5_CH29_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH30_PIN)
#define W_PWM5_PIN30_DECL { DT_ALIAS_PWM_5_CH30_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_5_CH31_PIN)
#define W_PWM5_PIN31_DECL { DT_ALIAS_PWM_5_CH31_PIN, DT_ALIAS_PWM_5_LABEL },
#else
#define W_PWM5_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH0_PIN)
#define W_PWM6_PIN0_DECL { DT_ALIAS_PWM_6_CH0_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH1_PIN)
#define W_PWM6_PIN1_DECL { DT_ALIAS_PWM_6_CH1_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH2_PIN)
#define W_PWM6_PIN2_DECL { DT_ALIAS_PWM_6_CH2_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH3_PIN)
#define W_PWM6_PIN3_DECL { DT_ALIAS_PWM_6_CH3_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH4_PIN)
#define W_PWM6_PIN4_DECL { DT_ALIAS_PWM_6_CH4_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH5_PIN)
#define W_PWM6_PIN5_DECL { DT_ALIAS_PWM_6_CH5_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH6_PIN)
#define W_PWM6_PIN6_DECL { DT_ALIAS_PWM_6_CH6_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH7_PIN)
#define W_PWM6_PIN7_DECL { DT_ALIAS_PWM_6_CH7_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH8_PIN)
#define W_PWM6_PIN8_DECL { DT_ALIAS_PWM_6_CH8_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH9_PIN)
#define W_PWM6_PIN9_DECL { DT_ALIAS_PWM_6_CH9_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH10_PIN)
#define W_PWM6_PIN10_DECL { DT_ALIAS_PWM_6_CH10_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH11_PIN)
#define W_PWM6_PIN11_DECL { DT_ALIAS_PWM_6_CH11_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH12_PIN)
#define W_PWM6_PIN12_DECL { DT_ALIAS_PWM_6_CH12_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH13_PIN)
#define W_PWM6_PIN13_DECL { DT_ALIAS_PWM_6_CH13_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH14_PIN)
#define W_PWM6_PIN14_DECL { DT_ALIAS_PWM_6_CH14_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH15_PIN)
#define W_PWM6_PIN15_DECL { DT_ALIAS_PWM_6_CH15_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH16_PIN)
#define W_PWM6_PIN16_DECL { DT_ALIAS_PWM_6_CH16_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH17_PIN)
#define W_PWM6_PIN17_DECL { DT_ALIAS_PWM_6_CH17_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH18_PIN)
#define W_PWM6_PIN18_DECL { DT_ALIAS_PWM_6_CH18_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH19_PIN)
#define W_PWM6_PIN19_DECL { DT_ALIAS_PWM_6_CH19_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH20_PIN)
#define W_PWM6_PIN20_DECL { DT_ALIAS_PWM_6_CH20_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH21_PIN)
#define W_PWM6_PIN21_DECL { DT_ALIAS_PWM_6_CH21_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH22_PIN)
#define W_PWM6_PIN22_DECL { DT_ALIAS_PWM_6_CH22_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH23_PIN)
#define W_PWM6_PIN23_DECL { DT_ALIAS_PWM_6_CH23_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH24_PIN)
#define W_PWM6_PIN24_DECL { DT_ALIAS_PWM_6_CH24_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH25_PIN)
#define W_PWM6_PIN25_DECL { DT_ALIAS_PWM_6_CH25_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH26_PIN)
#define W_PWM6_PIN26_DECL { DT_ALIAS_PWM_6_CH26_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH27_PIN)
#define W_PWM6_PIN27_DECL { DT_ALIAS_PWM_6_CH27_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH28_PIN)
#define W_PWM6_PIN28_DECL { DT_ALIAS_PWM_6_CH28_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH29_PIN)
#define W_PWM6_PIN29_DECL { DT_ALIAS_PWM_6_CH29_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH30_PIN)
#define W_PWM6_PIN30_DECL { DT_ALIAS_PWM_6_CH30_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_6_CH31_PIN)
#define W_PWM6_PIN31_DECL { DT_ALIAS_PWM_6_CH31_PIN, DT_ALIAS_PWM_6_LABEL },
#else
#define W_PWM6_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH0_PIN)
#define W_PWM7_PIN0_DECL { DT_ALIAS_PWM_7_CH0_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH1_PIN)
#define W_PWM7_PIN1_DECL { DT_ALIAS_PWM_7_CH1_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH2_PIN)
#define W_PWM7_PIN2_DECL { DT_ALIAS_PWM_7_CH2_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH3_PIN)
#define W_PWM7_PIN3_DECL { DT_ALIAS_PWM_7_CH3_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH4_PIN)
#define W_PWM7_PIN4_DECL { DT_ALIAS_PWM_7_CH4_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH5_PIN)
#define W_PWM7_PIN5_DECL { DT_ALIAS_PWM_7_CH5_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH6_PIN)
#define W_PWM7_PIN6_DECL { DT_ALIAS_PWM_7_CH6_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH7_PIN)
#define W_PWM7_PIN7_DECL { DT_ALIAS_PWM_7_CH7_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH8_PIN)
#define W_PWM7_PIN8_DECL { DT_ALIAS_PWM_7_CH8_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH9_PIN)
#define W_PWM7_PIN9_DECL { DT_ALIAS_PWM_7_CH9_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH10_PIN)
#define W_PWM7_PIN10_DECL { DT_ALIAS_PWM_7_CH10_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH11_PIN)
#define W_PWM7_PIN11_DECL { DT_ALIAS_PWM_7_CH11_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH12_PIN)
#define W_PWM7_PIN12_DECL { DT_ALIAS_PWM_7_CH12_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH13_PIN)
#define W_PWM7_PIN13_DECL { DT_ALIAS_PWM_7_CH13_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH14_PIN)
#define W_PWM7_PIN14_DECL { DT_ALIAS_PWM_7_CH14_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH15_PIN)
#define W_PWM7_PIN15_DECL { DT_ALIAS_PWM_7_CH15_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH16_PIN)
#define W_PWM7_PIN16_DECL { DT_ALIAS_PWM_7_CH16_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH17_PIN)
#define W_PWM7_PIN17_DECL { DT_ALIAS_PWM_7_CH17_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH18_PIN)
#define W_PWM7_PIN18_DECL { DT_ALIAS_PWM_7_CH18_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH19_PIN)
#define W_PWM7_PIN19_DECL { DT_ALIAS_PWM_7_CH19_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH20_PIN)
#define W_PWM7_PIN20_DECL { DT_ALIAS_PWM_7_CH20_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH21_PIN)
#define W_PWM7_PIN21_DECL { DT_ALIAS_PWM_7_CH21_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH22_PIN)
#define W_PWM7_PIN22_DECL { DT_ALIAS_PWM_7_CH22_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH23_PIN)
#define W_PWM7_PIN23_DECL { DT_ALIAS_PWM_7_CH23_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH24_PIN)
#define W_PWM7_PIN24_DECL { DT_ALIAS_PWM_7_CH24_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH25_PIN)
#define W_PWM7_PIN25_DECL { DT_ALIAS_PWM_7_CH25_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH26_PIN)
#define W_PWM7_PIN26_DECL { DT_ALIAS_PWM_7_CH26_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH27_PIN)
#define W_PWM7_PIN27_DECL { DT_ALIAS_PWM_7_CH27_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH28_PIN)
#define W_PWM7_PIN28_DECL { DT_ALIAS_PWM_7_CH28_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH29_PIN)
#define W_PWM7_PIN29_DECL { DT_ALIAS_PWM_7_CH29_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH30_PIN)
#define W_PWM7_PIN30_DECL { DT_ALIAS_PWM_7_CH30_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_7_CH31_PIN)
#define W_PWM7_PIN31_DECL { DT_ALIAS_PWM_7_CH31_PIN, DT_ALIAS_PWM_7_LABEL },
#else
#define W_PWM7_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH0_PIN)
#define W_PWM8_PIN0_DECL { DT_ALIAS_PWM_8_CH0_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH1_PIN)
#define W_PWM8_PIN1_DECL { DT_ALIAS_PWM_8_CH1_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH2_PIN)
#define W_PWM8_PIN2_DECL { DT_ALIAS_PWM_8_CH2_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH3_PIN)
#define W_PWM8_PIN3_DECL { DT_ALIAS_PWM_8_CH3_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH4_PIN)
#define W_PWM8_PIN4_DECL { DT_ALIAS_PWM_8_CH4_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH5_PIN)
#define W_PWM8_PIN5_DECL { DT_ALIAS_PWM_8_CH5_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH6_PIN)
#define W_PWM8_PIN6_DECL { DT_ALIAS_PWM_8_CH6_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH7_PIN)
#define W_PWM8_PIN7_DECL { DT_ALIAS_PWM_8_CH7_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH8_PIN)
#define W_PWM8_PIN8_DECL { DT_ALIAS_PWM_8_CH8_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH9_PIN)
#define W_PWM8_PIN9_DECL { DT_ALIAS_PWM_8_CH9_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH10_PIN)
#define W_PWM8_PIN10_DECL { DT_ALIAS_PWM_8_CH10_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH11_PIN)
#define W_PWM8_PIN11_DECL { DT_ALIAS_PWM_8_CH11_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH12_PIN)
#define W_PWM8_PIN12_DECL { DT_ALIAS_PWM_8_CH12_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH13_PIN)
#define W_PWM8_PIN13_DECL { DT_ALIAS_PWM_8_CH13_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH14_PIN)
#define W_PWM8_PIN14_DECL { DT_ALIAS_PWM_8_CH14_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH15_PIN)
#define W_PWM8_PIN15_DECL { DT_ALIAS_PWM_8_CH15_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH16_PIN)
#define W_PWM8_PIN16_DECL { DT_ALIAS_PWM_8_CH16_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH17_PIN)
#define W_PWM8_PIN17_DECL { DT_ALIAS_PWM_8_CH17_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH18_PIN)
#define W_PWM8_PIN18_DECL { DT_ALIAS_PWM_8_CH18_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH19_PIN)
#define W_PWM8_PIN19_DECL { DT_ALIAS_PWM_8_CH19_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH20_PIN)
#define W_PWM8_PIN20_DECL { DT_ALIAS_PWM_8_CH20_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH21_PIN)
#define W_PWM8_PIN21_DECL { DT_ALIAS_PWM_8_CH21_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH22_PIN)
#define W_PWM8_PIN22_DECL { DT_ALIAS_PWM_8_CH22_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH23_PIN)
#define W_PWM8_PIN23_DECL { DT_ALIAS_PWM_8_CH23_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH24_PIN)
#define W_PWM8_PIN24_DECL { DT_ALIAS_PWM_8_CH24_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH25_PIN)
#define W_PWM8_PIN25_DECL { DT_ALIAS_PWM_8_CH25_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH26_PIN)
#define W_PWM8_PIN26_DECL { DT_ALIAS_PWM_8_CH26_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH27_PIN)
#define W_PWM8_PIN27_DECL { DT_ALIAS_PWM_8_CH27_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH28_PIN)
#define W_PWM8_PIN28_DECL { DT_ALIAS_PWM_8_CH28_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH29_PIN)
#define W_PWM8_PIN29_DECL { DT_ALIAS_PWM_8_CH29_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH30_PIN)
#define W_PWM8_PIN30_DECL { DT_ALIAS_PWM_8_CH30_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_8_CH31_PIN)
#define W_PWM8_PIN31_DECL { DT_ALIAS_PWM_8_CH31_PIN, DT_ALIAS_PWM_8_LABEL },
#else
#define W_PWM8_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH0_PIN)
#define W_PWM9_PIN0_DECL { DT_ALIAS_PWM_9_CH0_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH1_PIN)
#define W_PWM9_PIN1_DECL { DT_ALIAS_PWM_9_CH1_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH2_PIN)
#define W_PWM9_PIN2_DECL { DT_ALIAS_PWM_9_CH2_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH3_PIN)
#define W_PWM9_PIN3_DECL { DT_ALIAS_PWM_9_CH3_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH4_PIN)
#define W_PWM9_PIN4_DECL { DT_ALIAS_PWM_9_CH4_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH5_PIN)
#define W_PWM9_PIN5_DECL { DT_ALIAS_PWM_9_CH5_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH6_PIN)
#define W_PWM9_PIN6_DECL { DT_ALIAS_PWM_9_CH6_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH7_PIN)
#define W_PWM9_PIN7_DECL { DT_ALIAS_PWM_9_CH7_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH8_PIN)
#define W_PWM9_PIN8_DECL { DT_ALIAS_PWM_9_CH8_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH9_PIN)
#define W_PWM9_PIN9_DECL { DT_ALIAS_PWM_9_CH9_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH10_PIN)
#define W_PWM9_PIN10_DECL { DT_ALIAS_PWM_9_CH10_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH11_PIN)
#define W_PWM9_PIN11_DECL { DT_ALIAS_PWM_9_CH11_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH12_PIN)
#define W_PWM9_PIN12_DECL { DT_ALIAS_PWM_9_CH12_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH13_PIN)
#define W_PWM9_PIN13_DECL { DT_ALIAS_PWM_9_CH13_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH14_PIN)
#define W_PWM9_PIN14_DECL { DT_ALIAS_PWM_9_CH14_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH15_PIN)
#define W_PWM9_PIN15_DECL { DT_ALIAS_PWM_9_CH15_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH16_PIN)
#define W_PWM9_PIN16_DECL { DT_ALIAS_PWM_9_CH16_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH17_PIN)
#define W_PWM9_PIN17_DECL { DT_ALIAS_PWM_9_CH17_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH18_PIN)
#define W_PWM9_PIN18_DECL { DT_ALIAS_PWM_9_CH18_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH19_PIN)
#define W_PWM9_PIN19_DECL { DT_ALIAS_PWM_9_CH19_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH20_PIN)
#define W_PWM9_PIN20_DECL { DT_ALIAS_PWM_9_CH20_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH21_PIN)
#define W_PWM9_PIN21_DECL { DT_ALIAS_PWM_9_CH21_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH22_PIN)
#define W_PWM9_PIN22_DECL { DT_ALIAS_PWM_9_CH22_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH23_PIN)
#define W_PWM9_PIN23_DECL { DT_ALIAS_PWM_9_CH23_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH24_PIN)
#define W_PWM9_PIN24_DECL { DT_ALIAS_PWM_9_CH24_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH25_PIN)
#define W_PWM9_PIN25_DECL { DT_ALIAS_PWM_9_CH25_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH26_PIN)
#define W_PWM9_PIN26_DECL { DT_ALIAS_PWM_9_CH26_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH27_PIN)
#define W_PWM9_PIN27_DECL { DT_ALIAS_PWM_9_CH27_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH28_PIN)
#define W_PWM9_PIN28_DECL { DT_ALIAS_PWM_9_CH28_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH29_PIN)
#define W_PWM9_PIN29_DECL { DT_ALIAS_PWM_9_CH29_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH30_PIN)
#define W_PWM9_PIN30_DECL { DT_ALIAS_PWM_9_CH30_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_9_CH31_PIN)
#define W_PWM9_PIN31_DECL { DT_ALIAS_PWM_9_CH31_PIN, DT_ALIAS_PWM_9_LABEL },
#else
#define W_PWM9_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH0_PIN)
#define W_PWM10_PIN0_DECL { DT_ALIAS_PWM_10_CH0_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH1_PIN)
#define W_PWM10_PIN1_DECL { DT_ALIAS_PWM_10_CH1_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH2_PIN)
#define W_PWM10_PIN2_DECL { DT_ALIAS_PWM_10_CH2_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH3_PIN)
#define W_PWM10_PIN3_DECL { DT_ALIAS_PWM_10_CH3_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH4_PIN)
#define W_PWM10_PIN4_DECL { DT_ALIAS_PWM_10_CH4_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH5_PIN)
#define W_PWM10_PIN5_DECL { DT_ALIAS_PWM_10_CH5_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH6_PIN)
#define W_PWM10_PIN6_DECL { DT_ALIAS_PWM_10_CH6_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH7_PIN)
#define W_PWM10_PIN7_DECL { DT_ALIAS_PWM_10_CH7_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH8_PIN)
#define W_PWM10_PIN8_DECL { DT_ALIAS_PWM_10_CH8_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH9_PIN)
#define W_PWM10_PIN9_DECL { DT_ALIAS_PWM_10_CH9_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH10_PIN)
#define W_PWM10_PIN10_DECL { DT_ALIAS_PWM_10_CH10_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH11_PIN)
#define W_PWM10_PIN11_DECL { DT_ALIAS_PWM_10_CH11_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH12_PIN)
#define W_PWM10_PIN12_DECL { DT_ALIAS_PWM_10_CH12_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH13_PIN)
#define W_PWM10_PIN13_DECL { DT_ALIAS_PWM_10_CH13_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH14_PIN)
#define W_PWM10_PIN14_DECL { DT_ALIAS_PWM_10_CH14_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH15_PIN)
#define W_PWM10_PIN15_DECL { DT_ALIAS_PWM_10_CH15_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH16_PIN)
#define W_PWM10_PIN16_DECL { DT_ALIAS_PWM_10_CH16_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH17_PIN)
#define W_PWM10_PIN17_DECL { DT_ALIAS_PWM_10_CH17_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH18_PIN)
#define W_PWM10_PIN18_DECL { DT_ALIAS_PWM_10_CH18_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH19_PIN)
#define W_PWM10_PIN19_DECL { DT_ALIAS_PWM_10_CH19_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH20_PIN)
#define W_PWM10_PIN20_DECL { DT_ALIAS_PWM_10_CH20_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH21_PIN)
#define W_PWM10_PIN21_DECL { DT_ALIAS_PWM_10_CH21_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH22_PIN)
#define W_PWM10_PIN22_DECL { DT_ALIAS_PWM_10_CH22_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH23_PIN)
#define W_PWM10_PIN23_DECL { DT_ALIAS_PWM_10_CH23_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH24_PIN)
#define W_PWM10_PIN24_DECL { DT_ALIAS_PWM_10_CH24_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH25_PIN)
#define W_PWM10_PIN25_DECL { DT_ALIAS_PWM_10_CH25_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH26_PIN)
#define W_PWM10_PIN26_DECL { DT_ALIAS_PWM_10_CH26_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH27_PIN)
#define W_PWM10_PIN27_DECL { DT_ALIAS_PWM_10_CH27_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH28_PIN)
#define W_PWM10_PIN28_DECL { DT_ALIAS_PWM_10_CH28_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH29_PIN)
#define W_PWM10_PIN29_DECL { DT_ALIAS_PWM_10_CH29_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH30_PIN)
#define W_PWM10_PIN30_DECL { DT_ALIAS_PWM_10_CH30_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_10_CH31_PIN)
#define W_PWM10_PIN31_DECL { DT_ALIAS_PWM_10_CH31_PIN, DT_ALIAS_PWM_10_LABEL },
#else
#define W_PWM10_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH0_PIN)
#define W_PWM11_PIN0_DECL { DT_ALIAS_PWM_11_CH0_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH1_PIN)
#define W_PWM11_PIN1_DECL { DT_ALIAS_PWM_11_CH1_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH2_PIN)
#define W_PWM11_PIN2_DECL { DT_ALIAS_PWM_11_CH2_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH3_PIN)
#define W_PWM11_PIN3_DECL { DT_ALIAS_PWM_11_CH3_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH4_PIN)
#define W_PWM11_PIN4_DECL { DT_ALIAS_PWM_11_CH4_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH5_PIN)
#define W_PWM11_PIN5_DECL { DT_ALIAS_PWM_11_CH5_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH6_PIN)
#define W_PWM11_PIN6_DECL { DT_ALIAS_PWM_11_CH6_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH7_PIN)
#define W_PWM11_PIN7_DECL { DT_ALIAS_PWM_11_CH7_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH8_PIN)
#define W_PWM11_PIN8_DECL { DT_ALIAS_PWM_11_CH8_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH9_PIN)
#define W_PWM11_PIN9_DECL { DT_ALIAS_PWM_11_CH9_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH10_PIN)
#define W_PWM11_PIN10_DECL { DT_ALIAS_PWM_11_CH10_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH11_PIN)
#define W_PWM11_PIN11_DECL { DT_ALIAS_PWM_11_CH11_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH12_PIN)
#define W_PWM11_PIN12_DECL { DT_ALIAS_PWM_11_CH12_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH13_PIN)
#define W_PWM11_PIN13_DECL { DT_ALIAS_PWM_11_CH13_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH14_PIN)
#define W_PWM11_PIN14_DECL { DT_ALIAS_PWM_11_CH14_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH15_PIN)
#define W_PWM11_PIN15_DECL { DT_ALIAS_PWM_11_CH15_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH16_PIN)
#define W_PWM11_PIN16_DECL { DT_ALIAS_PWM_11_CH16_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH17_PIN)
#define W_PWM11_PIN17_DECL { DT_ALIAS_PWM_11_CH17_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH18_PIN)
#define W_PWM11_PIN18_DECL { DT_ALIAS_PWM_11_CH18_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH19_PIN)
#define W_PWM11_PIN19_DECL { DT_ALIAS_PWM_11_CH19_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH20_PIN)
#define W_PWM11_PIN20_DECL { DT_ALIAS_PWM_11_CH20_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH21_PIN)
#define W_PWM11_PIN21_DECL { DT_ALIAS_PWM_11_CH21_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH22_PIN)
#define W_PWM11_PIN22_DECL { DT_ALIAS_PWM_11_CH22_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH23_PIN)
#define W_PWM11_PIN23_DECL { DT_ALIAS_PWM_11_CH23_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH24_PIN)
#define W_PWM11_PIN24_DECL { DT_ALIAS_PWM_11_CH24_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH25_PIN)
#define W_PWM11_PIN25_DECL { DT_ALIAS_PWM_11_CH25_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH26_PIN)
#define W_PWM11_PIN26_DECL { DT_ALIAS_PWM_11_CH26_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH27_PIN)
#define W_PWM11_PIN27_DECL { DT_ALIAS_PWM_11_CH27_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH28_PIN)
#define W_PWM11_PIN28_DECL { DT_ALIAS_PWM_11_CH28_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH29_PIN)
#define W_PWM11_PIN29_DECL { DT_ALIAS_PWM_11_CH29_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH30_PIN)
#define W_PWM11_PIN30_DECL { DT_ALIAS_PWM_11_CH30_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_11_CH31_PIN)
#define W_PWM11_PIN31_DECL { DT_ALIAS_PWM_11_CH31_PIN, DT_ALIAS_PWM_11_LABEL },
#else
#define W_PWM11_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH0_PIN)
#define W_PWM12_PIN0_DECL { DT_ALIAS_PWM_12_CH0_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH1_PIN)
#define W_PWM12_PIN1_DECL { DT_ALIAS_PWM_12_CH1_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH2_PIN)
#define W_PWM12_PIN2_DECL { DT_ALIAS_PWM_12_CH2_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH3_PIN)
#define W_PWM12_PIN3_DECL { DT_ALIAS_PWM_12_CH3_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH4_PIN)
#define W_PWM12_PIN4_DECL { DT_ALIAS_PWM_12_CH4_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH5_PIN)
#define W_PWM12_PIN5_DECL { DT_ALIAS_PWM_12_CH5_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH6_PIN)
#define W_PWM12_PIN6_DECL { DT_ALIAS_PWM_12_CH6_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH7_PIN)
#define W_PWM12_PIN7_DECL { DT_ALIAS_PWM_12_CH7_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH8_PIN)
#define W_PWM12_PIN8_DECL { DT_ALIAS_PWM_12_CH8_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH9_PIN)
#define W_PWM12_PIN9_DECL { DT_ALIAS_PWM_12_CH9_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH10_PIN)
#define W_PWM12_PIN10_DECL { DT_ALIAS_PWM_12_CH10_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH11_PIN)
#define W_PWM12_PIN11_DECL { DT_ALIAS_PWM_12_CH11_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH12_PIN)
#define W_PWM12_PIN12_DECL { DT_ALIAS_PWM_12_CH12_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH13_PIN)
#define W_PWM12_PIN13_DECL { DT_ALIAS_PWM_12_CH13_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH14_PIN)
#define W_PWM12_PIN14_DECL { DT_ALIAS_PWM_12_CH14_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH15_PIN)
#define W_PWM12_PIN15_DECL { DT_ALIAS_PWM_12_CH15_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH16_PIN)
#define W_PWM12_PIN16_DECL { DT_ALIAS_PWM_12_CH16_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH17_PIN)
#define W_PWM12_PIN17_DECL { DT_ALIAS_PWM_12_CH17_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH18_PIN)
#define W_PWM12_PIN18_DECL { DT_ALIAS_PWM_12_CH18_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH19_PIN)
#define W_PWM12_PIN19_DECL { DT_ALIAS_PWM_12_CH19_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH20_PIN)
#define W_PWM12_PIN20_DECL { DT_ALIAS_PWM_12_CH20_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH21_PIN)
#define W_PWM12_PIN21_DECL { DT_ALIAS_PWM_12_CH21_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH22_PIN)
#define W_PWM12_PIN22_DECL { DT_ALIAS_PWM_12_CH22_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH23_PIN)
#define W_PWM12_PIN23_DECL { DT_ALIAS_PWM_12_CH23_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH24_PIN)
#define W_PWM12_PIN24_DECL { DT_ALIAS_PWM_12_CH24_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH25_PIN)
#define W_PWM12_PIN25_DECL { DT_ALIAS_PWM_12_CH25_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH26_PIN)
#define W_PWM12_PIN26_DECL { DT_ALIAS_PWM_12_CH26_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH27_PIN)
#define W_PWM12_PIN27_DECL { DT_ALIAS_PWM_12_CH27_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH28_PIN)
#define W_PWM12_PIN28_DECL { DT_ALIAS_PWM_12_CH28_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH29_PIN)
#define W_PWM12_PIN29_DECL { DT_ALIAS_PWM_12_CH29_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH30_PIN)
#define W_PWM12_PIN30_DECL { DT_ALIAS_PWM_12_CH30_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_12_CH31_PIN)
#define W_PWM12_PIN31_DECL { DT_ALIAS_PWM_12_CH31_PIN, DT_ALIAS_PWM_12_LABEL },
#else
#define W_PWM12_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH0_PIN)
#define W_PWM13_PIN0_DECL { DT_ALIAS_PWM_13_CH0_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH1_PIN)
#define W_PWM13_PIN1_DECL { DT_ALIAS_PWM_13_CH1_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH2_PIN)
#define W_PWM13_PIN2_DECL { DT_ALIAS_PWM_13_CH2_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH3_PIN)
#define W_PWM13_PIN3_DECL { DT_ALIAS_PWM_13_CH3_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH4_PIN)
#define W_PWM13_PIN4_DECL { DT_ALIAS_PWM_13_CH4_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH5_PIN)
#define W_PWM13_PIN5_DECL { DT_ALIAS_PWM_13_CH5_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH6_PIN)
#define W_PWM13_PIN6_DECL { DT_ALIAS_PWM_13_CH6_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH7_PIN)
#define W_PWM13_PIN7_DECL { DT_ALIAS_PWM_13_CH7_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH8_PIN)
#define W_PWM13_PIN8_DECL { DT_ALIAS_PWM_13_CH8_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH9_PIN)
#define W_PWM13_PIN9_DECL { DT_ALIAS_PWM_13_CH9_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH10_PIN)
#define W_PWM13_PIN10_DECL { DT_ALIAS_PWM_13_CH10_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH11_PIN)
#define W_PWM13_PIN11_DECL { DT_ALIAS_PWM_13_CH11_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH12_PIN)
#define W_PWM13_PIN12_DECL { DT_ALIAS_PWM_13_CH12_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH13_PIN)
#define W_PWM13_PIN13_DECL { DT_ALIAS_PWM_13_CH13_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH14_PIN)
#define W_PWM13_PIN14_DECL { DT_ALIAS_PWM_13_CH14_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH15_PIN)
#define W_PWM13_PIN15_DECL { DT_ALIAS_PWM_13_CH15_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH16_PIN)
#define W_PWM13_PIN16_DECL { DT_ALIAS_PWM_13_CH16_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH17_PIN)
#define W_PWM13_PIN17_DECL { DT_ALIAS_PWM_13_CH17_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH18_PIN)
#define W_PWM13_PIN18_DECL { DT_ALIAS_PWM_13_CH18_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH19_PIN)
#define W_PWM13_PIN19_DECL { DT_ALIAS_PWM_13_CH19_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH20_PIN)
#define W_PWM13_PIN20_DECL { DT_ALIAS_PWM_13_CH20_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH21_PIN)
#define W_PWM13_PIN21_DECL { DT_ALIAS_PWM_13_CH21_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH22_PIN)
#define W_PWM13_PIN22_DECL { DT_ALIAS_PWM_13_CH22_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH23_PIN)
#define W_PWM13_PIN23_DECL { DT_ALIAS_PWM_13_CH23_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH24_PIN)
#define W_PWM13_PIN24_DECL { DT_ALIAS_PWM_13_CH24_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH25_PIN)
#define W_PWM13_PIN25_DECL { DT_ALIAS_PWM_13_CH25_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH26_PIN)
#define W_PWM13_PIN26_DECL { DT_ALIAS_PWM_13_CH26_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH27_PIN)
#define W_PWM13_PIN27_DECL { DT_ALIAS_PWM_13_CH27_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH28_PIN)
#define W_PWM13_PIN28_DECL { DT_ALIAS_PWM_13_CH28_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH29_PIN)
#define W_PWM13_PIN29_DECL { DT_ALIAS_PWM_13_CH29_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH30_PIN)
#define W_PWM13_PIN30_DECL { DT_ALIAS_PWM_13_CH30_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_13_CH31_PIN)
#define W_PWM13_PIN31_DECL { DT_ALIAS_PWM_13_CH31_PIN, DT_ALIAS_PWM_13_LABEL },
#else
#define W_PWM13_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH0_PIN)
#define W_PWM14_PIN0_DECL { DT_ALIAS_PWM_14_CH0_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH1_PIN)
#define W_PWM14_PIN1_DECL { DT_ALIAS_PWM_14_CH1_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH2_PIN)
#define W_PWM14_PIN2_DECL { DT_ALIAS_PWM_14_CH2_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH3_PIN)
#define W_PWM14_PIN3_DECL { DT_ALIAS_PWM_14_CH3_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH4_PIN)
#define W_PWM14_PIN4_DECL { DT_ALIAS_PWM_14_CH4_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH5_PIN)
#define W_PWM14_PIN5_DECL { DT_ALIAS_PWM_14_CH5_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH6_PIN)
#define W_PWM14_PIN6_DECL { DT_ALIAS_PWM_14_CH6_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH7_PIN)
#define W_PWM14_PIN7_DECL { DT_ALIAS_PWM_14_CH7_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH8_PIN)
#define W_PWM14_PIN8_DECL { DT_ALIAS_PWM_14_CH8_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH9_PIN)
#define W_PWM14_PIN9_DECL { DT_ALIAS_PWM_14_CH9_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH10_PIN)
#define W_PWM14_PIN10_DECL { DT_ALIAS_PWM_14_CH10_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH11_PIN)
#define W_PWM14_PIN11_DECL { DT_ALIAS_PWM_14_CH11_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH12_PIN)
#define W_PWM14_PIN12_DECL { DT_ALIAS_PWM_14_CH12_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH13_PIN)
#define W_PWM14_PIN13_DECL { DT_ALIAS_PWM_14_CH13_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH14_PIN)
#define W_PWM14_PIN14_DECL { DT_ALIAS_PWM_14_CH14_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH15_PIN)
#define W_PWM14_PIN15_DECL { DT_ALIAS_PWM_14_CH15_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH16_PIN)
#define W_PWM14_PIN16_DECL { DT_ALIAS_PWM_14_CH16_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH17_PIN)
#define W_PWM14_PIN17_DECL { DT_ALIAS_PWM_14_CH17_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH18_PIN)
#define W_PWM14_PIN18_DECL { DT_ALIAS_PWM_14_CH18_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH19_PIN)
#define W_PWM14_PIN19_DECL { DT_ALIAS_PWM_14_CH19_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH20_PIN)
#define W_PWM14_PIN20_DECL { DT_ALIAS_PWM_14_CH20_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH21_PIN)
#define W_PWM14_PIN21_DECL { DT_ALIAS_PWM_14_CH21_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH22_PIN)
#define W_PWM14_PIN22_DECL { DT_ALIAS_PWM_14_CH22_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH23_PIN)
#define W_PWM14_PIN23_DECL { DT_ALIAS_PWM_14_CH23_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH24_PIN)
#define W_PWM14_PIN24_DECL { DT_ALIAS_PWM_14_CH24_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH25_PIN)
#define W_PWM14_PIN25_DECL { DT_ALIAS_PWM_14_CH25_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH26_PIN)
#define W_PWM14_PIN26_DECL { DT_ALIAS_PWM_14_CH26_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH27_PIN)
#define W_PWM14_PIN27_DECL { DT_ALIAS_PWM_14_CH27_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH28_PIN)
#define W_PWM14_PIN28_DECL { DT_ALIAS_PWM_14_CH28_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH29_PIN)
#define W_PWM14_PIN29_DECL { DT_ALIAS_PWM_14_CH29_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH30_PIN)
#define W_PWM14_PIN30_DECL { DT_ALIAS_PWM_14_CH30_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_14_CH31_PIN)
#define W_PWM14_PIN31_DECL { DT_ALIAS_PWM_14_CH31_PIN, DT_ALIAS_PWM_14_LABEL },
#else
#define W_PWM14_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH0_PIN)
#define W_PWM15_PIN0_DECL { DT_ALIAS_PWM_15_CH0_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH1_PIN)
#define W_PWM15_PIN1_DECL { DT_ALIAS_PWM_15_CH1_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH2_PIN)
#define W_PWM15_PIN2_DECL { DT_ALIAS_PWM_15_CH2_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH3_PIN)
#define W_PWM15_PIN3_DECL { DT_ALIAS_PWM_15_CH3_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH4_PIN)
#define W_PWM15_PIN4_DECL { DT_ALIAS_PWM_15_CH4_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH5_PIN)
#define W_PWM15_PIN5_DECL { DT_ALIAS_PWM_15_CH5_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH6_PIN)
#define W_PWM15_PIN6_DECL { DT_ALIAS_PWM_15_CH6_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH7_PIN)
#define W_PWM15_PIN7_DECL { DT_ALIAS_PWM_15_CH7_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH8_PIN)
#define W_PWM15_PIN8_DECL { DT_ALIAS_PWM_15_CH8_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH9_PIN)
#define W_PWM15_PIN9_DECL { DT_ALIAS_PWM_15_CH9_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH10_PIN)
#define W_PWM15_PIN10_DECL { DT_ALIAS_PWM_15_CH10_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH11_PIN)
#define W_PWM15_PIN11_DECL { DT_ALIAS_PWM_15_CH11_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH12_PIN)
#define W_PWM15_PIN12_DECL { DT_ALIAS_PWM_15_CH12_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH13_PIN)
#define W_PWM15_PIN13_DECL { DT_ALIAS_PWM_15_CH13_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH14_PIN)
#define W_PWM15_PIN14_DECL { DT_ALIAS_PWM_15_CH14_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH15_PIN)
#define W_PWM15_PIN15_DECL { DT_ALIAS_PWM_15_CH15_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH16_PIN)
#define W_PWM15_PIN16_DECL { DT_ALIAS_PWM_15_CH16_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH17_PIN)
#define W_PWM15_PIN17_DECL { DT_ALIAS_PWM_15_CH17_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH18_PIN)
#define W_PWM15_PIN18_DECL { DT_ALIAS_PWM_15_CH18_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH19_PIN)
#define W_PWM15_PIN19_DECL { DT_ALIAS_PWM_15_CH19_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH20_PIN)
#define W_PWM15_PIN20_DECL { DT_ALIAS_PWM_15_CH20_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH21_PIN)
#define W_PWM15_PIN21_DECL { DT_ALIAS_PWM_15_CH21_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH22_PIN)
#define W_PWM15_PIN22_DECL { DT_ALIAS_PWM_15_CH22_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH23_PIN)
#define W_PWM15_PIN23_DECL { DT_ALIAS_PWM_15_CH23_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH24_PIN)
#define W_PWM15_PIN24_DECL { DT_ALIAS_PWM_15_CH24_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH25_PIN)
#define W_PWM15_PIN25_DECL { DT_ALIAS_PWM_15_CH25_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH26_PIN)
#define W_PWM15_PIN26_DECL { DT_ALIAS_PWM_15_CH26_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH27_PIN)
#define W_PWM15_PIN27_DECL { DT_ALIAS_PWM_15_CH27_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH28_PIN)
#define W_PWM15_PIN28_DECL { DT_ALIAS_PWM_15_CH28_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH29_PIN)
#define W_PWM15_PIN29_DECL { DT_ALIAS_PWM_15_CH29_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH30_PIN)
#define W_PWM15_PIN30_DECL { DT_ALIAS_PWM_15_CH30_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_15_CH31_PIN)
#define W_PWM15_PIN31_DECL { DT_ALIAS_PWM_15_CH31_PIN, DT_ALIAS_PWM_15_LABEL },
#else
#define W_PWM15_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH0_PIN)
#define W_PWM16_PIN0_DECL { DT_ALIAS_PWM_16_CH0_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH1_PIN)
#define W_PWM16_PIN1_DECL { DT_ALIAS_PWM_16_CH1_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH2_PIN)
#define W_PWM16_PIN2_DECL { DT_ALIAS_PWM_16_CH2_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH3_PIN)
#define W_PWM16_PIN3_DECL { DT_ALIAS_PWM_16_CH3_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH4_PIN)
#define W_PWM16_PIN4_DECL { DT_ALIAS_PWM_16_CH4_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH5_PIN)
#define W_PWM16_PIN5_DECL { DT_ALIAS_PWM_16_CH5_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH6_PIN)
#define W_PWM16_PIN6_DECL { DT_ALIAS_PWM_16_CH6_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH7_PIN)
#define W_PWM16_PIN7_DECL { DT_ALIAS_PWM_16_CH7_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH8_PIN)
#define W_PWM16_PIN8_DECL { DT_ALIAS_PWM_16_CH8_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH9_PIN)
#define W_PWM16_PIN9_DECL { DT_ALIAS_PWM_16_CH9_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH10_PIN)
#define W_PWM16_PIN10_DECL { DT_ALIAS_PWM_16_CH10_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH11_PIN)
#define W_PWM16_PIN11_DECL { DT_ALIAS_PWM_16_CH11_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH12_PIN)
#define W_PWM16_PIN12_DECL { DT_ALIAS_PWM_16_CH12_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH13_PIN)
#define W_PWM16_PIN13_DECL { DT_ALIAS_PWM_16_CH13_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH14_PIN)
#define W_PWM16_PIN14_DECL { DT_ALIAS_PWM_16_CH14_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH15_PIN)
#define W_PWM16_PIN15_DECL { DT_ALIAS_PWM_16_CH15_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH16_PIN)
#define W_PWM16_PIN16_DECL { DT_ALIAS_PWM_16_CH16_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH17_PIN)
#define W_PWM16_PIN17_DECL { DT_ALIAS_PWM_16_CH17_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH18_PIN)
#define W_PWM16_PIN18_DECL { DT_ALIAS_PWM_16_CH18_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH19_PIN)
#define W_PWM16_PIN19_DECL { DT_ALIAS_PWM_16_CH19_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH20_PIN)
#define W_PWM16_PIN20_DECL { DT_ALIAS_PWM_16_CH20_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH21_PIN)
#define W_PWM16_PIN21_DECL { DT_ALIAS_PWM_16_CH21_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH22_PIN)
#define W_PWM16_PIN22_DECL { DT_ALIAS_PWM_16_CH22_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH23_PIN)
#define W_PWM16_PIN23_DECL { DT_ALIAS_PWM_16_CH23_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH24_PIN)
#define W_PWM16_PIN24_DECL { DT_ALIAS_PWM_16_CH24_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH25_PIN)
#define W_PWM16_PIN25_DECL { DT_ALIAS_PWM_16_CH25_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH26_PIN)
#define W_PWM16_PIN26_DECL { DT_ALIAS_PWM_16_CH26_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH27_PIN)
#define W_PWM16_PIN27_DECL { DT_ALIAS_PWM_16_CH27_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH28_PIN)
#define W_PWM16_PIN28_DECL { DT_ALIAS_PWM_16_CH28_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH29_PIN)
#define W_PWM16_PIN29_DECL { DT_ALIAS_PWM_16_CH29_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH30_PIN)
#define W_PWM16_PIN30_DECL { DT_ALIAS_PWM_16_CH30_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_16_CH31_PIN)
#define W_PWM16_PIN31_DECL { DT_ALIAS_PWM_16_CH31_PIN, DT_ALIAS_PWM_16_LABEL },
#else
#define W_PWM16_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH0_PIN)
#define W_PWM17_PIN0_DECL { DT_ALIAS_PWM_17_CH0_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH1_PIN)
#define W_PWM17_PIN1_DECL { DT_ALIAS_PWM_17_CH1_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH2_PIN)
#define W_PWM17_PIN2_DECL { DT_ALIAS_PWM_17_CH2_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH3_PIN)
#define W_PWM17_PIN3_DECL { DT_ALIAS_PWM_17_CH3_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH4_PIN)
#define W_PWM17_PIN4_DECL { DT_ALIAS_PWM_17_CH4_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH5_PIN)
#define W_PWM17_PIN5_DECL { DT_ALIAS_PWM_17_CH5_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH6_PIN)
#define W_PWM17_PIN6_DECL { DT_ALIAS_PWM_17_CH6_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH7_PIN)
#define W_PWM17_PIN7_DECL { DT_ALIAS_PWM_17_CH7_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH8_PIN)
#define W_PWM17_PIN8_DECL { DT_ALIAS_PWM_17_CH8_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH9_PIN)
#define W_PWM17_PIN9_DECL { DT_ALIAS_PWM_17_CH9_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH10_PIN)
#define W_PWM17_PIN10_DECL { DT_ALIAS_PWM_17_CH10_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH11_PIN)
#define W_PWM17_PIN11_DECL { DT_ALIAS_PWM_17_CH11_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH12_PIN)
#define W_PWM17_PIN12_DECL { DT_ALIAS_PWM_17_CH12_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH13_PIN)
#define W_PWM17_PIN13_DECL { DT_ALIAS_PWM_17_CH13_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH14_PIN)
#define W_PWM17_PIN14_DECL { DT_ALIAS_PWM_17_CH14_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH15_PIN)
#define W_PWM17_PIN15_DECL { DT_ALIAS_PWM_17_CH15_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH16_PIN)
#define W_PWM17_PIN16_DECL { DT_ALIAS_PWM_17_CH16_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH17_PIN)
#define W_PWM17_PIN17_DECL { DT_ALIAS_PWM_17_CH17_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH18_PIN)
#define W_PWM17_PIN18_DECL { DT_ALIAS_PWM_17_CH18_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH19_PIN)
#define W_PWM17_PIN19_DECL { DT_ALIAS_PWM_17_CH19_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH20_PIN)
#define W_PWM17_PIN20_DECL { DT_ALIAS_PWM_17_CH20_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH21_PIN)
#define W_PWM17_PIN21_DECL { DT_ALIAS_PWM_17_CH21_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH22_PIN)
#define W_PWM17_PIN22_DECL { DT_ALIAS_PWM_17_CH22_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH23_PIN)
#define W_PWM17_PIN23_DECL { DT_ALIAS_PWM_17_CH23_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH24_PIN)
#define W_PWM17_PIN24_DECL { DT_ALIAS_PWM_17_CH24_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH25_PIN)
#define W_PWM17_PIN25_DECL { DT_ALIAS_PWM_17_CH25_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH26_PIN)
#define W_PWM17_PIN26_DECL { DT_ALIAS_PWM_17_CH26_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH27_PIN)
#define W_PWM17_PIN27_DECL { DT_ALIAS_PWM_17_CH27_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH28_PIN)
#define W_PWM17_PIN28_DECL { DT_ALIAS_PWM_17_CH28_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH29_PIN)
#define W_PWM17_PIN29_DECL { DT_ALIAS_PWM_17_CH29_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH30_PIN)
#define W_PWM17_PIN30_DECL { DT_ALIAS_PWM_17_CH30_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_17_CH31_PIN)
#define W_PWM17_PIN31_DECL { DT_ALIAS_PWM_17_CH31_PIN, DT_ALIAS_PWM_17_LABEL },
#else
#define W_PWM17_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH0_PIN)
#define W_PWM18_PIN0_DECL { DT_ALIAS_PWM_18_CH0_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH1_PIN)
#define W_PWM18_PIN1_DECL { DT_ALIAS_PWM_18_CH1_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH2_PIN)
#define W_PWM18_PIN2_DECL { DT_ALIAS_PWM_18_CH2_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH3_PIN)
#define W_PWM18_PIN3_DECL { DT_ALIAS_PWM_18_CH3_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH4_PIN)
#define W_PWM18_PIN4_DECL { DT_ALIAS_PWM_18_CH4_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH5_PIN)
#define W_PWM18_PIN5_DECL { DT_ALIAS_PWM_18_CH5_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH6_PIN)
#define W_PWM18_PIN6_DECL { DT_ALIAS_PWM_18_CH6_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH7_PIN)
#define W_PWM18_PIN7_DECL { DT_ALIAS_PWM_18_CH7_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH8_PIN)
#define W_PWM18_PIN8_DECL { DT_ALIAS_PWM_18_CH8_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH9_PIN)
#define W_PWM18_PIN9_DECL { DT_ALIAS_PWM_18_CH9_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH10_PIN)
#define W_PWM18_PIN10_DECL { DT_ALIAS_PWM_18_CH10_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH11_PIN)
#define W_PWM18_PIN11_DECL { DT_ALIAS_PWM_18_CH11_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH12_PIN)
#define W_PWM18_PIN12_DECL { DT_ALIAS_PWM_18_CH12_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH13_PIN)
#define W_PWM18_PIN13_DECL { DT_ALIAS_PWM_18_CH13_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH14_PIN)
#define W_PWM18_PIN14_DECL { DT_ALIAS_PWM_18_CH14_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH15_PIN)
#define W_PWM18_PIN15_DECL { DT_ALIAS_PWM_18_CH15_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH16_PIN)
#define W_PWM18_PIN16_DECL { DT_ALIAS_PWM_18_CH16_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH17_PIN)
#define W_PWM18_PIN17_DECL { DT_ALIAS_PWM_18_CH17_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH18_PIN)
#define W_PWM18_PIN18_DECL { DT_ALIAS_PWM_18_CH18_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH19_PIN)
#define W_PWM18_PIN19_DECL { DT_ALIAS_PWM_18_CH19_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH20_PIN)
#define W_PWM18_PIN20_DECL { DT_ALIAS_PWM_18_CH20_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH21_PIN)
#define W_PWM18_PIN21_DECL { DT_ALIAS_PWM_18_CH21_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH22_PIN)
#define W_PWM18_PIN22_DECL { DT_ALIAS_PWM_18_CH22_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH23_PIN)
#define W_PWM18_PIN23_DECL { DT_ALIAS_PWM_18_CH23_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH24_PIN)
#define W_PWM18_PIN24_DECL { DT_ALIAS_PWM_18_CH24_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH25_PIN)
#define W_PWM18_PIN25_DECL { DT_ALIAS_PWM_18_CH25_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH26_PIN)
#define W_PWM18_PIN26_DECL { DT_ALIAS_PWM_18_CH26_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH27_PIN)
#define W_PWM18_PIN27_DECL { DT_ALIAS_PWM_18_CH27_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH28_PIN)
#define W_PWM18_PIN28_DECL { DT_ALIAS_PWM_18_CH28_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH29_PIN)
#define W_PWM18_PIN29_DECL { DT_ALIAS_PWM_18_CH29_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH30_PIN)
#define W_PWM18_PIN30_DECL { DT_ALIAS_PWM_18_CH30_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_18_CH31_PIN)
#define W_PWM18_PIN31_DECL { DT_ALIAS_PWM_18_CH31_PIN, DT_ALIAS_PWM_18_LABEL },
#else
#define W_PWM18_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH0_PIN)
#define W_PWM19_PIN0_DECL { DT_ALIAS_PWM_19_CH0_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH1_PIN)
#define W_PWM19_PIN1_DECL { DT_ALIAS_PWM_19_CH1_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH2_PIN)
#define W_PWM19_PIN2_DECL { DT_ALIAS_PWM_19_CH2_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH3_PIN)
#define W_PWM19_PIN3_DECL { DT_ALIAS_PWM_19_CH3_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH4_PIN)
#define W_PWM19_PIN4_DECL { DT_ALIAS_PWM_19_CH4_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH5_PIN)
#define W_PWM19_PIN5_DECL { DT_ALIAS_PWM_19_CH5_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH6_PIN)
#define W_PWM19_PIN6_DECL { DT_ALIAS_PWM_19_CH6_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH7_PIN)
#define W_PWM19_PIN7_DECL { DT_ALIAS_PWM_19_CH7_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH8_PIN)
#define W_PWM19_PIN8_DECL { DT_ALIAS_PWM_19_CH8_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH9_PIN)
#define W_PWM19_PIN9_DECL { DT_ALIAS_PWM_19_CH9_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH10_PIN)
#define W_PWM19_PIN10_DECL { DT_ALIAS_PWM_19_CH10_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH11_PIN)
#define W_PWM19_PIN11_DECL { DT_ALIAS_PWM_19_CH11_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH12_PIN)
#define W_PWM19_PIN12_DECL { DT_ALIAS_PWM_19_CH12_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH13_PIN)
#define W_PWM19_PIN13_DECL { DT_ALIAS_PWM_19_CH13_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH14_PIN)
#define W_PWM19_PIN14_DECL { DT_ALIAS_PWM_19_CH14_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH15_PIN)
#define W_PWM19_PIN15_DECL { DT_ALIAS_PWM_19_CH15_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH16_PIN)
#define W_PWM19_PIN16_DECL { DT_ALIAS_PWM_19_CH16_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH17_PIN)
#define W_PWM19_PIN17_DECL { DT_ALIAS_PWM_19_CH17_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH18_PIN)
#define W_PWM19_PIN18_DECL { DT_ALIAS_PWM_19_CH18_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH19_PIN)
#define W_PWM19_PIN19_DECL { DT_ALIAS_PWM_19_CH19_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH20_PIN)
#define W_PWM19_PIN20_DECL { DT_ALIAS_PWM_19_CH20_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH21_PIN)
#define W_PWM19_PIN21_DECL { DT_ALIAS_PWM_19_CH21_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH22_PIN)
#define W_PWM19_PIN22_DECL { DT_ALIAS_PWM_19_CH22_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH23_PIN)
#define W_PWM19_PIN23_DECL { DT_ALIAS_PWM_19_CH23_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH24_PIN)
#define W_PWM19_PIN24_DECL { DT_ALIAS_PWM_19_CH24_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH25_PIN)
#define W_PWM19_PIN25_DECL { DT_ALIAS_PWM_19_CH25_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH26_PIN)
#define W_PWM19_PIN26_DECL { DT_ALIAS_PWM_19_CH26_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH27_PIN)
#define W_PWM19_PIN27_DECL { DT_ALIAS_PWM_19_CH27_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH28_PIN)
#define W_PWM19_PIN28_DECL { DT_ALIAS_PWM_19_CH28_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH29_PIN)
#define W_PWM19_PIN29_DECL { DT_ALIAS_PWM_19_CH29_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH30_PIN)
#define W_PWM19_PIN30_DECL { DT_ALIAS_PWM_19_CH30_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_19_CH31_PIN)
#define W_PWM19_PIN31_DECL { DT_ALIAS_PWM_19_CH31_PIN, DT_ALIAS_PWM_19_LABEL },
#else
#define W_PWM19_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH0_PIN)
#define W_PWM20_PIN0_DECL { DT_ALIAS_PWM_20_CH0_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH1_PIN)
#define W_PWM20_PIN1_DECL { DT_ALIAS_PWM_20_CH1_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH2_PIN)
#define W_PWM20_PIN2_DECL { DT_ALIAS_PWM_20_CH2_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH3_PIN)
#define W_PWM20_PIN3_DECL { DT_ALIAS_PWM_20_CH3_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH4_PIN)
#define W_PWM20_PIN4_DECL { DT_ALIAS_PWM_20_CH4_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH5_PIN)
#define W_PWM20_PIN5_DECL { DT_ALIAS_PWM_20_CH5_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH6_PIN)
#define W_PWM20_PIN6_DECL { DT_ALIAS_PWM_20_CH6_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH7_PIN)
#define W_PWM20_PIN7_DECL { DT_ALIAS_PWM_20_CH7_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH8_PIN)
#define W_PWM20_PIN8_DECL { DT_ALIAS_PWM_20_CH8_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH9_PIN)
#define W_PWM20_PIN9_DECL { DT_ALIAS_PWM_20_CH9_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH10_PIN)
#define W_PWM20_PIN10_DECL { DT_ALIAS_PWM_20_CH10_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH11_PIN)
#define W_PWM20_PIN11_DECL { DT_ALIAS_PWM_20_CH11_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH12_PIN)
#define W_PWM20_PIN12_DECL { DT_ALIAS_PWM_20_CH12_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH13_PIN)
#define W_PWM20_PIN13_DECL { DT_ALIAS_PWM_20_CH13_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH14_PIN)
#define W_PWM20_PIN14_DECL { DT_ALIAS_PWM_20_CH14_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH15_PIN)
#define W_PWM20_PIN15_DECL { DT_ALIAS_PWM_20_CH15_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH16_PIN)
#define W_PWM20_PIN16_DECL { DT_ALIAS_PWM_20_CH16_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH17_PIN)
#define W_PWM20_PIN17_DECL { DT_ALIAS_PWM_20_CH17_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH18_PIN)
#define W_PWM20_PIN18_DECL { DT_ALIAS_PWM_20_CH18_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH19_PIN)
#define W_PWM20_PIN19_DECL { DT_ALIAS_PWM_20_CH19_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH20_PIN)
#define W_PWM20_PIN20_DECL { DT_ALIAS_PWM_20_CH20_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH21_PIN)
#define W_PWM20_PIN21_DECL { DT_ALIAS_PWM_20_CH21_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH22_PIN)
#define W_PWM20_PIN22_DECL { DT_ALIAS_PWM_20_CH22_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH23_PIN)
#define W_PWM20_PIN23_DECL { DT_ALIAS_PWM_20_CH23_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH24_PIN)
#define W_PWM20_PIN24_DECL { DT_ALIAS_PWM_20_CH24_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH25_PIN)
#define W_PWM20_PIN25_DECL { DT_ALIAS_PWM_20_CH25_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH26_PIN)
#define W_PWM20_PIN26_DECL { DT_ALIAS_PWM_20_CH26_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH27_PIN)
#define W_PWM20_PIN27_DECL { DT_ALIAS_PWM_20_CH27_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH28_PIN)
#define W_PWM20_PIN28_DECL { DT_ALIAS_PWM_20_CH28_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH29_PIN)
#define W_PWM20_PIN29_DECL { DT_ALIAS_PWM_20_CH29_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH30_PIN)
#define W_PWM20_PIN30_DECL { DT_ALIAS_PWM_20_CH30_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_20_CH31_PIN)
#define W_PWM20_PIN31_DECL { DT_ALIAS_PWM_20_CH31_PIN, DT_ALIAS_PWM_20_LABEL },
#else
#define W_PWM20_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH0_PIN)
#define W_PWM21_PIN0_DECL { DT_ALIAS_PWM_21_CH0_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH1_PIN)
#define W_PWM21_PIN1_DECL { DT_ALIAS_PWM_21_CH1_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH2_PIN)
#define W_PWM21_PIN2_DECL { DT_ALIAS_PWM_21_CH2_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH3_PIN)
#define W_PWM21_PIN3_DECL { DT_ALIAS_PWM_21_CH3_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH4_PIN)
#define W_PWM21_PIN4_DECL { DT_ALIAS_PWM_21_CH4_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH5_PIN)
#define W_PWM21_PIN5_DECL { DT_ALIAS_PWM_21_CH5_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH6_PIN)
#define W_PWM21_PIN6_DECL { DT_ALIAS_PWM_21_CH6_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH7_PIN)
#define W_PWM21_PIN7_DECL { DT_ALIAS_PWM_21_CH7_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH8_PIN)
#define W_PWM21_PIN8_DECL { DT_ALIAS_PWM_21_CH8_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH9_PIN)
#define W_PWM21_PIN9_DECL { DT_ALIAS_PWM_21_CH9_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH10_PIN)
#define W_PWM21_PIN10_DECL { DT_ALIAS_PWM_21_CH10_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH11_PIN)
#define W_PWM21_PIN11_DECL { DT_ALIAS_PWM_21_CH11_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH12_PIN)
#define W_PWM21_PIN12_DECL { DT_ALIAS_PWM_21_CH12_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH13_PIN)
#define W_PWM21_PIN13_DECL { DT_ALIAS_PWM_21_CH13_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH14_PIN)
#define W_PWM21_PIN14_DECL { DT_ALIAS_PWM_21_CH14_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH15_PIN)
#define W_PWM21_PIN15_DECL { DT_ALIAS_PWM_21_CH15_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH16_PIN)
#define W_PWM21_PIN16_DECL { DT_ALIAS_PWM_21_CH16_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH17_PIN)
#define W_PWM21_PIN17_DECL { DT_ALIAS_PWM_21_CH17_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH18_PIN)
#define W_PWM21_PIN18_DECL { DT_ALIAS_PWM_21_CH18_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH19_PIN)
#define W_PWM21_PIN19_DECL { DT_ALIAS_PWM_21_CH19_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH20_PIN)
#define W_PWM21_PIN20_DECL { DT_ALIAS_PWM_21_CH20_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH21_PIN)
#define W_PWM21_PIN21_DECL { DT_ALIAS_PWM_21_CH21_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH22_PIN)
#define W_PWM21_PIN22_DECL { DT_ALIAS_PWM_21_CH22_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH23_PIN)
#define W_PWM21_PIN23_DECL { DT_ALIAS_PWM_21_CH23_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH24_PIN)
#define W_PWM21_PIN24_DECL { DT_ALIAS_PWM_21_CH24_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH25_PIN)
#define W_PWM21_PIN25_DECL { DT_ALIAS_PWM_21_CH25_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH26_PIN)
#define W_PWM21_PIN26_DECL { DT_ALIAS_PWM_21_CH26_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH27_PIN)
#define W_PWM21_PIN27_DECL { DT_ALIAS_PWM_21_CH27_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH28_PIN)
#define W_PWM21_PIN28_DECL { DT_ALIAS_PWM_21_CH28_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH29_PIN)
#define W_PWM21_PIN29_DECL { DT_ALIAS_PWM_21_CH29_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH30_PIN)
#define W_PWM21_PIN30_DECL { DT_ALIAS_PWM_21_CH30_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_21_CH31_PIN)
#define W_PWM21_PIN31_DECL { DT_ALIAS_PWM_21_CH31_PIN, DT_ALIAS_PWM_21_LABEL },
#else
#define W_PWM21_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH0_PIN)
#define W_PWM22_PIN0_DECL { DT_ALIAS_PWM_22_CH0_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH1_PIN)
#define W_PWM22_PIN1_DECL { DT_ALIAS_PWM_22_CH1_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH2_PIN)
#define W_PWM22_PIN2_DECL { DT_ALIAS_PWM_22_CH2_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH3_PIN)
#define W_PWM22_PIN3_DECL { DT_ALIAS_PWM_22_CH3_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH4_PIN)
#define W_PWM22_PIN4_DECL { DT_ALIAS_PWM_22_CH4_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH5_PIN)
#define W_PWM22_PIN5_DECL { DT_ALIAS_PWM_22_CH5_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH6_PIN)
#define W_PWM22_PIN6_DECL { DT_ALIAS_PWM_22_CH6_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH7_PIN)
#define W_PWM22_PIN7_DECL { DT_ALIAS_PWM_22_CH7_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH8_PIN)
#define W_PWM22_PIN8_DECL { DT_ALIAS_PWM_22_CH8_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH9_PIN)
#define W_PWM22_PIN9_DECL { DT_ALIAS_PWM_22_CH9_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH10_PIN)
#define W_PWM22_PIN10_DECL { DT_ALIAS_PWM_22_CH10_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH11_PIN)
#define W_PWM22_PIN11_DECL { DT_ALIAS_PWM_22_CH11_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH12_PIN)
#define W_PWM22_PIN12_DECL { DT_ALIAS_PWM_22_CH12_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH13_PIN)
#define W_PWM22_PIN13_DECL { DT_ALIAS_PWM_22_CH13_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH14_PIN)
#define W_PWM22_PIN14_DECL { DT_ALIAS_PWM_22_CH14_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH15_PIN)
#define W_PWM22_PIN15_DECL { DT_ALIAS_PWM_22_CH15_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH16_PIN)
#define W_PWM22_PIN16_DECL { DT_ALIAS_PWM_22_CH16_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH17_PIN)
#define W_PWM22_PIN17_DECL { DT_ALIAS_PWM_22_CH17_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH18_PIN)
#define W_PWM22_PIN18_DECL { DT_ALIAS_PWM_22_CH18_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH19_PIN)
#define W_PWM22_PIN19_DECL { DT_ALIAS_PWM_22_CH19_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH20_PIN)
#define W_PWM22_PIN20_DECL { DT_ALIAS_PWM_22_CH20_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH21_PIN)
#define W_PWM22_PIN21_DECL { DT_ALIAS_PWM_22_CH21_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH22_PIN)
#define W_PWM22_PIN22_DECL { DT_ALIAS_PWM_22_CH22_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH23_PIN)
#define W_PWM22_PIN23_DECL { DT_ALIAS_PWM_22_CH23_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH24_PIN)
#define W_PWM22_PIN24_DECL { DT_ALIAS_PWM_22_CH24_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH25_PIN)
#define W_PWM22_PIN25_DECL { DT_ALIAS_PWM_22_CH25_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH26_PIN)
#define W_PWM22_PIN26_DECL { DT_ALIAS_PWM_22_CH26_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH27_PIN)
#define W_PWM22_PIN27_DECL { DT_ALIAS_PWM_22_CH27_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH28_PIN)
#define W_PWM22_PIN28_DECL { DT_ALIAS_PWM_22_CH28_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH29_PIN)
#define W_PWM22_PIN29_DECL { DT_ALIAS_PWM_22_CH29_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH30_PIN)
#define W_PWM22_PIN30_DECL { DT_ALIAS_PWM_22_CH30_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_22_CH31_PIN)
#define W_PWM22_PIN31_DECL { DT_ALIAS_PWM_22_CH31_PIN, DT_ALIAS_PWM_22_LABEL },
#else
#define W_PWM22_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH0_PIN)
#define W_PWM23_PIN0_DECL { DT_ALIAS_PWM_23_CH0_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH1_PIN)
#define W_PWM23_PIN1_DECL { DT_ALIAS_PWM_23_CH1_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH2_PIN)
#define W_PWM23_PIN2_DECL { DT_ALIAS_PWM_23_CH2_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH3_PIN)
#define W_PWM23_PIN3_DECL { DT_ALIAS_PWM_23_CH3_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH4_PIN)
#define W_PWM23_PIN4_DECL { DT_ALIAS_PWM_23_CH4_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH5_PIN)
#define W_PWM23_PIN5_DECL { DT_ALIAS_PWM_23_CH5_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH6_PIN)
#define W_PWM23_PIN6_DECL { DT_ALIAS_PWM_23_CH6_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH7_PIN)
#define W_PWM23_PIN7_DECL { DT_ALIAS_PWM_23_CH7_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH8_PIN)
#define W_PWM23_PIN8_DECL { DT_ALIAS_PWM_23_CH8_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH9_PIN)
#define W_PWM23_PIN9_DECL { DT_ALIAS_PWM_23_CH9_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH10_PIN)
#define W_PWM23_PIN10_DECL { DT_ALIAS_PWM_23_CH10_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH11_PIN)
#define W_PWM23_PIN11_DECL { DT_ALIAS_PWM_23_CH11_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH12_PIN)
#define W_PWM23_PIN12_DECL { DT_ALIAS_PWM_23_CH12_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH13_PIN)
#define W_PWM23_PIN13_DECL { DT_ALIAS_PWM_23_CH13_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH14_PIN)
#define W_PWM23_PIN14_DECL { DT_ALIAS_PWM_23_CH14_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH15_PIN)
#define W_PWM23_PIN15_DECL { DT_ALIAS_PWM_23_CH15_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH16_PIN)
#define W_PWM23_PIN16_DECL { DT_ALIAS_PWM_23_CH16_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH17_PIN)
#define W_PWM23_PIN17_DECL { DT_ALIAS_PWM_23_CH17_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH18_PIN)
#define W_PWM23_PIN18_DECL { DT_ALIAS_PWM_23_CH18_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH19_PIN)
#define W_PWM23_PIN19_DECL { DT_ALIAS_PWM_23_CH19_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH20_PIN)
#define W_PWM23_PIN20_DECL { DT_ALIAS_PWM_23_CH20_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH21_PIN)
#define W_PWM23_PIN21_DECL { DT_ALIAS_PWM_23_CH21_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH22_PIN)
#define W_PWM23_PIN22_DECL { DT_ALIAS_PWM_23_CH22_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH23_PIN)
#define W_PWM23_PIN23_DECL { DT_ALIAS_PWM_23_CH23_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH24_PIN)
#define W_PWM23_PIN24_DECL { DT_ALIAS_PWM_23_CH24_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH25_PIN)
#define W_PWM23_PIN25_DECL { DT_ALIAS_PWM_23_CH25_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH26_PIN)
#define W_PWM23_PIN26_DECL { DT_ALIAS_PWM_23_CH26_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH27_PIN)
#define W_PWM23_PIN27_DECL { DT_ALIAS_PWM_23_CH27_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH28_PIN)
#define W_PWM23_PIN28_DECL { DT_ALIAS_PWM_23_CH28_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH29_PIN)
#define W_PWM23_PIN29_DECL { DT_ALIAS_PWM_23_CH29_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH30_PIN)
#define W_PWM23_PIN30_DECL { DT_ALIAS_PWM_23_CH30_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_23_CH31_PIN)
#define W_PWM23_PIN31_DECL { DT_ALIAS_PWM_23_CH31_PIN, DT_ALIAS_PWM_23_LABEL },
#else
#define W_PWM23_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH0_PIN)
#define W_PWM24_PIN0_DECL { DT_ALIAS_PWM_24_CH0_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH1_PIN)
#define W_PWM24_PIN1_DECL { DT_ALIAS_PWM_24_CH1_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH2_PIN)
#define W_PWM24_PIN2_DECL { DT_ALIAS_PWM_24_CH2_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH3_PIN)
#define W_PWM24_PIN3_DECL { DT_ALIAS_PWM_24_CH3_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH4_PIN)
#define W_PWM24_PIN4_DECL { DT_ALIAS_PWM_24_CH4_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH5_PIN)
#define W_PWM24_PIN5_DECL { DT_ALIAS_PWM_24_CH5_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH6_PIN)
#define W_PWM24_PIN6_DECL { DT_ALIAS_PWM_24_CH6_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH7_PIN)
#define W_PWM24_PIN7_DECL { DT_ALIAS_PWM_24_CH7_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH8_PIN)
#define W_PWM24_PIN8_DECL { DT_ALIAS_PWM_24_CH8_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH9_PIN)
#define W_PWM24_PIN9_DECL { DT_ALIAS_PWM_24_CH9_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH10_PIN)
#define W_PWM24_PIN10_DECL { DT_ALIAS_PWM_24_CH10_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH11_PIN)
#define W_PWM24_PIN11_DECL { DT_ALIAS_PWM_24_CH11_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH12_PIN)
#define W_PWM24_PIN12_DECL { DT_ALIAS_PWM_24_CH12_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH13_PIN)
#define W_PWM24_PIN13_DECL { DT_ALIAS_PWM_24_CH13_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH14_PIN)
#define W_PWM24_PIN14_DECL { DT_ALIAS_PWM_24_CH14_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH15_PIN)
#define W_PWM24_PIN15_DECL { DT_ALIAS_PWM_24_CH15_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH16_PIN)
#define W_PWM24_PIN16_DECL { DT_ALIAS_PWM_24_CH16_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH17_PIN)
#define W_PWM24_PIN17_DECL { DT_ALIAS_PWM_24_CH17_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH18_PIN)
#define W_PWM24_PIN18_DECL { DT_ALIAS_PWM_24_CH18_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH19_PIN)
#define W_PWM24_PIN19_DECL { DT_ALIAS_PWM_24_CH19_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH20_PIN)
#define W_PWM24_PIN20_DECL { DT_ALIAS_PWM_24_CH20_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH21_PIN)
#define W_PWM24_PIN21_DECL { DT_ALIAS_PWM_24_CH21_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH22_PIN)
#define W_PWM24_PIN22_DECL { DT_ALIAS_PWM_24_CH22_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH23_PIN)
#define W_PWM24_PIN23_DECL { DT_ALIAS_PWM_24_CH23_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH24_PIN)
#define W_PWM24_PIN24_DECL { DT_ALIAS_PWM_24_CH24_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH25_PIN)
#define W_PWM24_PIN25_DECL { DT_ALIAS_PWM_24_CH25_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH26_PIN)
#define W_PWM24_PIN26_DECL { DT_ALIAS_PWM_24_CH26_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH27_PIN)
#define W_PWM24_PIN27_DECL { DT_ALIAS_PWM_24_CH27_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH28_PIN)
#define W_PWM24_PIN28_DECL { DT_ALIAS_PWM_24_CH28_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH29_PIN)
#define W_PWM24_PIN29_DECL { DT_ALIAS_PWM_24_CH29_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH30_PIN)
#define W_PWM24_PIN30_DECL { DT_ALIAS_PWM_24_CH30_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_24_CH31_PIN)
#define W_PWM24_PIN31_DECL { DT_ALIAS_PWM_24_CH31_PIN, DT_ALIAS_PWM_24_LABEL },
#else
#define W_PWM24_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH0_PIN)
#define W_PWM25_PIN0_DECL { DT_ALIAS_PWM_25_CH0_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH1_PIN)
#define W_PWM25_PIN1_DECL { DT_ALIAS_PWM_25_CH1_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH2_PIN)
#define W_PWM25_PIN2_DECL { DT_ALIAS_PWM_25_CH2_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH3_PIN)
#define W_PWM25_PIN3_DECL { DT_ALIAS_PWM_25_CH3_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH4_PIN)
#define W_PWM25_PIN4_DECL { DT_ALIAS_PWM_25_CH4_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH5_PIN)
#define W_PWM25_PIN5_DECL { DT_ALIAS_PWM_25_CH5_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH6_PIN)
#define W_PWM25_PIN6_DECL { DT_ALIAS_PWM_25_CH6_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH7_PIN)
#define W_PWM25_PIN7_DECL { DT_ALIAS_PWM_25_CH7_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH8_PIN)
#define W_PWM25_PIN8_DECL { DT_ALIAS_PWM_25_CH8_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH9_PIN)
#define W_PWM25_PIN9_DECL { DT_ALIAS_PWM_25_CH9_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH10_PIN)
#define W_PWM25_PIN10_DECL { DT_ALIAS_PWM_25_CH10_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH11_PIN)
#define W_PWM25_PIN11_DECL { DT_ALIAS_PWM_25_CH11_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH12_PIN)
#define W_PWM25_PIN12_DECL { DT_ALIAS_PWM_25_CH12_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH13_PIN)
#define W_PWM25_PIN13_DECL { DT_ALIAS_PWM_25_CH13_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH14_PIN)
#define W_PWM25_PIN14_DECL { DT_ALIAS_PWM_25_CH14_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH15_PIN)
#define W_PWM25_PIN15_DECL { DT_ALIAS_PWM_25_CH15_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH16_PIN)
#define W_PWM25_PIN16_DECL { DT_ALIAS_PWM_25_CH16_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH17_PIN)
#define W_PWM25_PIN17_DECL { DT_ALIAS_PWM_25_CH17_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH18_PIN)
#define W_PWM25_PIN18_DECL { DT_ALIAS_PWM_25_CH18_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH19_PIN)
#define W_PWM25_PIN19_DECL { DT_ALIAS_PWM_25_CH19_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH20_PIN)
#define W_PWM25_PIN20_DECL { DT_ALIAS_PWM_25_CH20_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH21_PIN)
#define W_PWM25_PIN21_DECL { DT_ALIAS_PWM_25_CH21_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH22_PIN)
#define W_PWM25_PIN22_DECL { DT_ALIAS_PWM_25_CH22_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH23_PIN)
#define W_PWM25_PIN23_DECL { DT_ALIAS_PWM_25_CH23_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH24_PIN)
#define W_PWM25_PIN24_DECL { DT_ALIAS_PWM_25_CH24_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH25_PIN)
#define W_PWM25_PIN25_DECL { DT_ALIAS_PWM_25_CH25_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH26_PIN)
#define W_PWM25_PIN26_DECL { DT_ALIAS_PWM_25_CH26_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH27_PIN)
#define W_PWM25_PIN27_DECL { DT_ALIAS_PWM_25_CH27_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH28_PIN)
#define W_PWM25_PIN28_DECL { DT_ALIAS_PWM_25_CH28_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH29_PIN)
#define W_PWM25_PIN29_DECL { DT_ALIAS_PWM_25_CH29_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH30_PIN)
#define W_PWM25_PIN30_DECL { DT_ALIAS_PWM_25_CH30_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_25_CH31_PIN)
#define W_PWM25_PIN31_DECL { DT_ALIAS_PWM_25_CH31_PIN, DT_ALIAS_PWM_25_LABEL },
#else
#define W_PWM25_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH0_PIN)
#define W_PWM26_PIN0_DECL { DT_ALIAS_PWM_26_CH0_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH1_PIN)
#define W_PWM26_PIN1_DECL { DT_ALIAS_PWM_26_CH1_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH2_PIN)
#define W_PWM26_PIN2_DECL { DT_ALIAS_PWM_26_CH2_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH3_PIN)
#define W_PWM26_PIN3_DECL { DT_ALIAS_PWM_26_CH3_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH4_PIN)
#define W_PWM26_PIN4_DECL { DT_ALIAS_PWM_26_CH4_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH5_PIN)
#define W_PWM26_PIN5_DECL { DT_ALIAS_PWM_26_CH5_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH6_PIN)
#define W_PWM26_PIN6_DECL { DT_ALIAS_PWM_26_CH6_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH7_PIN)
#define W_PWM26_PIN7_DECL { DT_ALIAS_PWM_26_CH7_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH8_PIN)
#define W_PWM26_PIN8_DECL { DT_ALIAS_PWM_26_CH8_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH9_PIN)
#define W_PWM26_PIN9_DECL { DT_ALIAS_PWM_26_CH9_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH10_PIN)
#define W_PWM26_PIN10_DECL { DT_ALIAS_PWM_26_CH10_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH11_PIN)
#define W_PWM26_PIN11_DECL { DT_ALIAS_PWM_26_CH11_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH12_PIN)
#define W_PWM26_PIN12_DECL { DT_ALIAS_PWM_26_CH12_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH13_PIN)
#define W_PWM26_PIN13_DECL { DT_ALIAS_PWM_26_CH13_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH14_PIN)
#define W_PWM26_PIN14_DECL { DT_ALIAS_PWM_26_CH14_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH15_PIN)
#define W_PWM26_PIN15_DECL { DT_ALIAS_PWM_26_CH15_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH16_PIN)
#define W_PWM26_PIN16_DECL { DT_ALIAS_PWM_26_CH16_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH17_PIN)
#define W_PWM26_PIN17_DECL { DT_ALIAS_PWM_26_CH17_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH18_PIN)
#define W_PWM26_PIN18_DECL { DT_ALIAS_PWM_26_CH18_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH19_PIN)
#define W_PWM26_PIN19_DECL { DT_ALIAS_PWM_26_CH19_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH20_PIN)
#define W_PWM26_PIN20_DECL { DT_ALIAS_PWM_26_CH20_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH21_PIN)
#define W_PWM26_PIN21_DECL { DT_ALIAS_PWM_26_CH21_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH22_PIN)
#define W_PWM26_PIN22_DECL { DT_ALIAS_PWM_26_CH22_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH23_PIN)
#define W_PWM26_PIN23_DECL { DT_ALIAS_PWM_26_CH23_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH24_PIN)
#define W_PWM26_PIN24_DECL { DT_ALIAS_PWM_26_CH24_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH25_PIN)
#define W_PWM26_PIN25_DECL { DT_ALIAS_PWM_26_CH25_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH26_PIN)
#define W_PWM26_PIN26_DECL { DT_ALIAS_PWM_26_CH26_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH27_PIN)
#define W_PWM26_PIN27_DECL { DT_ALIAS_PWM_26_CH27_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH28_PIN)
#define W_PWM26_PIN28_DECL { DT_ALIAS_PWM_26_CH28_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH29_PIN)
#define W_PWM26_PIN29_DECL { DT_ALIAS_PWM_26_CH29_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH30_PIN)
#define W_PWM26_PIN30_DECL { DT_ALIAS_PWM_26_CH30_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_26_CH31_PIN)
#define W_PWM26_PIN31_DECL { DT_ALIAS_PWM_26_CH31_PIN, DT_ALIAS_PWM_26_LABEL },
#else
#define W_PWM26_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH0_PIN)
#define W_PWM27_PIN0_DECL { DT_ALIAS_PWM_27_CH0_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH1_PIN)
#define W_PWM27_PIN1_DECL { DT_ALIAS_PWM_27_CH1_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH2_PIN)
#define W_PWM27_PIN2_DECL { DT_ALIAS_PWM_27_CH2_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH3_PIN)
#define W_PWM27_PIN3_DECL { DT_ALIAS_PWM_27_CH3_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH4_PIN)
#define W_PWM27_PIN4_DECL { DT_ALIAS_PWM_27_CH4_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH5_PIN)
#define W_PWM27_PIN5_DECL { DT_ALIAS_PWM_27_CH5_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH6_PIN)
#define W_PWM27_PIN6_DECL { DT_ALIAS_PWM_27_CH6_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH7_PIN)
#define W_PWM27_PIN7_DECL { DT_ALIAS_PWM_27_CH7_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH8_PIN)
#define W_PWM27_PIN8_DECL { DT_ALIAS_PWM_27_CH8_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH9_PIN)
#define W_PWM27_PIN9_DECL { DT_ALIAS_PWM_27_CH9_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH10_PIN)
#define W_PWM27_PIN10_DECL { DT_ALIAS_PWM_27_CH10_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH11_PIN)
#define W_PWM27_PIN11_DECL { DT_ALIAS_PWM_27_CH11_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH12_PIN)
#define W_PWM27_PIN12_DECL { DT_ALIAS_PWM_27_CH12_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH13_PIN)
#define W_PWM27_PIN13_DECL { DT_ALIAS_PWM_27_CH13_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH14_PIN)
#define W_PWM27_PIN14_DECL { DT_ALIAS_PWM_27_CH14_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH15_PIN)
#define W_PWM27_PIN15_DECL { DT_ALIAS_PWM_27_CH15_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH16_PIN)
#define W_PWM27_PIN16_DECL { DT_ALIAS_PWM_27_CH16_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH17_PIN)
#define W_PWM27_PIN17_DECL { DT_ALIAS_PWM_27_CH17_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH18_PIN)
#define W_PWM27_PIN18_DECL { DT_ALIAS_PWM_27_CH18_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH19_PIN)
#define W_PWM27_PIN19_DECL { DT_ALIAS_PWM_27_CH19_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH20_PIN)
#define W_PWM27_PIN20_DECL { DT_ALIAS_PWM_27_CH20_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH21_PIN)
#define W_PWM27_PIN21_DECL { DT_ALIAS_PWM_27_CH21_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH22_PIN)
#define W_PWM27_PIN22_DECL { DT_ALIAS_PWM_27_CH22_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH23_PIN)
#define W_PWM27_PIN23_DECL { DT_ALIAS_PWM_27_CH23_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH24_PIN)
#define W_PWM27_PIN24_DECL { DT_ALIAS_PWM_27_CH24_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH25_PIN)
#define W_PWM27_PIN25_DECL { DT_ALIAS_PWM_27_CH25_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH26_PIN)
#define W_PWM27_PIN26_DECL { DT_ALIAS_PWM_27_CH26_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH27_PIN)
#define W_PWM27_PIN27_DECL { DT_ALIAS_PWM_27_CH27_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH28_PIN)
#define W_PWM27_PIN28_DECL { DT_ALIAS_PWM_27_CH28_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH29_PIN)
#define W_PWM27_PIN29_DECL { DT_ALIAS_PWM_27_CH29_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH30_PIN)
#define W_PWM27_PIN30_DECL { DT_ALIAS_PWM_27_CH30_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_27_CH31_PIN)
#define W_PWM27_PIN31_DECL { DT_ALIAS_PWM_27_CH31_PIN, DT_ALIAS_PWM_27_LABEL },
#else
#define W_PWM27_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH0_PIN)
#define W_PWM28_PIN0_DECL { DT_ALIAS_PWM_28_CH0_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH1_PIN)
#define W_PWM28_PIN1_DECL { DT_ALIAS_PWM_28_CH1_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH2_PIN)
#define W_PWM28_PIN2_DECL { DT_ALIAS_PWM_28_CH2_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH3_PIN)
#define W_PWM28_PIN3_DECL { DT_ALIAS_PWM_28_CH3_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH4_PIN)
#define W_PWM28_PIN4_DECL { DT_ALIAS_PWM_28_CH4_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH5_PIN)
#define W_PWM28_PIN5_DECL { DT_ALIAS_PWM_28_CH5_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH6_PIN)
#define W_PWM28_PIN6_DECL { DT_ALIAS_PWM_28_CH6_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH7_PIN)
#define W_PWM28_PIN7_DECL { DT_ALIAS_PWM_28_CH7_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH8_PIN)
#define W_PWM28_PIN8_DECL { DT_ALIAS_PWM_28_CH8_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH9_PIN)
#define W_PWM28_PIN9_DECL { DT_ALIAS_PWM_28_CH9_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH10_PIN)
#define W_PWM28_PIN10_DECL { DT_ALIAS_PWM_28_CH10_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH11_PIN)
#define W_PWM28_PIN11_DECL { DT_ALIAS_PWM_28_CH11_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH12_PIN)
#define W_PWM28_PIN12_DECL { DT_ALIAS_PWM_28_CH12_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH13_PIN)
#define W_PWM28_PIN13_DECL { DT_ALIAS_PWM_28_CH13_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH14_PIN)
#define W_PWM28_PIN14_DECL { DT_ALIAS_PWM_28_CH14_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH15_PIN)
#define W_PWM28_PIN15_DECL { DT_ALIAS_PWM_28_CH15_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH16_PIN)
#define W_PWM28_PIN16_DECL { DT_ALIAS_PWM_28_CH16_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH17_PIN)
#define W_PWM28_PIN17_DECL { DT_ALIAS_PWM_28_CH17_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH18_PIN)
#define W_PWM28_PIN18_DECL { DT_ALIAS_PWM_28_CH18_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH19_PIN)
#define W_PWM28_PIN19_DECL { DT_ALIAS_PWM_28_CH19_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH20_PIN)
#define W_PWM28_PIN20_DECL { DT_ALIAS_PWM_28_CH20_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH21_PIN)
#define W_PWM28_PIN21_DECL { DT_ALIAS_PWM_28_CH21_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH22_PIN)
#define W_PWM28_PIN22_DECL { DT_ALIAS_PWM_28_CH22_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH23_PIN)
#define W_PWM28_PIN23_DECL { DT_ALIAS_PWM_28_CH23_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH24_PIN)
#define W_PWM28_PIN24_DECL { DT_ALIAS_PWM_28_CH24_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH25_PIN)
#define W_PWM28_PIN25_DECL { DT_ALIAS_PWM_28_CH25_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH26_PIN)
#define W_PWM28_PIN26_DECL { DT_ALIAS_PWM_28_CH26_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH27_PIN)
#define W_PWM28_PIN27_DECL { DT_ALIAS_PWM_28_CH27_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH28_PIN)
#define W_PWM28_PIN28_DECL { DT_ALIAS_PWM_28_CH28_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH29_PIN)
#define W_PWM28_PIN29_DECL { DT_ALIAS_PWM_28_CH29_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH30_PIN)
#define W_PWM28_PIN30_DECL { DT_ALIAS_PWM_28_CH30_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_28_CH31_PIN)
#define W_PWM28_PIN31_DECL { DT_ALIAS_PWM_28_CH31_PIN, DT_ALIAS_PWM_28_LABEL },
#else
#define W_PWM28_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH0_PIN)
#define W_PWM29_PIN0_DECL { DT_ALIAS_PWM_29_CH0_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH1_PIN)
#define W_PWM29_PIN1_DECL { DT_ALIAS_PWM_29_CH1_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH2_PIN)
#define W_PWM29_PIN2_DECL { DT_ALIAS_PWM_29_CH2_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH3_PIN)
#define W_PWM29_PIN3_DECL { DT_ALIAS_PWM_29_CH3_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH4_PIN)
#define W_PWM29_PIN4_DECL { DT_ALIAS_PWM_29_CH4_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH5_PIN)
#define W_PWM29_PIN5_DECL { DT_ALIAS_PWM_29_CH5_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH6_PIN)
#define W_PWM29_PIN6_DECL { DT_ALIAS_PWM_29_CH6_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH7_PIN)
#define W_PWM29_PIN7_DECL { DT_ALIAS_PWM_29_CH7_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH8_PIN)
#define W_PWM29_PIN8_DECL { DT_ALIAS_PWM_29_CH8_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH9_PIN)
#define W_PWM29_PIN9_DECL { DT_ALIAS_PWM_29_CH9_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH10_PIN)
#define W_PWM29_PIN10_DECL { DT_ALIAS_PWM_29_CH10_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH11_PIN)
#define W_PWM29_PIN11_DECL { DT_ALIAS_PWM_29_CH11_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH12_PIN)
#define W_PWM29_PIN12_DECL { DT_ALIAS_PWM_29_CH12_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH13_PIN)
#define W_PWM29_PIN13_DECL { DT_ALIAS_PWM_29_CH13_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH14_PIN)
#define W_PWM29_PIN14_DECL { DT_ALIAS_PWM_29_CH14_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH15_PIN)
#define W_PWM29_PIN15_DECL { DT_ALIAS_PWM_29_CH15_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH16_PIN)
#define W_PWM29_PIN16_DECL { DT_ALIAS_PWM_29_CH16_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH17_PIN)
#define W_PWM29_PIN17_DECL { DT_ALIAS_PWM_29_CH17_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH18_PIN)
#define W_PWM29_PIN18_DECL { DT_ALIAS_PWM_29_CH18_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH19_PIN)
#define W_PWM29_PIN19_DECL { DT_ALIAS_PWM_29_CH19_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH20_PIN)
#define W_PWM29_PIN20_DECL { DT_ALIAS_PWM_29_CH20_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH21_PIN)
#define W_PWM29_PIN21_DECL { DT_ALIAS_PWM_29_CH21_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH22_PIN)
#define W_PWM29_PIN22_DECL { DT_ALIAS_PWM_29_CH22_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH23_PIN)
#define W_PWM29_PIN23_DECL { DT_ALIAS_PWM_29_CH23_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH24_PIN)
#define W_PWM29_PIN24_DECL { DT_ALIAS_PWM_29_CH24_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH25_PIN)
#define W_PWM29_PIN25_DECL { DT_ALIAS_PWM_29_CH25_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH26_PIN)
#define W_PWM29_PIN26_DECL { DT_ALIAS_PWM_29_CH26_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH27_PIN)
#define W_PWM29_PIN27_DECL { DT_ALIAS_PWM_29_CH27_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH28_PIN)
#define W_PWM29_PIN28_DECL { DT_ALIAS_PWM_29_CH28_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH29_PIN)
#define W_PWM29_PIN29_DECL { DT_ALIAS_PWM_29_CH29_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH30_PIN)
#define W_PWM29_PIN30_DECL { DT_ALIAS_PWM_29_CH30_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_29_CH31_PIN)
#define W_PWM29_PIN31_DECL { DT_ALIAS_PWM_29_CH31_PIN, DT_ALIAS_PWM_29_LABEL },
#else
#define W_PWM29_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH0_PIN)
#define W_PWM30_PIN0_DECL { DT_ALIAS_PWM_30_CH0_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH1_PIN)
#define W_PWM30_PIN1_DECL { DT_ALIAS_PWM_30_CH1_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH2_PIN)
#define W_PWM30_PIN2_DECL { DT_ALIAS_PWM_30_CH2_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH3_PIN)
#define W_PWM30_PIN3_DECL { DT_ALIAS_PWM_30_CH3_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH4_PIN)
#define W_PWM30_PIN4_DECL { DT_ALIAS_PWM_30_CH4_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH5_PIN)
#define W_PWM30_PIN5_DECL { DT_ALIAS_PWM_30_CH5_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH6_PIN)
#define W_PWM30_PIN6_DECL { DT_ALIAS_PWM_30_CH6_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH7_PIN)
#define W_PWM30_PIN7_DECL { DT_ALIAS_PWM_30_CH7_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH8_PIN)
#define W_PWM30_PIN8_DECL { DT_ALIAS_PWM_30_CH8_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH9_PIN)
#define W_PWM30_PIN9_DECL { DT_ALIAS_PWM_30_CH9_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH10_PIN)
#define W_PWM30_PIN10_DECL { DT_ALIAS_PWM_30_CH10_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH11_PIN)
#define W_PWM30_PIN11_DECL { DT_ALIAS_PWM_30_CH11_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH12_PIN)
#define W_PWM30_PIN12_DECL { DT_ALIAS_PWM_30_CH12_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH13_PIN)
#define W_PWM30_PIN13_DECL { DT_ALIAS_PWM_30_CH13_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH14_PIN)
#define W_PWM30_PIN14_DECL { DT_ALIAS_PWM_30_CH14_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH15_PIN)
#define W_PWM30_PIN15_DECL { DT_ALIAS_PWM_30_CH15_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH16_PIN)
#define W_PWM30_PIN16_DECL { DT_ALIAS_PWM_30_CH16_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH17_PIN)
#define W_PWM30_PIN17_DECL { DT_ALIAS_PWM_30_CH17_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH18_PIN)
#define W_PWM30_PIN18_DECL { DT_ALIAS_PWM_30_CH18_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH19_PIN)
#define W_PWM30_PIN19_DECL { DT_ALIAS_PWM_30_CH19_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH20_PIN)
#define W_PWM30_PIN20_DECL { DT_ALIAS_PWM_30_CH20_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH21_PIN)
#define W_PWM30_PIN21_DECL { DT_ALIAS_PWM_30_CH21_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH22_PIN)
#define W_PWM30_PIN22_DECL { DT_ALIAS_PWM_30_CH22_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH23_PIN)
#define W_PWM30_PIN23_DECL { DT_ALIAS_PWM_30_CH23_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH24_PIN)
#define W_PWM30_PIN24_DECL { DT_ALIAS_PWM_30_CH24_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH25_PIN)
#define W_PWM30_PIN25_DECL { DT_ALIAS_PWM_30_CH25_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH26_PIN)
#define W_PWM30_PIN26_DECL { DT_ALIAS_PWM_30_CH26_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH27_PIN)
#define W_PWM30_PIN27_DECL { DT_ALIAS_PWM_30_CH27_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH28_PIN)
#define W_PWM30_PIN28_DECL { DT_ALIAS_PWM_30_CH28_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH29_PIN)
#define W_PWM30_PIN29_DECL { DT_ALIAS_PWM_30_CH29_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH30_PIN)
#define W_PWM30_PIN30_DECL { DT_ALIAS_PWM_30_CH30_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_30_CH31_PIN)
#define W_PWM30_PIN31_DECL { DT_ALIAS_PWM_30_CH31_PIN, DT_ALIAS_PWM_30_LABEL },
#else
#define W_PWM30_PIN31_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH0_PIN)
#define W_PWM31_PIN0_DECL { DT_ALIAS_PWM_31_CH0_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN0_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH1_PIN)
#define W_PWM31_PIN1_DECL { DT_ALIAS_PWM_31_CH1_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN1_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH2_PIN)
#define W_PWM31_PIN2_DECL { DT_ALIAS_PWM_31_CH2_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN2_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH3_PIN)
#define W_PWM31_PIN3_DECL { DT_ALIAS_PWM_31_CH3_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN3_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH4_PIN)
#define W_PWM31_PIN4_DECL { DT_ALIAS_PWM_31_CH4_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN4_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH5_PIN)
#define W_PWM31_PIN5_DECL { DT_ALIAS_PWM_31_CH5_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN5_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH6_PIN)
#define W_PWM31_PIN6_DECL { DT_ALIAS_PWM_31_CH6_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN6_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH7_PIN)
#define W_PWM31_PIN7_DECL { DT_ALIAS_PWM_31_CH7_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN7_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH8_PIN)
#define W_PWM31_PIN8_DECL { DT_ALIAS_PWM_31_CH8_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN8_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH9_PIN)
#define W_PWM31_PIN9_DECL { DT_ALIAS_PWM_31_CH9_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN9_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH10_PIN)
#define W_PWM31_PIN10_DECL { DT_ALIAS_PWM_31_CH10_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN10_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH11_PIN)
#define W_PWM31_PIN11_DECL { DT_ALIAS_PWM_31_CH11_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN11_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH12_PIN)
#define W_PWM31_PIN12_DECL { DT_ALIAS_PWM_31_CH12_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN12_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH13_PIN)
#define W_PWM31_PIN13_DECL { DT_ALIAS_PWM_31_CH13_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN13_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH14_PIN)
#define W_PWM31_PIN14_DECL { DT_ALIAS_PWM_31_CH14_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN14_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH15_PIN)
#define W_PWM31_PIN15_DECL { DT_ALIAS_PWM_31_CH15_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN15_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH16_PIN)
#define W_PWM31_PIN16_DECL { DT_ALIAS_PWM_31_CH16_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN16_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH17_PIN)
#define W_PWM31_PIN17_DECL { DT_ALIAS_PWM_31_CH17_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN17_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH18_PIN)
#define W_PWM31_PIN18_DECL { DT_ALIAS_PWM_31_CH18_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN18_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH19_PIN)
#define W_PWM31_PIN19_DECL { DT_ALIAS_PWM_31_CH19_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN19_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH20_PIN)
#define W_PWM31_PIN20_DECL { DT_ALIAS_PWM_31_CH20_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN20_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH21_PIN)
#define W_PWM31_PIN21_DECL { DT_ALIAS_PWM_31_CH21_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN21_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH22_PIN)
#define W_PWM31_PIN22_DECL { DT_ALIAS_PWM_31_CH22_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN22_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH23_PIN)
#define W_PWM31_PIN23_DECL { DT_ALIAS_PWM_31_CH23_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN23_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH24_PIN)
#define W_PWM31_PIN24_DECL { DT_ALIAS_PWM_31_CH24_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN24_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH25_PIN)
#define W_PWM31_PIN25_DECL { DT_ALIAS_PWM_31_CH25_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN25_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH26_PIN)
#define W_PWM31_PIN26_DECL { DT_ALIAS_PWM_31_CH26_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN26_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH27_PIN)
#define W_PWM31_PIN27_DECL { DT_ALIAS_PWM_31_CH27_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN27_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH28_PIN)
#define W_PWM31_PIN28_DECL { DT_ALIAS_PWM_31_CH28_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN28_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH29_PIN)
#define W_PWM31_PIN29_DECL { DT_ALIAS_PWM_31_CH29_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN29_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH30_PIN)
#define W_PWM31_PIN30_DECL { DT_ALIAS_PWM_31_CH30_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN30_DECL
#endif
#if defined(DT_ALIAS_PWM_31_CH31_PIN)
#define W_PWM31_PIN31_DECL { DT_ALIAS_PWM_31_CH31_PIN, DT_ALIAS_PWM_31_LABEL },
#else
#define W_PWM31_PIN31_DECL
#endif

#ifndef W_PWM_PIN2DEV_MAP
#define W_PWM_PIN2DEV_MAP {\
W_PWM0_PIN0_DECL \
W_PWM0_PIN1_DECL \
W_PWM0_PIN2_DECL \
W_PWM0_PIN3_DECL \
W_PWM0_PIN4_DECL \
W_PWM0_PIN5_DECL \
W_PWM0_PIN6_DECL \
W_PWM0_PIN7_DECL \
W_PWM0_PIN8_DECL \
W_PWM0_PIN9_DECL \
W_PWM0_PIN10_DECL \
W_PWM0_PIN11_DECL \
W_PWM0_PIN12_DECL \
W_PWM0_PIN13_DECL \
W_PWM0_PIN14_DECL \
W_PWM0_PIN15_DECL \
W_PWM0_PIN16_DECL \
W_PWM0_PIN17_DECL \
W_PWM0_PIN18_DECL \
W_PWM0_PIN19_DECL \
W_PWM0_PIN20_DECL \
W_PWM0_PIN21_DECL \
W_PWM0_PIN22_DECL \
W_PWM0_PIN23_DECL \
W_PWM0_PIN24_DECL \
W_PWM0_PIN25_DECL \
W_PWM0_PIN26_DECL \
W_PWM0_PIN27_DECL \
W_PWM0_PIN28_DECL \
W_PWM0_PIN29_DECL \
W_PWM0_PIN30_DECL \
W_PWM0_PIN31_DECL \
W_PWM1_PIN0_DECL \
W_PWM1_PIN1_DECL \
W_PWM1_PIN2_DECL \
W_PWM1_PIN3_DECL \
W_PWM1_PIN4_DECL \
W_PWM1_PIN5_DECL \
W_PWM1_PIN6_DECL \
W_PWM1_PIN7_DECL \
W_PWM1_PIN8_DECL \
W_PWM1_PIN9_DECL \
W_PWM1_PIN10_DECL \
W_PWM1_PIN11_DECL \
W_PWM1_PIN12_DECL \
W_PWM1_PIN13_DECL \
W_PWM1_PIN14_DECL \
W_PWM1_PIN15_DECL \
W_PWM1_PIN16_DECL \
W_PWM1_PIN17_DECL \
W_PWM1_PIN18_DECL \
W_PWM1_PIN19_DECL \
W_PWM1_PIN20_DECL \
W_PWM1_PIN21_DECL \
W_PWM1_PIN22_DECL \
W_PWM1_PIN23_DECL \
W_PWM1_PIN24_DECL \
W_PWM1_PIN25_DECL \
W_PWM1_PIN26_DECL \
W_PWM1_PIN27_DECL \
W_PWM1_PIN28_DECL \
W_PWM1_PIN29_DECL \
W_PWM1_PIN30_DECL \
W_PWM1_PIN31_DECL \
W_PWM2_PIN0_DECL \
W_PWM2_PIN1_DECL \
W_PWM2_PIN2_DECL \
W_PWM2_PIN3_DECL \
W_PWM2_PIN4_DECL \
W_PWM2_PIN5_DECL \
W_PWM2_PIN6_DECL \
W_PWM2_PIN7_DECL \
W_PWM2_PIN8_DECL \
W_PWM2_PIN9_DECL \
W_PWM2_PIN10_DECL \
W_PWM2_PIN11_DECL \
W_PWM2_PIN12_DECL \
W_PWM2_PIN13_DECL \
W_PWM2_PIN14_DECL \
W_PWM2_PIN15_DECL \
W_PWM2_PIN16_DECL \
W_PWM2_PIN17_DECL \
W_PWM2_PIN18_DECL \
W_PWM2_PIN19_DECL \
W_PWM2_PIN20_DECL \
W_PWM2_PIN21_DECL \
W_PWM2_PIN22_DECL \
W_PWM2_PIN23_DECL \
W_PWM2_PIN24_DECL \
W_PWM2_PIN25_DECL \
W_PWM2_PIN26_DECL \
W_PWM2_PIN27_DECL \
W_PWM2_PIN28_DECL \
W_PWM2_PIN29_DECL \
W_PWM2_PIN30_DECL \
W_PWM2_PIN31_DECL \
W_PWM3_PIN0_DECL \
W_PWM3_PIN1_DECL \
W_PWM3_PIN2_DECL \
W_PWM3_PIN3_DECL \
W_PWM3_PIN4_DECL \
W_PWM3_PIN5_DECL \
W_PWM3_PIN6_DECL \
W_PWM3_PIN7_DECL \
W_PWM3_PIN8_DECL \
W_PWM3_PIN9_DECL \
W_PWM3_PIN10_DECL \
W_PWM3_PIN11_DECL \
W_PWM3_PIN12_DECL \
W_PWM3_PIN13_DECL \
W_PWM3_PIN14_DECL \
W_PWM3_PIN15_DECL \
W_PWM3_PIN16_DECL \
W_PWM3_PIN17_DECL \
W_PWM3_PIN18_DECL \
W_PWM3_PIN19_DECL \
W_PWM3_PIN20_DECL \
W_PWM3_PIN21_DECL \
W_PWM3_PIN22_DECL \
W_PWM3_PIN23_DECL \
W_PWM3_PIN24_DECL \
W_PWM3_PIN25_DECL \
W_PWM3_PIN26_DECL \
W_PWM3_PIN27_DECL \
W_PWM3_PIN28_DECL \
W_PWM3_PIN29_DECL \
W_PWM3_PIN30_DECL \
W_PWM3_PIN31_DECL \
W_PWM4_PIN0_DECL \
W_PWM4_PIN1_DECL \
W_PWM4_PIN2_DECL \
W_PWM4_PIN3_DECL \
W_PWM4_PIN4_DECL \
W_PWM4_PIN5_DECL \
W_PWM4_PIN6_DECL \
W_PWM4_PIN7_DECL \
W_PWM4_PIN8_DECL \
W_PWM4_PIN9_DECL \
W_PWM4_PIN10_DECL \
W_PWM4_PIN11_DECL \
W_PWM4_PIN12_DECL \
W_PWM4_PIN13_DECL \
W_PWM4_PIN14_DECL \
W_PWM4_PIN15_DECL \
W_PWM4_PIN16_DECL \
W_PWM4_PIN17_DECL \
W_PWM4_PIN18_DECL \
W_PWM4_PIN19_DECL \
W_PWM4_PIN20_DECL \
W_PWM4_PIN21_DECL \
W_PWM4_PIN22_DECL \
W_PWM4_PIN23_DECL \
W_PWM4_PIN24_DECL \
W_PWM4_PIN25_DECL \
W_PWM4_PIN26_DECL \
W_PWM4_PIN27_DECL \
W_PWM4_PIN28_DECL \
W_PWM4_PIN29_DECL \
W_PWM4_PIN30_DECL \
W_PWM4_PIN31_DECL \
W_PWM5_PIN0_DECL \
W_PWM5_PIN1_DECL \
W_PWM5_PIN2_DECL \
W_PWM5_PIN3_DECL \
W_PWM5_PIN4_DECL \
W_PWM5_PIN5_DECL \
W_PWM5_PIN6_DECL \
W_PWM5_PIN7_DECL \
W_PWM5_PIN8_DECL \
W_PWM5_PIN9_DECL \
W_PWM5_PIN10_DECL \
W_PWM5_PIN11_DECL \
W_PWM5_PIN12_DECL \
W_PWM5_PIN13_DECL \
W_PWM5_PIN14_DECL \
W_PWM5_PIN15_DECL \
W_PWM5_PIN16_DECL \
W_PWM5_PIN17_DECL \
W_PWM5_PIN18_DECL \
W_PWM5_PIN19_DECL \
W_PWM5_PIN20_DECL \
W_PWM5_PIN21_DECL \
W_PWM5_PIN22_DECL \
W_PWM5_PIN23_DECL \
W_PWM5_PIN24_DECL \
W_PWM5_PIN25_DECL \
W_PWM5_PIN26_DECL \
W_PWM5_PIN27_DECL \
W_PWM5_PIN28_DECL \
W_PWM5_PIN29_DECL \
W_PWM5_PIN30_DECL \
W_PWM5_PIN31_DECL \
W_PWM6_PIN0_DECL \
W_PWM6_PIN1_DECL \
W_PWM6_PIN2_DECL \
W_PWM6_PIN3_DECL \
W_PWM6_PIN4_DECL \
W_PWM6_PIN5_DECL \
W_PWM6_PIN6_DECL \
W_PWM6_PIN7_DECL \
W_PWM6_PIN8_DECL \
W_PWM6_PIN9_DECL \
W_PWM6_PIN10_DECL \
W_PWM6_PIN11_DECL \
W_PWM6_PIN12_DECL \
W_PWM6_PIN13_DECL \
W_PWM6_PIN14_DECL \
W_PWM6_PIN15_DECL \
W_PWM6_PIN16_DECL \
W_PWM6_PIN17_DECL \
W_PWM6_PIN18_DECL \
W_PWM6_PIN19_DECL \
W_PWM6_PIN20_DECL \
W_PWM6_PIN21_DECL \
W_PWM6_PIN22_DECL \
W_PWM6_PIN23_DECL \
W_PWM6_PIN24_DECL \
W_PWM6_PIN25_DECL \
W_PWM6_PIN26_DECL \
W_PWM6_PIN27_DECL \
W_PWM6_PIN28_DECL \
W_PWM6_PIN29_DECL \
W_PWM6_PIN30_DECL \
W_PWM6_PIN31_DECL \
W_PWM7_PIN0_DECL \
W_PWM7_PIN1_DECL \
W_PWM7_PIN2_DECL \
W_PWM7_PIN3_DECL \
W_PWM7_PIN4_DECL \
W_PWM7_PIN5_DECL \
W_PWM7_PIN6_DECL \
W_PWM7_PIN7_DECL \
W_PWM7_PIN8_DECL \
W_PWM7_PIN9_DECL \
W_PWM7_PIN10_DECL \
W_PWM7_PIN11_DECL \
W_PWM7_PIN12_DECL \
W_PWM7_PIN13_DECL \
W_PWM7_PIN14_DECL \
W_PWM7_PIN15_DECL \
W_PWM7_PIN16_DECL \
W_PWM7_PIN17_DECL \
W_PWM7_PIN18_DECL \
W_PWM7_PIN19_DECL \
W_PWM7_PIN20_DECL \
W_PWM7_PIN21_DECL \
W_PWM7_PIN22_DECL \
W_PWM7_PIN23_DECL \
W_PWM7_PIN24_DECL \
W_PWM7_PIN25_DECL \
W_PWM7_PIN26_DECL \
W_PWM7_PIN27_DECL \
W_PWM7_PIN28_DECL \
W_PWM7_PIN29_DECL \
W_PWM7_PIN30_DECL \
W_PWM7_PIN31_DECL \
W_PWM8_PIN0_DECL \
W_PWM8_PIN1_DECL \
W_PWM8_PIN2_DECL \
W_PWM8_PIN3_DECL \
W_PWM8_PIN4_DECL \
W_PWM8_PIN5_DECL \
W_PWM8_PIN6_DECL \
W_PWM8_PIN7_DECL \
W_PWM8_PIN8_DECL \
W_PWM8_PIN9_DECL \
W_PWM8_PIN10_DECL \
W_PWM8_PIN11_DECL \
W_PWM8_PIN12_DECL \
W_PWM8_PIN13_DECL \
W_PWM8_PIN14_DECL \
W_PWM8_PIN15_DECL \
W_PWM8_PIN16_DECL \
W_PWM8_PIN17_DECL \
W_PWM8_PIN18_DECL \
W_PWM8_PIN19_DECL \
W_PWM8_PIN20_DECL \
W_PWM8_PIN21_DECL \
W_PWM8_PIN22_DECL \
W_PWM8_PIN23_DECL \
W_PWM8_PIN24_DECL \
W_PWM8_PIN25_DECL \
W_PWM8_PIN26_DECL \
W_PWM8_PIN27_DECL \
W_PWM8_PIN28_DECL \
W_PWM8_PIN29_DECL \
W_PWM8_PIN30_DECL \
W_PWM8_PIN31_DECL \
W_PWM9_PIN0_DECL \
W_PWM9_PIN1_DECL \
W_PWM9_PIN2_DECL \
W_PWM9_PIN3_DECL \
W_PWM9_PIN4_DECL \
W_PWM9_PIN5_DECL \
W_PWM9_PIN6_DECL \
W_PWM9_PIN7_DECL \
W_PWM9_PIN8_DECL \
W_PWM9_PIN9_DECL \
W_PWM9_PIN10_DECL \
W_PWM9_PIN11_DECL \
W_PWM9_PIN12_DECL \
W_PWM9_PIN13_DECL \
W_PWM9_PIN14_DECL \
W_PWM9_PIN15_DECL \
W_PWM9_PIN16_DECL \
W_PWM9_PIN17_DECL \
W_PWM9_PIN18_DECL \
W_PWM9_PIN19_DECL \
W_PWM9_PIN20_DECL \
W_PWM9_PIN21_DECL \
W_PWM9_PIN22_DECL \
W_PWM9_PIN23_DECL \
W_PWM9_PIN24_DECL \
W_PWM9_PIN25_DECL \
W_PWM9_PIN26_DECL \
W_PWM9_PIN27_DECL \
W_PWM9_PIN28_DECL \
W_PWM9_PIN29_DECL \
W_PWM9_PIN30_DECL \
W_PWM9_PIN31_DECL \
W_PWM10_PIN0_DECL \
W_PWM10_PIN1_DECL \
W_PWM10_PIN2_DECL \
W_PWM10_PIN3_DECL \
W_PWM10_PIN4_DECL \
W_PWM10_PIN5_DECL \
W_PWM10_PIN6_DECL \
W_PWM10_PIN7_DECL \
W_PWM10_PIN8_DECL \
W_PWM10_PIN9_DECL \
W_PWM10_PIN10_DECL \
W_PWM10_PIN11_DECL \
W_PWM10_PIN12_DECL \
W_PWM10_PIN13_DECL \
W_PWM10_PIN14_DECL \
W_PWM10_PIN15_DECL \
W_PWM10_PIN16_DECL \
W_PWM10_PIN17_DECL \
W_PWM10_PIN18_DECL \
W_PWM10_PIN19_DECL \
W_PWM10_PIN20_DECL \
W_PWM10_PIN21_DECL \
W_PWM10_PIN22_DECL \
W_PWM10_PIN23_DECL \
W_PWM10_PIN24_DECL \
W_PWM10_PIN25_DECL \
W_PWM10_PIN26_DECL \
W_PWM10_PIN27_DECL \
W_PWM10_PIN28_DECL \
W_PWM10_PIN29_DECL \
W_PWM10_PIN30_DECL \
W_PWM10_PIN31_DECL \
W_PWM11_PIN0_DECL \
W_PWM11_PIN1_DECL \
W_PWM11_PIN2_DECL \
W_PWM11_PIN3_DECL \
W_PWM11_PIN4_DECL \
W_PWM11_PIN5_DECL \
W_PWM11_PIN6_DECL \
W_PWM11_PIN7_DECL \
W_PWM11_PIN8_DECL \
W_PWM11_PIN9_DECL \
W_PWM11_PIN10_DECL \
W_PWM11_PIN11_DECL \
W_PWM11_PIN12_DECL \
W_PWM11_PIN13_DECL \
W_PWM11_PIN14_DECL \
W_PWM11_PIN15_DECL \
W_PWM11_PIN16_DECL \
W_PWM11_PIN17_DECL \
W_PWM11_PIN18_DECL \
W_PWM11_PIN19_DECL \
W_PWM11_PIN20_DECL \
W_PWM11_PIN21_DECL \
W_PWM11_PIN22_DECL \
W_PWM11_PIN23_DECL \
W_PWM11_PIN24_DECL \
W_PWM11_PIN25_DECL \
W_PWM11_PIN26_DECL \
W_PWM11_PIN27_DECL \
W_PWM11_PIN28_DECL \
W_PWM11_PIN29_DECL \
W_PWM11_PIN30_DECL \
W_PWM11_PIN31_DECL \
W_PWM12_PIN0_DECL \
W_PWM12_PIN1_DECL \
W_PWM12_PIN2_DECL \
W_PWM12_PIN3_DECL \
W_PWM12_PIN4_DECL \
W_PWM12_PIN5_DECL \
W_PWM12_PIN6_DECL \
W_PWM12_PIN7_DECL \
W_PWM12_PIN8_DECL \
W_PWM12_PIN9_DECL \
W_PWM12_PIN10_DECL \
W_PWM12_PIN11_DECL \
W_PWM12_PIN12_DECL \
W_PWM12_PIN13_DECL \
W_PWM12_PIN14_DECL \
W_PWM12_PIN15_DECL \
W_PWM12_PIN16_DECL \
W_PWM12_PIN17_DECL \
W_PWM12_PIN18_DECL \
W_PWM12_PIN19_DECL \
W_PWM12_PIN20_DECL \
W_PWM12_PIN21_DECL \
W_PWM12_PIN22_DECL \
W_PWM12_PIN23_DECL \
W_PWM12_PIN24_DECL \
W_PWM12_PIN25_DECL \
W_PWM12_PIN26_DECL \
W_PWM12_PIN27_DECL \
W_PWM12_PIN28_DECL \
W_PWM12_PIN29_DECL \
W_PWM12_PIN30_DECL \
W_PWM12_PIN31_DECL \
W_PWM13_PIN0_DECL \
W_PWM13_PIN1_DECL \
W_PWM13_PIN2_DECL \
W_PWM13_PIN3_DECL \
W_PWM13_PIN4_DECL \
W_PWM13_PIN5_DECL \
W_PWM13_PIN6_DECL \
W_PWM13_PIN7_DECL \
W_PWM13_PIN8_DECL \
W_PWM13_PIN9_DECL \
W_PWM13_PIN10_DECL \
W_PWM13_PIN11_DECL \
W_PWM13_PIN12_DECL \
W_PWM13_PIN13_DECL \
W_PWM13_PIN14_DECL \
W_PWM13_PIN15_DECL \
W_PWM13_PIN16_DECL \
W_PWM13_PIN17_DECL \
W_PWM13_PIN18_DECL \
W_PWM13_PIN19_DECL \
W_PWM13_PIN20_DECL \
W_PWM13_PIN21_DECL \
W_PWM13_PIN22_DECL \
W_PWM13_PIN23_DECL \
W_PWM13_PIN24_DECL \
W_PWM13_PIN25_DECL \
W_PWM13_PIN26_DECL \
W_PWM13_PIN27_DECL \
W_PWM13_PIN28_DECL \
W_PWM13_PIN29_DECL \
W_PWM13_PIN30_DECL \
W_PWM13_PIN31_DECL \
W_PWM14_PIN0_DECL \
W_PWM14_PIN1_DECL \
W_PWM14_PIN2_DECL \
W_PWM14_PIN3_DECL \
W_PWM14_PIN4_DECL \
W_PWM14_PIN5_DECL \
W_PWM14_PIN6_DECL \
W_PWM14_PIN7_DECL \
W_PWM14_PIN8_DECL \
W_PWM14_PIN9_DECL \
W_PWM14_PIN10_DECL \
W_PWM14_PIN11_DECL \
W_PWM14_PIN12_DECL \
W_PWM14_PIN13_DECL \
W_PWM14_PIN14_DECL \
W_PWM14_PIN15_DECL \
W_PWM14_PIN16_DECL \
W_PWM14_PIN17_DECL \
W_PWM14_PIN18_DECL \
W_PWM14_PIN19_DECL \
W_PWM14_PIN20_DECL \
W_PWM14_PIN21_DECL \
W_PWM14_PIN22_DECL \
W_PWM14_PIN23_DECL \
W_PWM14_PIN24_DECL \
W_PWM14_PIN25_DECL \
W_PWM14_PIN26_DECL \
W_PWM14_PIN27_DECL \
W_PWM14_PIN28_DECL \
W_PWM14_PIN29_DECL \
W_PWM14_PIN30_DECL \
W_PWM14_PIN31_DECL \
W_PWM15_PIN0_DECL \
W_PWM15_PIN1_DECL \
W_PWM15_PIN2_DECL \
W_PWM15_PIN3_DECL \
W_PWM15_PIN4_DECL \
W_PWM15_PIN5_DECL \
W_PWM15_PIN6_DECL \
W_PWM15_PIN7_DECL \
W_PWM15_PIN8_DECL \
W_PWM15_PIN9_DECL \
W_PWM15_PIN10_DECL \
W_PWM15_PIN11_DECL \
W_PWM15_PIN12_DECL \
W_PWM15_PIN13_DECL \
W_PWM15_PIN14_DECL \
W_PWM15_PIN15_DECL \
W_PWM15_PIN16_DECL \
W_PWM15_PIN17_DECL \
W_PWM15_PIN18_DECL \
W_PWM15_PIN19_DECL \
W_PWM15_PIN20_DECL \
W_PWM15_PIN21_DECL \
W_PWM15_PIN22_DECL \
W_PWM15_PIN23_DECL \
W_PWM15_PIN24_DECL \
W_PWM15_PIN25_DECL \
W_PWM15_PIN26_DECL \
W_PWM15_PIN27_DECL \
W_PWM15_PIN28_DECL \
W_PWM15_PIN29_DECL \
W_PWM15_PIN30_DECL \
W_PWM15_PIN31_DECL \
W_PWM16_PIN0_DECL \
W_PWM16_PIN1_DECL \
W_PWM16_PIN2_DECL \
W_PWM16_PIN3_DECL \
W_PWM16_PIN4_DECL \
W_PWM16_PIN5_DECL \
W_PWM16_PIN6_DECL \
W_PWM16_PIN7_DECL \
W_PWM16_PIN8_DECL \
W_PWM16_PIN9_DECL \
W_PWM16_PIN10_DECL \
W_PWM16_PIN11_DECL \
W_PWM16_PIN12_DECL \
W_PWM16_PIN13_DECL \
W_PWM16_PIN14_DECL \
W_PWM16_PIN15_DECL \
W_PWM16_PIN16_DECL \
W_PWM16_PIN17_DECL \
W_PWM16_PIN18_DECL \
W_PWM16_PIN19_DECL \
W_PWM16_PIN20_DECL \
W_PWM16_PIN21_DECL \
W_PWM16_PIN22_DECL \
W_PWM16_PIN23_DECL \
W_PWM16_PIN24_DECL \
W_PWM16_PIN25_DECL \
W_PWM16_PIN26_DECL \
W_PWM16_PIN27_DECL \
W_PWM16_PIN28_DECL \
W_PWM16_PIN29_DECL \
W_PWM16_PIN30_DECL \
W_PWM16_PIN31_DECL \
W_PWM17_PIN0_DECL \
W_PWM17_PIN1_DECL \
W_PWM17_PIN2_DECL \
W_PWM17_PIN3_DECL \
W_PWM17_PIN4_DECL \
W_PWM17_PIN5_DECL \
W_PWM17_PIN6_DECL \
W_PWM17_PIN7_DECL \
W_PWM17_PIN8_DECL \
W_PWM17_PIN9_DECL \
W_PWM17_PIN10_DECL \
W_PWM17_PIN11_DECL \
W_PWM17_PIN12_DECL \
W_PWM17_PIN13_DECL \
W_PWM17_PIN14_DECL \
W_PWM17_PIN15_DECL \
W_PWM17_PIN16_DECL \
W_PWM17_PIN17_DECL \
W_PWM17_PIN18_DECL \
W_PWM17_PIN19_DECL \
W_PWM17_PIN20_DECL \
W_PWM17_PIN21_DECL \
W_PWM17_PIN22_DECL \
W_PWM17_PIN23_DECL \
W_PWM17_PIN24_DECL \
W_PWM17_PIN25_DECL \
W_PWM17_PIN26_DECL \
W_PWM17_PIN27_DECL \
W_PWM17_PIN28_DECL \
W_PWM17_PIN29_DECL \
W_PWM17_PIN30_DECL \
W_PWM17_PIN31_DECL \
W_PWM18_PIN0_DECL \
W_PWM18_PIN1_DECL \
W_PWM18_PIN2_DECL \
W_PWM18_PIN3_DECL \
W_PWM18_PIN4_DECL \
W_PWM18_PIN5_DECL \
W_PWM18_PIN6_DECL \
W_PWM18_PIN7_DECL \
W_PWM18_PIN8_DECL \
W_PWM18_PIN9_DECL \
W_PWM18_PIN10_DECL \
W_PWM18_PIN11_DECL \
W_PWM18_PIN12_DECL \
W_PWM18_PIN13_DECL \
W_PWM18_PIN14_DECL \
W_PWM18_PIN15_DECL \
W_PWM18_PIN16_DECL \
W_PWM18_PIN17_DECL \
W_PWM18_PIN18_DECL \
W_PWM18_PIN19_DECL \
W_PWM18_PIN20_DECL \
W_PWM18_PIN21_DECL \
W_PWM18_PIN22_DECL \
W_PWM18_PIN23_DECL \
W_PWM18_PIN24_DECL \
W_PWM18_PIN25_DECL \
W_PWM18_PIN26_DECL \
W_PWM18_PIN27_DECL \
W_PWM18_PIN28_DECL \
W_PWM18_PIN29_DECL \
W_PWM18_PIN30_DECL \
W_PWM18_PIN31_DECL \
W_PWM19_PIN0_DECL \
W_PWM19_PIN1_DECL \
W_PWM19_PIN2_DECL \
W_PWM19_PIN3_DECL \
W_PWM19_PIN4_DECL \
W_PWM19_PIN5_DECL \
W_PWM19_PIN6_DECL \
W_PWM19_PIN7_DECL \
W_PWM19_PIN8_DECL \
W_PWM19_PIN9_DECL \
W_PWM19_PIN10_DECL \
W_PWM19_PIN11_DECL \
W_PWM19_PIN12_DECL \
W_PWM19_PIN13_DECL \
W_PWM19_PIN14_DECL \
W_PWM19_PIN15_DECL \
W_PWM19_PIN16_DECL \
W_PWM19_PIN17_DECL \
W_PWM19_PIN18_DECL \
W_PWM19_PIN19_DECL \
W_PWM19_PIN20_DECL \
W_PWM19_PIN21_DECL \
W_PWM19_PIN22_DECL \
W_PWM19_PIN23_DECL \
W_PWM19_PIN24_DECL \
W_PWM19_PIN25_DECL \
W_PWM19_PIN26_DECL \
W_PWM19_PIN27_DECL \
W_PWM19_PIN28_DECL \
W_PWM19_PIN29_DECL \
W_PWM19_PIN30_DECL \
W_PWM19_PIN31_DECL \
W_PWM20_PIN0_DECL \
W_PWM20_PIN1_DECL \
W_PWM20_PIN2_DECL \
W_PWM20_PIN3_DECL \
W_PWM20_PIN4_DECL \
W_PWM20_PIN5_DECL \
W_PWM20_PIN6_DECL \
W_PWM20_PIN7_DECL \
W_PWM20_PIN8_DECL \
W_PWM20_PIN9_DECL \
W_PWM20_PIN10_DECL \
W_PWM20_PIN11_DECL \
W_PWM20_PIN12_DECL \
W_PWM20_PIN13_DECL \
W_PWM20_PIN14_DECL \
W_PWM20_PIN15_DECL \
W_PWM20_PIN16_DECL \
W_PWM20_PIN17_DECL \
W_PWM20_PIN18_DECL \
W_PWM20_PIN19_DECL \
W_PWM20_PIN20_DECL \
W_PWM20_PIN21_DECL \
W_PWM20_PIN22_DECL \
W_PWM20_PIN23_DECL \
W_PWM20_PIN24_DECL \
W_PWM20_PIN25_DECL \
W_PWM20_PIN26_DECL \
W_PWM20_PIN27_DECL \
W_PWM20_PIN28_DECL \
W_PWM20_PIN29_DECL \
W_PWM20_PIN30_DECL \
W_PWM20_PIN31_DECL \
W_PWM21_PIN0_DECL \
W_PWM21_PIN1_DECL \
W_PWM21_PIN2_DECL \
W_PWM21_PIN3_DECL \
W_PWM21_PIN4_DECL \
W_PWM21_PIN5_DECL \
W_PWM21_PIN6_DECL \
W_PWM21_PIN7_DECL \
W_PWM21_PIN8_DECL \
W_PWM21_PIN9_DECL \
W_PWM21_PIN10_DECL \
W_PWM21_PIN11_DECL \
W_PWM21_PIN12_DECL \
W_PWM21_PIN13_DECL \
W_PWM21_PIN14_DECL \
W_PWM21_PIN15_DECL \
W_PWM21_PIN16_DECL \
W_PWM21_PIN17_DECL \
W_PWM21_PIN18_DECL \
W_PWM21_PIN19_DECL \
W_PWM21_PIN20_DECL \
W_PWM21_PIN21_DECL \
W_PWM21_PIN22_DECL \
W_PWM21_PIN23_DECL \
W_PWM21_PIN24_DECL \
W_PWM21_PIN25_DECL \
W_PWM21_PIN26_DECL \
W_PWM21_PIN27_DECL \
W_PWM21_PIN28_DECL \
W_PWM21_PIN29_DECL \
W_PWM21_PIN30_DECL \
W_PWM21_PIN31_DECL \
W_PWM22_PIN0_DECL \
W_PWM22_PIN1_DECL \
W_PWM22_PIN2_DECL \
W_PWM22_PIN3_DECL \
W_PWM22_PIN4_DECL \
W_PWM22_PIN5_DECL \
W_PWM22_PIN6_DECL \
W_PWM22_PIN7_DECL \
W_PWM22_PIN8_DECL \
W_PWM22_PIN9_DECL \
W_PWM22_PIN10_DECL \
W_PWM22_PIN11_DECL \
W_PWM22_PIN12_DECL \
W_PWM22_PIN13_DECL \
W_PWM22_PIN14_DECL \
W_PWM22_PIN15_DECL \
W_PWM22_PIN16_DECL \
W_PWM22_PIN17_DECL \
W_PWM22_PIN18_DECL \
W_PWM22_PIN19_DECL \
W_PWM22_PIN20_DECL \
W_PWM22_PIN21_DECL \
W_PWM22_PIN22_DECL \
W_PWM22_PIN23_DECL \
W_PWM22_PIN24_DECL \
W_PWM22_PIN25_DECL \
W_PWM22_PIN26_DECL \
W_PWM22_PIN27_DECL \
W_PWM22_PIN28_DECL \
W_PWM22_PIN29_DECL \
W_PWM22_PIN30_DECL \
W_PWM22_PIN31_DECL \
W_PWM23_PIN0_DECL \
W_PWM23_PIN1_DECL \
W_PWM23_PIN2_DECL \
W_PWM23_PIN3_DECL \
W_PWM23_PIN4_DECL \
W_PWM23_PIN5_DECL \
W_PWM23_PIN6_DECL \
W_PWM23_PIN7_DECL \
W_PWM23_PIN8_DECL \
W_PWM23_PIN9_DECL \
W_PWM23_PIN10_DECL \
W_PWM23_PIN11_DECL \
W_PWM23_PIN12_DECL \
W_PWM23_PIN13_DECL \
W_PWM23_PIN14_DECL \
W_PWM23_PIN15_DECL \
W_PWM23_PIN16_DECL \
W_PWM23_PIN17_DECL \
W_PWM23_PIN18_DECL \
W_PWM23_PIN19_DECL \
W_PWM23_PIN20_DECL \
W_PWM23_PIN21_DECL \
W_PWM23_PIN22_DECL \
W_PWM23_PIN23_DECL \
W_PWM23_PIN24_DECL \
W_PWM23_PIN25_DECL \
W_PWM23_PIN26_DECL \
W_PWM23_PIN27_DECL \
W_PWM23_PIN28_DECL \
W_PWM23_PIN29_DECL \
W_PWM23_PIN30_DECL \
W_PWM23_PIN31_DECL \
W_PWM24_PIN0_DECL \
W_PWM24_PIN1_DECL \
W_PWM24_PIN2_DECL \
W_PWM24_PIN3_DECL \
W_PWM24_PIN4_DECL \
W_PWM24_PIN5_DECL \
W_PWM24_PIN6_DECL \
W_PWM24_PIN7_DECL \
W_PWM24_PIN8_DECL \
W_PWM24_PIN9_DECL \
W_PWM24_PIN10_DECL \
W_PWM24_PIN11_DECL \
W_PWM24_PIN12_DECL \
W_PWM24_PIN13_DECL \
W_PWM24_PIN14_DECL \
W_PWM24_PIN15_DECL \
W_PWM24_PIN16_DECL \
W_PWM24_PIN17_DECL \
W_PWM24_PIN18_DECL \
W_PWM24_PIN19_DECL \
W_PWM24_PIN20_DECL \
W_PWM24_PIN21_DECL \
W_PWM24_PIN22_DECL \
W_PWM24_PIN23_DECL \
W_PWM24_PIN24_DECL \
W_PWM24_PIN25_DECL \
W_PWM24_PIN26_DECL \
W_PWM24_PIN27_DECL \
W_PWM24_PIN28_DECL \
W_PWM24_PIN29_DECL \
W_PWM24_PIN30_DECL \
W_PWM24_PIN31_DECL \
W_PWM25_PIN0_DECL \
W_PWM25_PIN1_DECL \
W_PWM25_PIN2_DECL \
W_PWM25_PIN3_DECL \
W_PWM25_PIN4_DECL \
W_PWM25_PIN5_DECL \
W_PWM25_PIN6_DECL \
W_PWM25_PIN7_DECL \
W_PWM25_PIN8_DECL \
W_PWM25_PIN9_DECL \
W_PWM25_PIN10_DECL \
W_PWM25_PIN11_DECL \
W_PWM25_PIN12_DECL \
W_PWM25_PIN13_DECL \
W_PWM25_PIN14_DECL \
W_PWM25_PIN15_DECL \
W_PWM25_PIN16_DECL \
W_PWM25_PIN17_DECL \
W_PWM25_PIN18_DECL \
W_PWM25_PIN19_DECL \
W_PWM25_PIN20_DECL \
W_PWM25_PIN21_DECL \
W_PWM25_PIN22_DECL \
W_PWM25_PIN23_DECL \
W_PWM25_PIN24_DECL \
W_PWM25_PIN25_DECL \
W_PWM25_PIN26_DECL \
W_PWM25_PIN27_DECL \
W_PWM25_PIN28_DECL \
W_PWM25_PIN29_DECL \
W_PWM25_PIN30_DECL \
W_PWM25_PIN31_DECL \
W_PWM26_PIN0_DECL \
W_PWM26_PIN1_DECL \
W_PWM26_PIN2_DECL \
W_PWM26_PIN3_DECL \
W_PWM26_PIN4_DECL \
W_PWM26_PIN5_DECL \
W_PWM26_PIN6_DECL \
W_PWM26_PIN7_DECL \
W_PWM26_PIN8_DECL \
W_PWM26_PIN9_DECL \
W_PWM26_PIN10_DECL \
W_PWM26_PIN11_DECL \
W_PWM26_PIN12_DECL \
W_PWM26_PIN13_DECL \
W_PWM26_PIN14_DECL \
W_PWM26_PIN15_DECL \
W_PWM26_PIN16_DECL \
W_PWM26_PIN17_DECL \
W_PWM26_PIN18_DECL \
W_PWM26_PIN19_DECL \
W_PWM26_PIN20_DECL \
W_PWM26_PIN21_DECL \
W_PWM26_PIN22_DECL \
W_PWM26_PIN23_DECL \
W_PWM26_PIN24_DECL \
W_PWM26_PIN25_DECL \
W_PWM26_PIN26_DECL \
W_PWM26_PIN27_DECL \
W_PWM26_PIN28_DECL \
W_PWM26_PIN29_DECL \
W_PWM26_PIN30_DECL \
W_PWM26_PIN31_DECL \
W_PWM27_PIN0_DECL \
W_PWM27_PIN1_DECL \
W_PWM27_PIN2_DECL \
W_PWM27_PIN3_DECL \
W_PWM27_PIN4_DECL \
W_PWM27_PIN5_DECL \
W_PWM27_PIN6_DECL \
W_PWM27_PIN7_DECL \
W_PWM27_PIN8_DECL \
W_PWM27_PIN9_DECL \
W_PWM27_PIN10_DECL \
W_PWM27_PIN11_DECL \
W_PWM27_PIN12_DECL \
W_PWM27_PIN13_DECL \
W_PWM27_PIN14_DECL \
W_PWM27_PIN15_DECL \
W_PWM27_PIN16_DECL \
W_PWM27_PIN17_DECL \
W_PWM27_PIN18_DECL \
W_PWM27_PIN19_DECL \
W_PWM27_PIN20_DECL \
W_PWM27_PIN21_DECL \
W_PWM27_PIN22_DECL \
W_PWM27_PIN23_DECL \
W_PWM27_PIN24_DECL \
W_PWM27_PIN25_DECL \
W_PWM27_PIN26_DECL \
W_PWM27_PIN27_DECL \
W_PWM27_PIN28_DECL \
W_PWM27_PIN29_DECL \
W_PWM27_PIN30_DECL \
W_PWM27_PIN31_DECL \
W_PWM28_PIN0_DECL \
W_PWM28_PIN1_DECL \
W_PWM28_PIN2_DECL \
W_PWM28_PIN3_DECL \
W_PWM28_PIN4_DECL \
W_PWM28_PIN5_DECL \
W_PWM28_PIN6_DECL \
W_PWM28_PIN7_DECL \
W_PWM28_PIN8_DECL \
W_PWM28_PIN9_DECL \
W_PWM28_PIN10_DECL \
W_PWM28_PIN11_DECL \
W_PWM28_PIN12_DECL \
W_PWM28_PIN13_DECL \
W_PWM28_PIN14_DECL \
W_PWM28_PIN15_DECL \
W_PWM28_PIN16_DECL \
W_PWM28_PIN17_DECL \
W_PWM28_PIN18_DECL \
W_PWM28_PIN19_DECL \
W_PWM28_PIN20_DECL \
W_PWM28_PIN21_DECL \
W_PWM28_PIN22_DECL \
W_PWM28_PIN23_DECL \
W_PWM28_PIN24_DECL \
W_PWM28_PIN25_DECL \
W_PWM28_PIN26_DECL \
W_PWM28_PIN27_DECL \
W_PWM28_PIN28_DECL \
W_PWM28_PIN29_DECL \
W_PWM28_PIN30_DECL \
W_PWM28_PIN31_DECL \
W_PWM29_PIN0_DECL \
W_PWM29_PIN1_DECL \
W_PWM29_PIN2_DECL \
W_PWM29_PIN3_DECL \
W_PWM29_PIN4_DECL \
W_PWM29_PIN5_DECL \
W_PWM29_PIN6_DECL \
W_PWM29_PIN7_DECL \
W_PWM29_PIN8_DECL \
W_PWM29_PIN9_DECL \
W_PWM29_PIN10_DECL \
W_PWM29_PIN11_DECL \
W_PWM29_PIN12_DECL \
W_PWM29_PIN13_DECL \
W_PWM29_PIN14_DECL \
W_PWM29_PIN15_DECL \
W_PWM29_PIN16_DECL \
W_PWM29_PIN17_DECL \
W_PWM29_PIN18_DECL \
W_PWM29_PIN19_DECL \
W_PWM29_PIN20_DECL \
W_PWM29_PIN21_DECL \
W_PWM29_PIN22_DECL \
W_PWM29_PIN23_DECL \
W_PWM29_PIN24_DECL \
W_PWM29_PIN25_DECL \
W_PWM29_PIN26_DECL \
W_PWM29_PIN27_DECL \
W_PWM29_PIN28_DECL \
W_PWM29_PIN29_DECL \
W_PWM29_PIN30_DECL \
W_PWM29_PIN31_DECL \
W_PWM30_PIN0_DECL \
W_PWM30_PIN1_DECL \
W_PWM30_PIN2_DECL \
W_PWM30_PIN3_DECL \
W_PWM30_PIN4_DECL \
W_PWM30_PIN5_DECL \
W_PWM30_PIN6_DECL \
W_PWM30_PIN7_DECL \
W_PWM30_PIN8_DECL \
W_PWM30_PIN9_DECL \
W_PWM30_PIN10_DECL \
W_PWM30_PIN11_DECL \
W_PWM30_PIN12_DECL \
W_PWM30_PIN13_DECL \
W_PWM30_PIN14_DECL \
W_PWM30_PIN15_DECL \
W_PWM30_PIN16_DECL \
W_PWM30_PIN17_DECL \
W_PWM30_PIN18_DECL \
W_PWM30_PIN19_DECL \
W_PWM30_PIN20_DECL \
W_PWM30_PIN21_DECL \
W_PWM30_PIN22_DECL \
W_PWM30_PIN23_DECL \
W_PWM30_PIN24_DECL \
W_PWM30_PIN25_DECL \
W_PWM30_PIN26_DECL \
W_PWM30_PIN27_DECL \
W_PWM30_PIN28_DECL \
W_PWM30_PIN29_DECL \
W_PWM30_PIN30_DECL \
W_PWM30_PIN31_DECL \
W_PWM31_PIN0_DECL \
W_PWM31_PIN1_DECL \
W_PWM31_PIN2_DECL \
W_PWM31_PIN3_DECL \
W_PWM31_PIN4_DECL \
W_PWM31_PIN5_DECL \
W_PWM31_PIN6_DECL \
W_PWM31_PIN7_DECL \
W_PWM31_PIN8_DECL \
W_PWM31_PIN9_DECL \
W_PWM31_PIN10_DECL \
W_PWM31_PIN11_DECL \
W_PWM31_PIN12_DECL \
W_PWM31_PIN13_DECL \
W_PWM31_PIN14_DECL \
W_PWM31_PIN15_DECL \
W_PWM31_PIN16_DECL \
W_PWM31_PIN17_DECL \
W_PWM31_PIN18_DECL \
W_PWM31_PIN19_DECL \
W_PWM31_PIN20_DECL \
W_PWM31_PIN21_DECL \
W_PWM31_PIN22_DECL \
W_PWM31_PIN23_DECL \
W_PWM31_PIN24_DECL \
W_PWM31_PIN25_DECL \
W_PWM31_PIN26_DECL \
W_PWM31_PIN27_DECL \
W_PWM31_PIN28_DECL \
W_PWM31_PIN29_DECL \
W_PWM31_PIN30_DECL \
W_PWM31_PIN31_DECL \
}
#endif

#ifdef __cplusplus
} // extern "C"
#endif

/* END GENERATED SECTION */

#if 0
COMMENTOUT
#endif
