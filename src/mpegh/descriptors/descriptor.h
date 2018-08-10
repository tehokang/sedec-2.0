#if !defined __MH_DESCRIPTOR_H__
#define __MH_DESCRIPTOR_H__

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
    @addtogroup mh
    @{
*/

class Descriptor
{
public:
    Descriptor();
    Descriptor(base::BitReadWriter *rw);
    virtual ~Descriptor();

    int GetDescriptorLength();
    int GetDescriptorTag();

    virtual void WriteDescriptor(base::BitReadWriter* rw);
    virtual void PrintDescriptor()=0;

    static enum DESCRIPTOR_TAG
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

    } _SUPPORTED_DESCRIPTOR_TAG_;

protected:
    virtual void calcLength()=0;
    const int DESCRIPTOR_HEADER_LENGTH = 3;

    int descriptor_tag;
    int descriptor_length;
};

class UnknownDescriptor : public Descriptor
{
public:
    UnknownDescriptor();
    UnknownDescriptor(base::BitReadWriter *rw);
    virtual ~UnknownDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw){};
    virtual void PrintDescriptor();

protected:
    virtual void calcLength(){};
};

/** @} */

} // end of mh namespace

/** @} */

} // end of sedec namespace
#endif
