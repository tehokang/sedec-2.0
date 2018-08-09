// descriptor_factory.cpp: implementation of the DescriptorFactory class.
//
//////////////////////////////////////////////////////////////////////
#include "section_common.h"
#include "descriptors/mh/descriptor_factory.h"
#include "bit_readwriter.h"
#include "descriptors/mh/descriptor.h"
#include "descriptors/mh/application_descriptor.h"
#include "descriptors/mh/simple_application_location_descriptor.h"
#include "descriptors/mh/transport_protocol_descriptor.h"

#include "descriptors/mh/application_boundary_and_permission_descriptor.h"
#include "descriptors/mh/autostart_priority_descriptor.h"
#include "descriptors/mh/cache_control_info_descriptor.h"
#include "descriptors/mh/randomized_latency_descriptor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace sedec
{

namespace mh
{

Descriptor* DescriptorFactory::CreateDescriptor(BitReadWriter *rw)
{
    int descriptor_tag = ((*(rw->GetCurrentBuffer()) << 8) &0xff00);
    descriptor_tag |= *(rw->GetCurrentBuffer()+1);
    
    switch(descriptor_tag)
    {
        /**
         * @note It is related in ARIB STD-B60 version 1.2
         **/
        case Descriptor::APPLICATION_DESCRIPTOR:
            return new ApplicationDescriptor(rw);
        case Descriptor::SIMPLE_APPLICATION_LOCATION_DESCRIPTOR:
            return new SimpleApplicationLocationDescriptor(rw);
        case Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR:
            return new TransportProtocolDescriptor(rw);
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

} // end of mh namespace

} // end of sedec namespace
