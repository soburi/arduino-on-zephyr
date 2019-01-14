cmake_minimum_required(VERSION 3.0.2)

set(build_dir ${ARDUINO_BUILD_PATH})

file(COPY ${ARDUINO_VARIANT_PATH}/prj.conf DESTINATION ${ARDUINO_BUILD_PATH}/_cmakefile )

execute_process(
  COMMAND ${CMAKE_COMMAND} -GNinja -DBOARD=${BOARD} _cmakefile
  WORKING_DIRECTORY ${build_dir}
)

execute_process(
  COMMAND ${CMAKE_COMMAND} --build ${build_dir} -- 
  WORKING_DIRECTORY ${build_dir}
  RESULT_VARIABLE retcode
)

if(${retcode})
  message(FATAL_ERROR)
endif()

