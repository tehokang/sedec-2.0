cmake_minimum_required(VERSION 2.8)

project(sedec)

#=====================================================================================
# Version
#=====================================================================================
set(VERSION_MAJOR "2")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION "${SDK_VERSION_MAJOR}.${SDK_VERSION_MINOR}.${SDK_VERSION_PATCH}")

if ( ${TARGET_PLATFORM} MATCHES "arm" )
set (LIBUSB_LIB
  ${CMAKE_SOURCE_DIR}/3rdparty/libusb/1.0/pi3/32bit/lib
)
set (MYSPIN_LIB
  ${CMAKE_SOURCE_DIR}/3rdparty/myspin/1.2.3/arm/32bit/debug/lib
)

elseif ( ${TARGET_PLATFORM} MATCHES "tcc-arm" )
set (LIBUSB_LIB
  ${CMAKE_SOURCE_DIR}/3rdparty/libusb/1.0/tcc/lib
)
set (MYSPIN_LIB
  ${CMAKE_SOURCE_DIR}/3rdparty/myspin/1.2.3/tcc/32bit/debug/lib
)

elseif ( ${TARGET_PLATFORM} MATCHES "brcm-arm" )
set (LIBUSB_LIB
  ${CMAKE_SOURCE_DIR}/3rdparty/libusb/1.0/x86/64bit/lib
)
endif()

#=====================================================================================
# Build Options
#=====================================================================================
message(STATUS "CMAKE_TOOLCHAIN_FILE='${CMAKE_TOOLCHAIN_FILE}'")

# Temporary for Debug or Do comment or make param via CLI
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/out/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/out/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/out/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(BIUILD_SRC_DIR ${CMAKE_SOURCE_DIR}/build/src)

#=====================================================================================
# Sub directories
#=====================================================================================
add_subdirectory(${CMAKE_SOURCE_DIR}/src/utility)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/transport-adapter)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/projection-handler)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/export)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/examples)

#=======================================================================================
# Build sources
#=======================================================================================


#=====================================================================================
# Install
#=====================================================================================
file( GLOB_RECURSE LIBUSB_LIB_FILES ${LIBUSB_LIB}/libusb*.so* )
file(INSTALL ${LIBUSB_LIB_FILES} DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )

file( GLOB_RECURSE MYSPIN_LIB_FILES ${MYSPIN_LIB}/libmySPIN*.so* )
file(INSTALL ${MYSPIN_LIB_FILES} DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )
