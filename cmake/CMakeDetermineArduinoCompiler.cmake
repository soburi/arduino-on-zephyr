# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE

set (CMAKE_Arduino_COMPILER_ENV_VAR "ARDUINO_COMPILER")
set (CMAKE_Arduino_COMPILER ${CMAKE_CURRENT_LIST_DIR}/ino.py CACHE FILEPATH "Arduino Compiler")

include (CMakeFindBinUtils)

# Configure the variables in this file for faster reloads
configure_file (${CMAKE_CURRENT_LIST_DIR}/CMakeArduinoCompiler.cmake.in
  ${CMAKE_PLATFORM_INFO_DIR}/CMakeArduinoCompiler.cmake
  @ONLY IMMEDIATE # IMMEDIATE must be here for compatibility mode <= 2.0
)

