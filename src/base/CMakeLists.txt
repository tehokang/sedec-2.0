cmake_minimum_required(VERSION 2.8)

set(MODULE_NAME sedec-base)
#=====================================================================================
# Version
#=====================================================================================
set(VERSION_MAJOR "2")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(TARGET ${MODULE_NAME}-${VERSION})
#=====================================================================================
# Build Options
#=====================================================================================

#=====================================================================================
# Sub directories
#=====================================================================================
include_directories(
  ${CMAKE_SOURCE_DIR}/src/base
)

set(SOURCE_FILES ${SOURCE_FILES}
  bit_readwriter.cc
  descriptor.cc
  table.cc
)

link_directories(

)

#=======================================================================================
# Build sources
#=======================================================================================
add_library(${TARGET} SHARED ${SOURCE_FILES})

if (APPLE) 
add_custom_command(
  TARGET ${TARGET}
  POST_BUILD
  COMMAND ln -sf lib${TARGET}.dylib
      ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib${MODULE_NAME}.dylib
)
elseif (UNIX)
add_custom_command(
  TARGET ${TARGET}
  POST_BUILD
  COMMAND ln -sf lib${TARGET}.so
      ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib${MODULE_NAME}.so
)
endif()

target_link_libraries(${TARGET}

)
#=====================================================================================
# Install
#=====================================================================================
