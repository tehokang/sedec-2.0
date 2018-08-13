cmake_minimum_required(VERSION 2.8)

set(MODULE_NAME sedec-hybridcast)
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
  ${CMAKE_SOURCE_DIR}/src/hybridcast
)

set(SOURCE_FILES ${SOURCE_FILES}
  section_factory.cc
  descriptor_factory.cc

  descriptors/application_boundary_and_permission_descriptor.cc
  descriptors/application_descriptor.cc
  descriptors/application_name_descriptor.cc
  descriptors/application_recording_descriptor.cc
  descriptors/application_usage_descriptor.cc
  descriptors/application.cc
  descriptors/autostart_priority_descriptor.cc
  descriptors/cache_control_info_descriptor.cc
  descriptors/connection_requirement_descriptor.cc
  descriptors/descriptor.cc
  descriptors/parental_rating_descriptor.cc
  descriptors/randomized_latency_descriptor.cc
  descriptors/simple_application_boundary_descriptor.cc
  descriptors/simple_application_location_descriptor.cc
  descriptors/transport_protocol_descriptor.cc

  sections/application_information_table.cc
  sections/application_information_table_transcoder.cc
)

link_directories(
  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

#=======================================================================================
# Build sources
#=======================================================================================
add_library(${TARGET} SHARED ${SOURCE_FILES})
add_custom_command(
  TARGET ${TARGET}
  POST_BUILD
  COMMAND ln -sf lib${TARGET}.so
      ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib${MODULE_NAME}.so
)

target_link_libraries(${TARGET}
  sedec-base
)
#=====================================================================================
# Install
#=====================================================================================