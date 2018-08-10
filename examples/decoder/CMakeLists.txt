cmake_minimum_required(VERSION 2.8)

#=====================================================================================
# Version
#=====================================================================================

#=====================================================================================
# Build Options
#=====================================================================================

#=====================================================================================
# Sub directories
#=====================================================================================
include_directories(
  ${CMAKE_SOURCE_DIR}/src
)

link_directories(
  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")
set(CMAKE_C_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -O2")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")

#=======================================================================================
# Build sources
#=======================================================================================

add_executable(sedec-dvb-decoder dvb-decoder.cc)
target_link_libraries(sedec-dvb-decoder
  sedec-base
  sedec-dvb
)

add_executable(sedec-hybridcast-decoder hybridcast-decoder.cc)
target_link_libraries(sedec-hybridcast-decoder
  sedec-base
  sedec-hybridcast
)

add_executable(sedec-mpegh-decoder mpegh-decoder.cc)
target_link_libraries(sedec-mpegh-decoder
  sedec-base
  sedec-mpegh
)

#=====================================================================================
# Install
#=====================================================================================
