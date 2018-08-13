#include "base/macro.h"
#include "descriptor_factory.h"
#include "descriptors/descriptor.h"
#include "descriptors/application_descriptor.h"
#include "descriptors/simple_application_location_descriptor.h"
#include "descriptors/transport_protocol_descriptor.h"

#include "descriptors/application_boundary_and_permission_descriptor.h"
#include "descriptors/autostart_priority_descriptor.h"
#include "descriptors/cache_control_info_descriptor.h"
#include "descriptors/randomized_latency_descriptor.h"

namespace sedec
{

namespace mpegh
{

Descriptor* DescriptorFactory::CreateDescriptor(base::BitReadWriter *rw)
{
    int descriptor_tag = ((*(rw->GetCurrentBuffer()) << 8) &0xff00);
    descriptor_tag |= *(rw->GetCurrentBuffer()+1);

    switch(descriptor_tag)
    {
        /**
         * @note It is related in ARIB STD-B60 version 1.2
         **/
        case APPLICATION_DESCRIPTOR:
            return new ApplicationDescriptor(rw);
        case SIMPLE_APPLICATION_LOCATION_DESCRIPTOR:
            return new SimpleApplicationLocationDescriptor(rw);
        case TRANSPORT_PROTOCOL_DESCRIPTOR:
            return new TransportProtocolDescriptor(rw);
        case APPLICATION_BOUNDARY_AND_PERMISSION_DESCRIPTOR:
            return new ApplicationBoundaryAndPermissionDescriptor(rw);
        case AUTOSTART_PRIORITY_DESCRIPTOR:
            return new AutostartPriorityDescriptor(rw);
        case CACHE_CONTROL_INFO_DESCRIPTOR:
            return new CacheControlInfoDescriptor(rw);
        case RANDOMIZED_LATENCY_DESCRIPTOR:
            return new RandomizedLatencyDescriptor(rw);
        default:
            return new UnknownDescriptor(rw);
    }
}

} // end of mh namespace

} // end of sedec namespace
