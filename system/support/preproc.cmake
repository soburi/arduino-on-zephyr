cmake_minimum_required(VERSION 3.0.2)

set(preproc_dir ${ARDUINO_BUILD_PATH}/preproc)

file(COPY ${ARDUINO_VARIANT_PATH}/prj.conf DESTINATION ${ARDUINO_BUILD_PATH}/preproc/_cmakefile )

if(EXISTS ${preproc_dir}/zephyr/ )
  execute_process(
    COMMAND  python3   $ENV{ZEPHYR_BASE}/scripts/subfolder_list.py
    --directory        $ENV{ZEPHYR_BASE}/include
    --out-file         ${preproc_dir}/zephyr/misc/generated/syscalls_subdirs.txt
    --trigger          ${preproc_dir}/zephyr/misc/generated/syscalls_subdirs.trigger
    --create-links     ${preproc_dir}/zephyr/misc/generated/syscalls_links
  )
endif()

if(EXISTS ${ARDUINO_BUILD_PATH}/preproc/_cmakefile/.NOT_CHANGED )
  file(REMOVE ${ARDUINO_BUILD_PATH}/preproc/_cmakefile/.NOT_CHANGED )
else()
  if(NOT EXISTS ${ARDUINO_BUILD_PATH}/preproc/preproc.sh )
    execute_process(
      COMMAND ${CMAKE_COMMAND} -GNinja -DBOARD=${BOARD} _cmakefile
      WORKING_DIRECTORY ${preproc_dir}
      OUTPUT_QUIET
      ERROR_QUIET
    )

    execute_process(
      COMMAND ${CMAKE_COMMAND} --build ${preproc_dir} -- zephyr/linker.cmd
      WORKING_DIRECTORY ${preproc_dir}
      OUTPUT_QUIET
      ERROR_QUIET
    )
  endif()
endif()

set(run_preproc_script bash ${ARDUINO_BUILD_PATH}/preproc/preproc.sh)

if(NOT WIN32)
  if(${ARDUINO_PREPROC_TARGET} STREQUAL "nul")
    message(STATUS ARDUINO_PREPROC_TARGET=nul)
    set(ARDUINO_PREPROC_TARGET /dev/null)
  endif()
endif()

execute_process(
  COMMAND ${run_preproc_script} ${ARDUINO_PREPROC_SOURCE} ${ARDUINO_PREPROC_TARGET}
  WORKING_DIRECTORY ${preproc_dir}
  RESULT_VARIABLE retcode
)

if(${retcode})
  message(FATAL_ERROR)
endif()

