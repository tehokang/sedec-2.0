// Descriptor.h: interface for the Descriptor class.
//
//////////////////////////////////////////////////////////////////////
#if !defined __HYBRIDCAST_DESCRIPTOR_H__
#define __HYBRIDCAST_DESCRIPTOR_H__

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/
class BitReadWriter;

namespace hybridcast
{
/**
    @addtogroup hybridcast
    @{
*/

class Descriptor
{
public:	
    Descriptor();
    Descriptor(BitReadWriter *rw);
    virtual ~Descriptor();

    int GetDescriptorLength();
    int GetDescriptorTag();

    virtual void WriteDescriptor(BitReadWriter* rw);
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
        
        /**
         * @note It is related in IPTVFJ STD-0010 version 2.0
         **/
        APPLICATION_BOUNDARY_AND_PERMISSION_DESCRIPTOR = 0x30, 
        AUTOSTART_PRIORITY_DESCRIPTOR = 0X31,
        CACHE_CONTROL_INFO_DESCRIPTOR = 0x32,
        RANDOMIZED_LATENCY_DESCRIPTOR = 0x33,
        
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
    UnknownDescriptor(BitReadWriter *rw);
    virtual ~UnknownDescriptor();

    virtual void WriteDescriptor(BitReadWriter* rw){};
    virtual void PrintDescriptor();

protected:
    virtual void calcLength(){};
};

/** @} */

} // end of hybridcast namespace

/** @} */

} // end of sedec namespace
#endif 
