cmake_minimum_required(VERSION 3.0.2)

set(build_dir ${ARDUINO_BUILD_PATH})

file(COPY ${ARDUINO_VARIANT_PATH}/prj.conf DESTINATION ${ARDUINO_BUILD_PATH}/_cmakefile )

if(EXISTS ${build_dir}/zephyr/ )
  execute_process(
    COMMAND  python3   $ENV{ZEPHYR_BASE}/scripts/subfolder_list.py
    --directory        $ENV{ZEPHYR_BASE}/include
    --out-file         ${build_dir}/zephyr/misc/generated/syscalls_subdirs.txt
    --trigger          ${build_dir}/zephyr/misc/generated/syscalls_subdirs.trigger
    --create-links     ${build_dir}/zephyr/misc/generated/syscalls_links
  )
endif()

if(EXISTS ${ARDUINO_BUILD_PATH}/_cmakefile/.NOT_CHANGED )
  file(REMOVE ${ARDUINO_BUILD_PATH}/_cmakefile/.NOT_CHANGED )
else()
  execute_process(
    COMMAND ${CMAKE_COMMAND} -GNinja -DBOARD=${BOARD} _cmakefile
    WORKING_DIRECTORY ${build_dir}
  )
endif()

  execute_process(
    COMMAND ${CMAKE_COMMAND} --build ${build_dir} --
    WORKING_DIRECTORY ${build_dir}
    RESULT_VARIABLE retcode
  )

if(${retcode})
  message(FATAL_ERROR)
endif()

