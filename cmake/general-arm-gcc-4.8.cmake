#
# CMake Toolchain file for crosscompiling on ARM.
#
# This can be used when running cmake in the following way:
#  mkdir out
#  cd out/
#  cmake ../ -DCMAKE_TOOLCHAIN_FILE=../cross-stbgcc-4.8-1.0.cmake
#
set(CMAKE_SYSTEM_NAME Linux)

set(CROSS_PATH "")
set(CMAKE_C_COMPILER "${CROSS_PATH}gcc")
set(CMAKE_CXX_COMPILER "${CROSS_PATH}g++")
set(CMAKE_LINKER "${CROSS_PATH}ld")
set(CMAKE_C_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

set(TARGET_PLATFORM "pi-arm")