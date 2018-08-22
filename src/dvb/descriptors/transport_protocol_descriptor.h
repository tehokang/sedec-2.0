#if !defined __DVB_TRANSPORT_PROTOCOL_DESC__
#define __DVB_TRANSPORT_PROTOCOL_DESC__

#include <list>
#include <string.h>
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

class TransportProtocolDescriptor : public Descriptor
{
public:
    TransportProtocolDescriptor();
    TransportProtocolDescriptor(base::BitReadWriter *rw);
    virtual ~TransportProtocolDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw) override;
    virtual void PrintDescriptor() override;

    /* Interface to encode (setter) */
    void SetBaseUrl(const char *base_url)
    {
        memset(&channel_transport, 0x00, sizeof(Channeltransport));
        channel_transport.URL_base_length = strlen(base_url);
        for(int i=0;i<channel_transport.URL_base_length;i++)
            channel_transport.URL_base_byte[i] = base_url[i];
        channel_transport.URL_extension_count = 0;
    }
    void SetProtocolId(unsigned int value){ protocol_id = value;}
    void SetTransportProtocolLabel(unsigned char value)
    {
        transport_protocol_label = value;
    }
    void SetRemoteConnection(unsigned char value)
    {
        transport.remote_connection = value;
    }
    void SetOriginalNetworkId(unsigned int value)
    {
        transport.original_network_id = value;
    }
    void SetTransportStreamId(unsigned int value)
    {
        transport.transport_stream_id = value;
    }
    void SetServiceId(unsigned int value)
    {
        transport.service_id = value;
    }
    void SetComponentTag(unsigned char value)
    {
        transport.component_tag = value;
    }

    /* Interface to decode (getter) */
    char* GetBaseUrl() { return channel_transport.URL_base_byte;}
    unsigned int GetProtocolId() { return protocol_id;}
    unsigned char GetTransportProtocolLabel() { return transport_protocol_label;}
    unsigned char GetRemoteConnection() { return transport.remote_connection;}
    unsigned int GetOriginalNetworkId() { return transport.original_network_id;}
    unsigned int GetTransportStreamId() { return transport.transport_stream_id;}
    unsigned int GetServiceId(){ return transport.service_id;}
    unsigned char GetComponentTag(){ return transport.component_tag;}

protected:
    virtual void updateDescriptorLength() override;

    enum{
        PROTOCOL_OBJECT_CAROUSEL=0x0001,
        PROTOCOL_HTTP=0x0003,
        /**
         * @note It is related in IPTVFJ STD-0010 version 2.0
         **/
        PROTOCOL_DATA_CAROUSEL=0x0004,
    };
    unsigned int protocol_id;
    unsigned char transport_protocol_label;

    /**
     * @note It is related in IPTVFJ STD-0010 version 2.0
     **/
    struct Transport{
        unsigned char remote_connection;
        unsigned int original_network_id;
        unsigned int transport_stream_id;
        unsigned int service_id;
        unsigned char component_tag;
    };
    Transport transport;

    struct UrlExtension {
        unsigned char URL_extension_length;
        char URL_extension_byte[256];
    };
    std::list<UrlExtension *> url_extensions;

    struct Channeltransport {
        unsigned char URL_base_length;
        char URL_base_byte[256];
        unsigned char URL_extension_count;
    };

    Channeltransport channel_transport;
};

/** @} */

} // end of dvb namespace

/** @} */

} // end of sedec namespace
#endif
