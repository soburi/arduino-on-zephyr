cmake_minimum_required(VERSION 3.0.2)

set(build_dir ${ARDUINO_BUILD_PATH})
set(conffiles ${ARDUINO_VARIANT_PATH}/prj.conf)

get_cmake_property(_variableNames VARIABLES)
foreach(varname ${_variableNames})
  string(FIND ${varname} OVERLAY_APPEND_ match)
  if(${match} EQUAL 0)
    #message(STATUS "${varname}=${${varname}}")
    list(APPEND conffiles ${${varname}})
  endif()
endforeach()
string(JOIN " " conffile_opt ${conffiles})
#message(STATUS "-DCONF_FILE="${conffile_opt})


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
    COMMAND ${CMAKE_COMMAND} -GNinja -DBOARD=${BOARD} -DCONF_FILE=${conffile_opt} _cmakefile
    WORKING_DIRECTORY ${build_dir}
  )
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} --build ${build_dir} --
  WORKING_DIRECTORY ${build_dir}
  RESULT_VARIABLE retcode
)

file(GLOB_RECURSE sc_links ${build_dir}/zephyr/misc/generated/syscalls_links/*)

foreach(l ${sc_links})
  if(IS_SYMLINK ${l})
    file(REMOVE ${l})
  endif()
endforeach()


if(${retcode})
  message(FATAL_ERROR)
endif()

