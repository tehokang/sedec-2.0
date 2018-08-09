// descriptor_factory.cpp: implementation of the DescriptorFactory class.
//
//////////////////////////////////////////////////////////////////////
#include "section_common.h"
#include "descriptors/hybridcast/descriptor_factory.h"
#include "bit_readwriter.h"
#include "descriptors/hybridcast/descriptor.h"
#include "descriptors/hybridcast/application_descriptor.h"
#include "descriptors/hybridcast/application_name_descriptor.h"
#include "descriptors/hybridcast/application_usage_descriptor.h"
#include "descriptors/hybridcast/application_recording_descriptor.h"
#include "descriptors/hybridcast/simple_application_location_descriptor.h"
#include "descriptors/hybridcast/simple_application_boundary_descriptor.h"
#include "descriptors/hybridcast/transport_protocol_descriptor.h"
#include "descriptors/hybridcast/parental_rating_descriptor.h"
#include "descriptors/hybridcast/connection_requirement_descriptor.h"

#include "descriptors/hybridcast/application_boundary_and_permission_descriptor.h"
#include "descriptors/hybridcast/autostart_priority_descriptor.h"
#include "descriptors/hybridcast/cache_control_info_descriptor.h"
#include "descriptors/hybridcast/randomized_latency_descriptor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace sedec
{

namespace hybridcast
{

Descriptor* DescriptorFactory::CreateDescriptor(BitReadWriter *rw)
{
    int descriptor_tag = (*(rw->GetCurrentBuffer()) & 0xff);

    switch(descriptor_tag)
    {
        /**
         * @note It is related in ETSI TS 102 809 v1.4.1
         **/
        case Descriptor::APPLICATION_DESCRIPTOR:
            return new ApplicationDescriptor(rw);
        case Descriptor::APPLICATION_NAME_DESCRIPTOR:
            return new ApplicationNameDescriptor(rw);
        case Descriptor::APPLICATION_USAGE_DESCRIPTOR:
            return new ApplicationUsageDescriptor(rw);
        case Descriptor::APPLICATION_RECORDING_DESCRIPTOR:
       	    return new ApplicationRecordingDescriptor(rw);
        case Descriptor::SIMPLE_APPLICATION_LOCATION_DESCRIPTOR:
            return new SimpleApplicationLocationDescriptor(rw);
        case Descriptor::SIMPLE_APPLICATION_BOUNDARY_DESCRIPTOR:
            return new SimpleApplicationBoundaryDescriptor(rw);
        case Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR:
            return new TransportProtocolDescriptor(rw);
        case Descriptor::PARENTAL_RATING_DESCRIPTOR:
       	    return new ParentalRatingDescriptor(rw);
        case Descriptor::CONNECTION_REQUIREMENT_DESCRIPTOR:
            return new ConnectionRequirementDescriptor(rw);

        /**
         * @note It is related in IPTVFJ STD-0010 version 2.0
         **/
        case Descriptor::APPLICATION_BOUNDARY_AND_PERMISSION_DESCRIPTOR:
            return new ApplicationBoundaryAndPermissionDescriptor(rw);
        case Descriptor::AUTOSTART_PRIORITY_DESCRIPTOR:
            return new AutostartPriorityDescriptor(rw);
        case Descriptor::CACHE_CONTROL_INFO_DESCRIPTOR:
            return new CacheControlInfoDescriptor(rw);
        case Descriptor::RANDOMIZED_LATENCY_DESCRIPTOR:
            return new RandomizedLatencyDescriptor(rw);

        default:
            return new UnknownDescriptor(rw);
    }
}

} // end of hybridcast namespace

} // end of sedec namespace
