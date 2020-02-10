# SPDX-License-Identifier: Apache-2.0
zephyr_include_directories(.)

if(NOT DEFINED ARDUINO_BUILD_PATH)

zephyr_sources(HardwareSerial.cpp)
zephyr_sources(IPAddress.cpp)
zephyr_sources(itoa.c)
zephyr_sources(main.cpp)
zephyr_sources(Print.cpp)
zephyr_sources(pulse.c)
zephyr_sources(Stream.cpp)
zephyr_sources(Tone.cpp)
zephyr_sources(UartDevice.cpp)
zephyr_sources(variant_common.cpp)
zephyr_sources(wiring.c)
zephyr_sources(wiring_analog.c)
zephyr_sources(wiring_digital.c)
zephyr_sources(wiring_shift.c)
zephyr_sources(WMath.cpp)
zephyr_sources(WString.cpp)

endif()

