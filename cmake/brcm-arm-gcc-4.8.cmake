#
# CMake Toolchain file for crosscompiling on ARM.
#
# This can be used when running cmake in the following way:
#  mkdir out
#  cd out/
#  cmake ../ -DCMAKE_TOOLCHAIN_FILE=../cross-stbgcc-4.8-1.0.cmake
#
set(CMAKE_SYSTEM_NAME Linux)

set(CROSS_PATH "/opt/toolchains/stbgcc-4.8-1.6/bin/arm-linux-")
set(SYSROOT "/opt/toolchains/stbgcc-4.8-1.6/arm-linux-gnueabihf/sys-root")

set(CMAKE_C_COMPILER "${CROSS_PATH}gcc")
set(CMAKE_CXX_COMPILER "${CROSS_PATH}g++")
set(CMAKE_LINKER "${CROSS_PATH}ld")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --sysroot=${SYSROOT}" CACHE INTERNAL "" FORCE)
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} --sysroot=${SYSROOT}" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --sysroot=${SYSROOT}" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} --sysroot=${SYSROOT}" CACHE INTERNAL "" FORCE)

set(TARGET_PLATFORM "brcm-arm")