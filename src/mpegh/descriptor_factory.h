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
        TRANSPORT_PROTOCOL_DESCRIPTOR = 0x802a,
        SIMPLE_APPLICATION_LOCATION_DESCRIPTOR = 0x802b,

        APPLICATION_BOUNDARY_AND_PERMISSION_DESCRIPTOR = 0x802c,
        AUTOSTART_PRIORITY_DESCRIPTOR = 0x802d,
        CACHE_CONTROL_INFO_DESCRIPTOR = 0x802e,
        RANDOMIZED_LATENCY_DESCRIPTOR = 0x802f,

       /**
         * @note 10.3.4 ,. Descriptor used in the data asset management table
         **/
        TYPE_DESCRIPTOR = 0x801c,
        INFO_DESCRIPTOR = 0x801d,
        EXPIRE_DESCRIPTOR = 0x801e,
        COMPRESSION_TYPE_DESCRIPTOR = 0x801f,

        /**
         * @note 10.3.5 ,. Descriptor used in the data content management table
         **/
        LINKED_PU_DESCRIPTOR = 0x8030,
        LOCKED_CACHE_DESCRIPTOR = 0x8031,
        UNLOCKED_CACHE_DESCRIPTOR = 0x8032,

        UNKNOWN_DESCRIPTOR = 0xffff,
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
