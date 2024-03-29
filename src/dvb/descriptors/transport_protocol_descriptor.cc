#include <stdlib.h>
#include <string.h>

#include "base/macro.h"
#include "descriptors/transport_protocol_descriptor.h"


namespace sedec
{

namespace dvb
{

TransportProtocolDescriptor::TransportProtocolDescriptor()
{
    descriptor_tag = 0x02;
    descriptor_length = 0;

    protocol_id = 0;
    transport_protocol_label = 0;
    memset(&transport, 0x00, sizeof(Transport));
    memset(&channel_transport, 0x00, sizeof(Channeltransport));

    /**
     * @note It is related in IPTVFJ STD-0010 version 2.0
     **/
    memset(&transport, 0x00, sizeof(Transport));
}

TransportProtocolDescriptor::TransportProtocolDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    protocol_id = rw->Read_On_Buffer(16);
    transport_protocol_label = rw->Read_On_Buffer(8);

    if( 0 < descriptor_length-3 )
    {
        switch(protocol_id)
        {
            case PROTOCOL_OBJECT_CAROUSEL:
                {
                    memset(&transport, 0x00, sizeof(Transport));
                    transport.remote_connection = rw->Read_On_Buffer(1);
                    rw->Skip_On_Buffer(7);
                    if(0x01 == transport.remote_connection)
                    {
                        transport.original_network_id = rw->Read_On_Buffer(16);
                        transport.transport_stream_id = rw->Read_On_Buffer(16);
                        transport.service_id = rw->Read_On_Buffer(16);
                    }
                    transport.component_tag = rw->Read_On_Buffer(8);
                }
                break;
            case PROTOCOL_HTTP:
                {
                    memset(&channel_transport, 0x00, sizeof(Channeltransport));
                    channel_transport.URL_base_length = rw->Read_On_Buffer(8);
                    for(int i=0;i<channel_transport.URL_base_length;i++)
                        channel_transport.URL_base_byte[i] = rw->Read_On_Buffer(8);
                    channel_transport.URL_extension_count = rw->Read_On_Buffer(8);

                    for(int i=0;i<channel_transport.URL_extension_count;i++)
                    {
                        UrlExtension *ext = new UrlExtension;
                        ext->URL_extension_length = 0;
                        memset(ext->URL_extension_byte, 0x00, sizeof(ext->URL_extension_byte));

                        ext->URL_extension_length = rw->Read_On_Buffer(8);
                        for(int j=0;j<ext->URL_extension_length;j++)
                            ext->URL_extension_byte[j] = rw->Read_On_Buffer(8);
                        url_extensions.push_back(ext);
                    }

                }
                break;
            /**
             * @note It is related in IPTVFJ STD-0010 version 2.0
             **/
            case PROTOCOL_DATA_CAROUSEL:
                {
                    memset(&transport, 0x00, sizeof(Transport));
                    transport.remote_connection = rw->Read_On_Buffer(1);
                    rw->Skip_On_Buffer(7);
                    if(0x01 == transport.remote_connection)
                    {
                        transport.original_network_id = rw->Read_On_Buffer(16);
                        transport.transport_stream_id = rw->Read_On_Buffer(16);
                        transport.service_id = rw->Read_On_Buffer(16);
                    }
                    transport.component_tag = rw->Read_On_Buffer(8);
                }
                break;
            default:
                break;
        }
    }
}

TransportProtocolDescriptor::~TransportProtocolDescriptor()
{
    for (std::list<UrlExtension *>::iterator it=url_extensions.begin();
        it != url_extensions.end(); ++it)
    {
        delete (*it);
    }
    url_extensions.clear();
}

void TransportProtocolDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    Descriptor::PrintDescriptor("TransportProtocolDescriptor");

    SECTION_DEBUG("\tprotocol_id : %x \n", protocol_id);
    SECTION_DEBUG("\ttransport_protocol_label : %x \n", transport_protocol_label);

    switch(protocol_id)
    {
        case PROTOCOL_OBJECT_CAROUSEL:
            {
                SECTION_DEBUG("\tremote_connection : %x \n", transport.remote_connection);
                if(0x01 == transport.remote_connection)
                {
                    SECTION_DEBUG("\toriginal_network_id : %x \n", transport.original_network_id);
                    SECTION_DEBUG("\ttransport_stream_id : %x \n", transport.transport_stream_id);
                    SECTION_DEBUG("\tservice_id : %x \n", transport.service_id);
                }
                SECTION_DEBUG("\tcomponent_tag : %x \n", transport.component_tag);
            }
            break;
        case PROTOCOL_HTTP:
            {
                SECTION_DEBUG("\tURL_base_length : 0x%x (%d) \n",
                                channel_transport.URL_base_length, channel_transport.URL_base_length);
                SECTION_DEBUG("\tURL_base_byte : %s \n", channel_transport.URL_base_byte);
                SECTION_DEBUG("\tURL_extension_count : 0x%x \n", channel_transport.URL_extension_count);

                for (std::list<UrlExtension *>::iterator it=url_extensions.begin();
                    it != url_extensions.end(); ++it)
                {
                    SECTION_DEBUG("\tmanaged_URL_length : 0x%x \n", (*it)->URL_extension_length);
                    SECTION_DEBUG("\tmanaged_URL_byte : %s \n", (*it)->URL_extension_byte);
                }
            }
            break;
        /**
         * @note It is related in IPTVFJ STD-0010 version 2.0
         **/
        case PROTOCOL_DATA_CAROUSEL:
            {
                SECTION_DEBUG("\tremote_connection : %x \n", transport.remote_connection);
                if(0x01 == transport.remote_connection)
                {
                    SECTION_DEBUG("\toriginal_network_id : %x \n", transport.original_network_id);
                    SECTION_DEBUG("\ttransport_stream_id : %x \n", transport.transport_stream_id);
                    SECTION_DEBUG("\tservice_id : %x \n", transport.service_id);
                }
                SECTION_DEBUG("\tcomponent_tag : %x \n", transport.component_tag);
            }
            break;
        default:
            break;
    }
    SECTION_DEBUG("\n");
}

void TransportProtocolDescriptor::updateDescriptorLength()
{
    int selector_byte_length = 0;
    switch(protocol_id)
    {
        case PROTOCOL_OBJECT_CAROUSEL:
            if(0x01 == transport.remote_connection)
                selector_byte_length = 8;
            else
                selector_byte_length = 2;
            break;
        case PROTOCOL_HTTP:
            {
                selector_byte_length = 1 + channel_transport.URL_base_length +
                                        1 + channel_transport.URL_extension_count;

                for (std::list<UrlExtension *>::iterator it=url_extensions.begin();
                    it != url_extensions.end(); ++it)
                {
                    selector_byte_length += 1 + (*it)->URL_extension_length;
                }
            }
            break;
        /**
         * @note It is related in IPTVFJ STD-0010 version 2.0
         **/
        case PROTOCOL_DATA_CAROUSEL:
            if(0x01 == transport.remote_connection)
                selector_byte_length = 8;
            else
                selector_byte_length = 2;
            break;
        default:
            break;
    }
    descriptor_length = 3 + selector_byte_length;
}

void TransportProtocolDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    rw->Write_On_Buffer(protocol_id, 16);
    rw->Write_On_Buffer(transport_protocol_label, 8);

    switch(protocol_id)
    {
        case PROTOCOL_OBJECT_CAROUSEL:
            rw->Write_On_Buffer(transport.remote_connection, 1);
            rw->Write_On_Buffer(0x7f, 7);
            if(0x01 == transport.remote_connection)
            {
                rw->Write_On_Buffer(transport.original_network_id, 16);
                rw->Write_On_Buffer(transport.transport_stream_id, 16);
                rw->Write_On_Buffer(transport.service_id, 16);
            }
            rw->Write_On_Buffer(transport.component_tag, 8);
            break;
        case PROTOCOL_HTTP:
            rw->Write_On_Buffer(channel_transport.URL_base_length, 8);
            for(int i=0;i<channel_transport.URL_base_length;i++)
                rw->Write_On_Buffer(channel_transport.URL_base_byte[i], 8);

            rw->Write_On_Buffer(channel_transport.URL_extension_count, 8);

            for (std::list<UrlExtension *>::iterator it=url_extensions.begin();
                it != url_extensions.end(); ++it)
            {
                rw->Write_On_Buffer((*it)->URL_extension_length, 8);
                for(int j=0;j<(*it)->URL_extension_length;j++)
                    rw->Write_On_Buffer((*it)->URL_extension_byte[j], 8);
            }
            break;
        /**
         * @note It is related in IPTVFJ STD-0010 version 2.0
         **/
        case PROTOCOL_DATA_CAROUSEL:
            rw->Write_On_Buffer(transport.remote_connection, 1);
            rw->Write_On_Buffer(0x7f, 7);
            if(0x01 == transport.remote_connection)
            {
                rw->Write_On_Buffer(transport.original_network_id, 16);
                rw->Write_On_Buffer(transport.transport_stream_id, 16);
                rw->Write_On_Buffer(transport.service_id, 16);
            }
            rw->Write_On_Buffer(transport.component_tag, 8);
            break;
        default:
            break;
    }
}

} // end of dvb namespace

} // end of sedec namespace
