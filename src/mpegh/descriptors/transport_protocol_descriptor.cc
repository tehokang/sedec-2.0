// transport_protocol_descriptor.cpp: implementation of the TransportProtocolDescriptor class.
//
//////////////////////////////////////////////////////////////////////
#include "section_common.h"
#include "descriptors/mh/transport_protocol_descriptor.h"
#include "bit_readwriter.h"

#include <stdlib.h>
#include <string.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace sedec
{

namespace mh
{

TransportProtocolDescriptor::TransportProtocolDescriptor()
{
    descriptor_tag = TRANSPORT_PROTOCOL_DESCRIPTOR;
    descriptor_length = 0;

    protocol_id = 0;
    transport_protocol_label = 0;
    memset(&oc_transport, 0x00, sizeof(OCtransport));
    memset(&channel_transport, 0x00, sizeof(Channeltransport));

    /**
     * @note It is related in IPTVFJ STD-0010 version 2.0
     **/
    memset(&dc_transport, 0x00, sizeof(DCtransport));
}

TransportProtocolDescriptor::TransportProtocolDescriptor(BitReadWriter *rw) : Descriptor(rw)
{
    protocol_id = rw->Read_On_Buffer(16);
    transport_protocol_label = rw->Read_On_Buffer(8);

    if( 0 < descriptor_length-3 )
    {
        switch(protocol_id)
        {
            case PROTOCOL_OBJECT_CAROUSEL:
                {
                    memset(&oc_transport, 0x00, sizeof(OCtransport));
                    oc_transport.remote_connection = rw->Read_On_Buffer(1);
                    rw->Skip_On_Buffer(7);
                    if(0x01 == oc_transport.remote_connection)
                    {
                        oc_transport.original_network_id = rw->Read_On_Buffer(16);
                        oc_transport.transport_stream_id = rw->Read_On_Buffer(16);
                        oc_transport.service_id = rw->Read_On_Buffer(16);
                    }
                    oc_transport.component_tag = rw->Read_On_Buffer(8);
                }
                break;
            /**
             * @note It is related in ARIB STD-B60 version 1.2
             **/
            case PROTOCOL_HTTP:
            case PROTOCOL_MMT_NON_TIMED: 
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
                    memset(&dc_transport, 0x00, sizeof(DCtransport));
                    dc_transport.remote_connection = rw->Read_On_Buffer(1);
                    rw->Skip_On_Buffer(7);
                    if(0x01 == dc_transport.remote_connection)
                    {
                        dc_transport.original_network_id = rw->Read_On_Buffer(16);
                        dc_transport.transport_stream_id = rw->Read_On_Buffer(16);
                        dc_transport.service_id = rw->Read_On_Buffer(16);
                    }
                    dc_transport.component_tag = rw->Read_On_Buffer(8);
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
    SECTION_DEBUG("\tdescriptor_tag : 0x%04x (transport_protocol_descriptor)\n", descriptor_tag);
    SECTION_DEBUG("\tdescriptor_length : 0x%x \n", descriptor_length);
    SECTION_DEBUG("\tprotocol_id : %x \n", protocol_id);
    SECTION_DEBUG("\ttransport_protocol_label : %x \n", transport_protocol_label);

    switch(protocol_id)
    {
        case PROTOCOL_OBJECT_CAROUSEL:
            {
                SECTION_DEBUG("\tremote_connection : %x \n", oc_transport.remote_connection);
                if(0x01 == oc_transport.remote_connection)
                {
                    SECTION_DEBUG("\toriginal_network_id : %x \n", oc_transport.original_network_id);
                    SECTION_DEBUG("\ttransport_stream_id : %x \n", oc_transport.transport_stream_id);
                    SECTION_DEBUG("\tservice_id : %x \n", oc_transport.service_id);
                }
                SECTION_DEBUG("\tcomponent_tag : %x \n", oc_transport.component_tag);
            }
            break;
        /**
         * @note It is related in ARIB STD-B60 version 1.2
         **/
        case PROTOCOL_HTTP:
        case PROTOCOL_MMT_NON_TIMED: 
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
                SECTION_DEBUG("\tremote_connection : %x \n", dc_transport.remote_connection);
                if(0x01 == dc_transport.remote_connection)
                {
                    SECTION_DEBUG("\toriginal_network_id : %x \n", dc_transport.original_network_id);
                    SECTION_DEBUG("\ttransport_stream_id : %x \n", dc_transport.transport_stream_id);
                    SECTION_DEBUG("\tservice_id : %x \n", dc_transport.service_id);
                }
                SECTION_DEBUG("\tcomponent_tag : %x \n", dc_transport.component_tag);
            }
            break;
        default:
            break;
    }
    SECTION_DEBUG("\n");
}

void TransportProtocolDescriptor::calcLength()
{
    int selector_byte_length = 0;
    switch(protocol_id)
    {
        case PROTOCOL_OBJECT_CAROUSEL:
            if(0x01 == oc_transport.remote_connection)
                selector_byte_length = 8;
            else
                selector_byte_length = 2;
            break;
        /**
         * @note It is related in ARIB STD-B60 version 1.2
         **/
        case PROTOCOL_HTTP:
        case PROTOCOL_MMT_NON_TIMED:        
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
            if(0x01 == dc_transport.remote_connection)
                selector_byte_length = 8;
            else
                selector_byte_length = 2;
            break;    
        default:
            break;
    }
    descriptor_length = 3 + selector_byte_length;
}

void TransportProtocolDescriptor::WriteDescriptor(BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    rw->Write_On_Buffer(protocol_id, 16);
    rw->Write_On_Buffer(transport_protocol_label, 8);

    switch(protocol_id)
    {
        case PROTOCOL_OBJECT_CAROUSEL:
            rw->Write_On_Buffer(oc_transport.remote_connection, 1);
            rw->Write_On_Buffer(0x7f, 7);
            if(0x01 == oc_transport.remote_connection)
            {
                rw->Write_On_Buffer(oc_transport.original_network_id, 16);
                rw->Write_On_Buffer(oc_transport.transport_stream_id, 16);
                rw->Write_On_Buffer(oc_transport.service_id, 16);
            }
            rw->Write_On_Buffer(oc_transport.component_tag, 8);
            break;
        /**
         * @note It is related in ARIB STD-B60 version 1.2
         **/
        case PROTOCOL_HTTP:
        case PROTOCOL_MMT_NON_TIMED: 
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
            rw->Write_On_Buffer(dc_transport.remote_connection, 1);
            rw->Write_On_Buffer(0x7f, 7);
            if(0x01 == dc_transport.remote_connection)
            {
                rw->Write_On_Buffer(dc_transport.original_network_id, 16);
                rw->Write_On_Buffer(dc_transport.transport_stream_id, 16);
                rw->Write_On_Buffer(dc_transport.service_id, 16);
            }
            rw->Write_On_Buffer(dc_transport.component_tag, 8);
            break;            
        default:
            break;
    }
}

} // end of mh namespace

} // end of sedec namespace
