#if !defined __DVB_DESCRIPTOR_FACTORY_H__
#define __DVB_DESCRIPTOR_FACTORY_H__

#include "base/bit_readwriter.h"
#include "descriptors/descriptor.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace dvb
{
/**
    @addtogroup dvb
    @{
*/
class DescriptorFactory
{
public:
    static Descriptor* CreateDescriptor(base::BitReadWriter *rw);

    enum DescriptorTag
    {
        APPLICATION_DESCRIPTOR = 0x00,
        APPLICATION_NAME_DESCRIPTOR = 0x01,
        TRANSPORT_PROTOCOL_DESCRIPTOR = 0x02,
        APPLICATION_RECORDING_DESCRIPTOR = 0x06,
        SIMPLE_APPLICATION_LOCATION_DESCRIPTOR = 0x15,
        APPLICATION_USAGE_DESCRIPTOR = 0x16,
        SIMPLE_APPLICATION_BOUNDARY_DESCRIPTOR = 0x17,
        PARENTAL_RATING_DESCRIPTOR = 0x55,
        CONNECTION_REQUIREMENT_DESCRIPTOR = 0x72,
        UNKNOWN_DESCRIPTOR = 0xff,
    };

private:
    DescriptorFactory(){};
    virtual ~DescriptorFactory(){};
};

/** @} */

} // end of dvb namespace

/** @} */

} // end of sedec namespace
#endif
