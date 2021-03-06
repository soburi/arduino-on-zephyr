cmake_minimum_required(VERSION 3.0.2)

file(READ $ENV{ZEPHYR_BASE}/VERSION ver)

string(REGEX MATCH "VERSION_MAJOR = ([0-9]*)" _ ${ver})
set(PROJECT_VERSION_MAJOR ${CMAKE_MATCH_1})
string(REGEX MATCH "VERSION_MINOR = ([0-9]*)" _ ${ver})
set(PROJECT_VERSION_MINOR ${CMAKE_MATCH_1})
string(REGEX MATCH "PATCHLEVEL = ([0-9]*)" _ ${ver})
set(PROJECT_VERSION_PATCH ${CMAKE_MATCH_1})
string(REGEX MATCH "VERSION_TWEAK = ([0-9]*)" _ ${ver})
set(PROJECT_VERSION_TWEAK ${CMAKE_MATCH_1})

# Temporary convenience variable
set(PROJECT_VERSION_WITHOUT_TWEAK ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

if(PROJECT_VERSION_TWEAK)
  set(PROJECT_VERSION ${PROJECT_VERSION_WITHOUT_TWEAK}.${PROJECT_VERSION_TWEAK})
else()
  set(PROJECT_VERSION ${PROJECT_VERSION_WITHOUT_TWEAK})
endif()

#message(FATAL_ERROR ${PROJECT_VERSION})

set(BUILD_VERSION "zephyr-v${PROJECT_VERSION}")


if("${ARDUINO_PREPROC_TARGET}" STREQUAL "{preprocessed_file_path}")
  set(build_dir ${ARDUINO_BUILD_PATH})
else()
  set(build_dir ${ARDUINO_BUILD_PATH}/preproc)
endif()

set(conffiles ${ARDUINO_VARIANT_PATH}/prj.conf)
set(extradeps "")

get_cmake_property(_variableNames VARIABLES)
foreach(varname ${_variableNames})
  string(FIND ${varname} OVERLAY_APPEND_ match)
  if(${match} EQUAL 0)
    #message(STATUS "${varname}=${${varname}}")
    list(APPEND conffiles ${${varname}})
  endif()

  string(FIND ${varname} DEPENDENCY_APPEND_ match)
  if(${match} EQUAL 0)
    list(APPEND extradeps ${${varname}})
  endif()
endforeach()
string(JOIN " " conffile_opt ${conffiles})
#message(STATUS "-DCONF_FILE="${conffile_opt})


# restore symlinks
if(EXISTS ${build_dir}/zephyr/ AND NOT WIN32)
  execute_process(
    COMMAND  python3   $ENV{ZEPHYR_BASE}/scripts/subfolder_list.py
    --directory        $ENV{ZEPHYR_BASE}/include
    --out-file         ${build_dir}/zephyr/misc/generated/syscalls_subdirs.txt
    --trigger          ${build_dir}/zephyr/misc/generated/syscalls_subdirs.trigger
    --create-links     ${build_dir}/zephyr/misc/generated/syscalls_links
  )
endif()

if(EXISTS ${build_dir}/build.ninja )
  execute_process(
    COMMAND  python3   ${CMAKE_CURRENT_LIST_DIR}/copy_timestamp.py
    ${build_dir}/build.ninja ${build_dir}/zephyr/misc/generated/syscalls_subdirs.txt
  )
endif()

if(WIN32)
set(run_preproc_script ${ARDUINO_BUILD_PATH}/preproc/preproc.cpp.bat)
else()
set(run_preproc_script bash ${ARDUINO_BUILD_PATH}/preproc/preproc.cpp.sh)
endif()

if(NOT WIN32)
  if(${ARDUINO_PREPROC_TARGET} STREQUAL "nul")
    message(STATUS ARDUINO_PREPROC_TARGET=nul)
    set(ARDUINO_PREPROC_TARGET /dev/null)
  endif()
endif()

message(STATUS "COMMAND ${CMAKE_COMMAND} -GNinja -DARDUINO_BUILD_PATH=${ARDUINO_BUILD_PATH} -DARDUINO_VARIANT_PATH=${ARDUINO_VARIANT_PATH} -DBOARD=${BOARD} -DCONF_FILE=${conffile_opt} -DBUILD_VERSION=${BUILD_VERSION} _cmakefile")

if(EXISTS ${build_dir}/_cmakefile/.NOT_CHANGED )
  file(REMOVE ${build_dir}/_cmakefile/.NOT_CHANGED )
else()
  if("${ARDUINO_PREPROC_TARGET}" STREQUAL "{preprocessed_file_path}")
    execute_process(
      COMMAND ${CMAKE_COMMAND} -GNinja -DARDUINO_BUILD_PATH=${ARDUINO_BUILD_PATH} -DARDUINO_VARIANT_PATH=${ARDUINO_VARIANT_PATH} -DBOARD=${BOARD} -DCONF_FILE=${conffile_opt} -DBUILD_VERSION=${BUILD_VERSION} _cmakefile
      WORKING_DIRECTORY ${build_dir}
    )
  elseif(NOT EXISTS ${ARDUINO_BUILD_PATH}/preproc/preproc.cpp.sh)
    #message(${conffiles})
    execute_process(
      COMMAND ${CMAKE_COMMAND} -GNinja -DARDUINO_BUILD_PATH=${ARDUINO_BUILD_PATH} -DARDUINO_VARIANT_PATH=${ARDUINO_VARIANT_PATH} -DBOARD=${BOARD} -DCONF_FILE=${conffile_opt} -DBUILD_VERSION=${BUILD_VERSION} _cmakefile
      WORKING_DIRECTORY ${build_dir}
      OUTPUT_QUIET
      ERROR_QUIET
    )

    # enforce GENERETE_OUTPUT
    execute_process(
      COMMAND ${CMAKE_COMMAND} --build ${build_dir} -- zephyr/linker.cmd
      WORKING_DIRECTORY ${build_dir}
      OUTPUT_QUIET
      ERROR_QUIET
    )
  endif()
endif()

if("${ARDUINO_PREPROC_TARGET}" STREQUAL "{preprocessed_file_path}")
  execute_process(
    COMMAND ${CMAKE_COMMAND} --build ${build_dir} --
    WORKING_DIRECTORY ${build_dir}
    RESULT_VARIABLE retcode
  )
else()
  execute_process(
    COMMAND ${run_preproc_script} ${ARDUINO_PREPROC_SOURCE} ${ARDUINO_PREPROC_TARGET}
    WORKING_DIRECTORY ${build_dir}
    RESULT_VARIABLE retcode
  )
endif()

# remove symlinks (Prevent system file deletion by cleanup on Arduino IDE exit)
file(GLOB_RECURSE sc_links ${build_dir}/zephyr/misc/generated/syscalls_links/*)
foreach(l ${sc_links})
  if(IS_SYMLINK ${l})
    file(REMOVE ${l})
  endif()
endforeach()


if(${retcode})
  message(FATAL_ERROR)
endif()

