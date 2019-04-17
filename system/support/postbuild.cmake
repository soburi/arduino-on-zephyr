cmake_minimum_required(VERSION 3.0.2)

file(GLOB_RECURSE files ${ARDUINO_BUILD_PATH}/preproc/zephyr/misc/generated/syscalls_links/* ${ARDUINO_BUILD_PATH}/zephyr/misc/generated/syscalls_links/*)

foreach(f ${files})
  if(IS_SYMLINK ${f})
    file(REMOVE ${f})
  endif()
endforeach()
