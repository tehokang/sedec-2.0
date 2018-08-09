#include "base/macro.h"
#include "base/bit_readwriter.h"

#include "dvb/descriptor_factory.h"
#include "dvb/descriptors/descriptor.h"
#include "dvb/descriptors/application_descriptor.h"
#include "dvb/descriptors/application_name_descriptor.h"
#include "dvb/descriptors/application_usage_descriptor.h"
#include "dvb/descriptors/application_recording_descriptor.h"
#include "dvb/descriptors/simple_application_location_descriptor.h"
#include "dvb/descriptors/simple_application_boundary_descriptor.h"
#include "dvb/descriptors/transport_protocol_descriptor.h"
#include "dvb/descriptors/parental_rating_descriptor.h"
#include "dvb/descriptors/connection_requirement_descriptor.h"

namespace sedec
{

namespace dvb
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
        default:
            return new UnknownDescriptor(rw);
    }
}

} // end of dvb namespace

} // end of sedec namespace
