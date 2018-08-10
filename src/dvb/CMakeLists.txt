cmake_minimum_required(VERSION 2.8)

set(MODULE_NAME sedec-dvb)
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

#=====================================================================================
# Sub directories
#=====================================================================================
set(INCPATHS
    ${CMAKE_SOURCE_DIR}/src/
    ${CMAKE_SOURCE_DIR}/src/dvb/
)

include_directories(
    ${INCPATHS}
)

set(SOURCE_FILES ${SOURCE_FILES}
  section_factory.cc
  descriptor_factory.cc

  descriptors/application_descriptor.cc
  descriptors/application_name_descriptor.cc
  descriptors/application_recording_descriptor.cc
  descriptors/application_usage_descriptor.cc
  descriptors/application.cc
  descriptors/connection_requirement_descriptor.cc
  descriptors/descriptor.cc
  descriptors/parental_rating_descriptor.cc
  descriptors/simple_application_boundary_descriptor.cc
  descriptors/simple_application_location_descriptor.cc
  descriptors/transport_protocol_descriptor.cc

  sections/application_information_table.cc
  sections/application_information_table_transcoder.cc
)

link_directories(

)

#=======================================================================================
# Build sources
#=======================================================================================
add_library(${MODULE_NAME}-${VERSION} SHARED ${SOURCE_FILES})

target_link_libraries(${MODULE_NAME}

)
#=====================================================================================
# Install
#=====================================================================================