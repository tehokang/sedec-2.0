cmake_minimum_required(VERSION 2.8)

set(MODULE_NAME sedec-dvb)
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
  ${CMAKE_SOURCE_DIR}/src/dvb/
)

set(SOURCE_FILES ${SOURCE_FILES}
  table_factory.cc
  descriptor_factory.cc

  descriptors/application_descriptor.cc
  descriptors/application_name_descriptor.cc
  descriptors/application_recording_descriptor.cc
  descriptors/application_usage_descriptor.cc
  descriptors/application.cc
  descriptors/connection_requirement_descriptor.cc
  descriptors/parental_rating_descriptor.cc
  descriptors/simple_application_boundary_descriptor.cc
  descriptors/simple_application_location_descriptor.cc
  descriptors/transport_protocol_descriptor.cc
  descriptors/descriptor.cc

  tables/application_information_table.cc
  tables/application_information_table_transcoder.cc
  tables/program_association_table.cc
  tables/conditional_access_table.cc
  tables/program_map_table.cc
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
