#if !defined __DVB_DESCRIPTOR_H__
#define __DVB_DESCRIPTOR_H__

#include "base/bit_readwriter.h"

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
    } _SUPPORTED_DESCRIPTOR_TAG_;

protected:
    virtual void calcLength()=0;
    const int DESCRIPTOR_HEADER_LENGTH = 2;

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

} // end of dvb namespace

/** @} */

} // end of sedec namespace
#endif
