cmake_minimum_required(VERSION 3.0.2)

set(preproc_dir ${ARDUINO_BUILD_PATH}/preproc)

file(COPY ${ARDUINO_VARIANT_PATH}/prj.conf DESTINATION ${ARDUINO_BUILD_PATH}/preproc/_cmakefile )

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

set(run_preproc_script sh preproc.sh)

execute_process(
  COMMAND ${run_preproc_script} ${ARDUINO_PREPROC_SOURCE} ${ARDUINO_PREPROC_TARGET}
  WORKING_DIRECTORY ${preproc_dir}
  RESULT_VARIABLE retcode
)

if(${retcode})
  message(FATAL_ERROR)
endif()

