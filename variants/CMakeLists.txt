if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${BOARD})
  add_subdirectory(${BOARD})
endif()
