cmake_minimum_required(VERSION 2.8)

project(sedec)

#=====================================================================================
# Version
#=====================================================================================
set(VERSION_MAJOR "2")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

#=====================================================================================
# Build Options
#=====================================================================================
message(STATUS "CMAKE_TOOLCHAIN_FILE='${CMAKE_TOOLCHAIN_FILE}'")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/out/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/out/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/out/lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -Wno-c++1z-extensions")
#=====================================================================================
# Sub directories
#=====================================================================================
add_subdirectory(${CMAKE_SOURCE_DIR}/src/base)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/dvb)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/arib)

add_subdirectory(${CMAKE_SOURCE_DIR}/examples/decoder)
# add_subdirectory(${CMAKE_SOURCE_DIR}/examples/encoder)
# add_subdirectory(${CMAKE_SOURCE_DIR}/examples/transcoder)

#=======================================================================================
# Build sources
#=======================================================================================
if (APPLE)
  message("You're building on MACOSX")
endif()

#=====================================================================================
# Install
#=====================================================================================
install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/src/base
  DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/include
  FILES_MATCHING PATTERN "*.h"
)

install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/src/dvb
  DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/include
  FILES_MATCHING PATTERN "*.h"
)

install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/src/arib
  DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/include
  FILES_MATCHING PATTERN "*.h"
)
