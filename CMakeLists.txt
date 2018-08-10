cmake_minimum_required(VERSION 2.8)

project(sedec)

#=====================================================================================
# Version
#=====================================================================================
set(VERSION_MAJOR "2")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

if ( ${TARGET_PLATFORM} MATCHES "arm" )

elseif ( ${TARGET_PLATFORM} MATCHES "x86" )

endif()

#=====================================================================================
# Build Options
#=====================================================================================
message(STATUS "CMAKE_TOOLCHAIN_FILE='${CMAKE_TOOLCHAIN_FILE}'")

# Temporary for Debug or Do comment or make param via CLI
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
#=====================================================================================
# Sub directories
#=====================================================================================
add_subdirectory(${CMAKE_SOURCE_DIR}/src/base)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/dvb)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/hybridcast)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/mpegh)

add_subdirectory(${CMAKE_SOURCE_DIR}/examples/decoder)
# add_subdirectory(${CMAKE_SOURCE_DIR}/examples/encoder)
# add_subdirectory(${CMAKE_SOURCE_DIR}/examples/transcoder)

#=======================================================================================
# Build sources
#=======================================================================================


#=====================================================================================
# Install
#=====================================================================================
# file( GLOB_RECURSE LIBUSB_LIB_FILES ${LIBUSB_LIB}/libusb*.so* )
# file(INSTALL ${LIBUSB_LIB_FILES} DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )

# file( GLOB_RECURSE MYSPIN_LIB_FILES ${MYSPIN_LIB}/libmySPIN*.so* )
# file(INSTALL ${MYSPIN_LIB_FILES} DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )
