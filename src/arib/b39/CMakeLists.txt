cmake_minimum_required(VERSION 2.8)

set(MODULE_NAME sedec-arib-b39)
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
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/arib/b39
)

set(SOURCE_FILES ${SOURCE_FILES}
  descriptors/application_boundary_and_permission_descriptor.cc
  descriptors/application_descriptor.cc
  descriptors/application.cc
  descriptors/autostart_priority_descriptor.cc
  descriptors/cache_control_info_descriptor.cc
  descriptors/descriptor.cc
  descriptors/randomized_latency_descriptor.cc
  descriptors/simple_application_location_descriptor.cc
  descriptors/transport_protocol_descriptor.cc
  descriptors/compression_type_descriptor.cc
  descriptors/expire_descriptor.cc
  descriptors/info_descriptor.cc
  descriptors/linked_pu_descriptor.cc
  descriptors/locked_cache_descriptor.cc
  descriptors/type_descriptor.cc
  descriptors/unlocked_cache_descriptor.cc
  tables/application_information_table.cc
  table_factory.cc
  descriptor_factory.cc
)

link_directories(
  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
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
  sedec-base
)
#=====================================================================================
# Install
#=====================================================================================
