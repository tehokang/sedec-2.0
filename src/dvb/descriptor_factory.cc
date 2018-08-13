#include "base/macro.h"
#include "base/descriptor.h"

#include "descriptor_factory.h"
#include "descriptors/application_descriptor.h"
#include "descriptors/application_name_descriptor.h"
#include "descriptors/application_usage_descriptor.h"
#include "descriptors/application_recording_descriptor.h"
#include "descriptors/simple_application_location_descriptor.h"
#include "descriptors/simple_application_boundary_descriptor.h"
#include "descriptors/transport_protocol_descriptor.h"
#include "descriptors/parental_rating_descriptor.h"
#include "descriptors/connection_requirement_descriptor.h"

namespace sedec
{

namespace dvb
{

Descriptor* DescriptorFactory::CreateDescriptor(base::BitReadWriter *rw)
{
    int descriptor_tag = (*(rw->GetCurrentBuffer()) & 0xff);

    switch(descriptor_tag)
    {
        /**
         * @note It is related in ETSI TS 102 809 v1.4.1
         **/
        case APPLICATION_DESCRIPTOR:
            return new ApplicationDescriptor(rw);
        case APPLICATION_NAME_DESCRIPTOR:
            return new ApplicationNameDescriptor(rw);
        case APPLICATION_USAGE_DESCRIPTOR:
            return new ApplicationUsageDescriptor(rw);
        case APPLICATION_RECORDING_DESCRIPTOR:
       	    return new ApplicationRecordingDescriptor(rw);
        case SIMPLE_APPLICATION_LOCATION_DESCRIPTOR:
            return new SimpleApplicationLocationDescriptor(rw);
        case SIMPLE_APPLICATION_BOUNDARY_DESCRIPTOR:
            return new SimpleApplicationBoundaryDescriptor(rw);
        case TRANSPORT_PROTOCOL_DESCRIPTOR:
            return new TransportProtocolDescriptor(rw);
        case PARENTAL_RATING_DESCRIPTOR:
       	    return new ParentalRatingDescriptor(rw);
        case CONNECTION_REQUIREMENT_DESCRIPTOR:
            return new ConnectionRequirementDescriptor(rw);
        default:
            return new UnknownDescriptor(rw);
    }
}

} // end of dvb namespace

} // end of sedec namespace
