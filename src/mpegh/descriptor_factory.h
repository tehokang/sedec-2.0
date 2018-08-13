#if !defined __MH_DESCRIPTOR_FACTORY_H__
#define __MH_DESCRIPTOR_FACTORY_H__

#include "base/bit_readwriter.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace mpegh
{
/**
    @addtogroup mpegh
    @{
*/
class Descriptor;
class DescriptorFactory
{
public:
    static Descriptor* CreateDescriptor(base::BitReadWriter *rw);

    enum DescriptorTag
    {
        /**
         * @note It is related in ARIB STD-B60 version 1.2
         **/
        APPLICATION_DESCRIPTOR = 0x8029,
        TRANSPORT_PROTOCOL_DESCRIPTOR = 0x802A,
        SIMPLE_APPLICATION_LOCATION_DESCRIPTOR = 0x802B,

        APPLICATION_BOUNDARY_AND_PERMISSION_DESCRIPTOR = 0x802C,
        AUTOSTART_PRIORITY_DESCRIPTOR = 0X802D,
        CACHE_CONTROL_INFO_DESCRIPTOR = 0x802E,
        RANDOMIZED_LATENCY_DESCRIPTOR = 0x802F,

        UNKNOWN_DESCRIPTOR = 0xFFFF,

    };

private:
    DescriptorFactory(){};
    virtual ~DescriptorFactory(){};
};

/** @} */

} // end of mh namespace

/** @} */

} // end of sedec namespace
#endif
