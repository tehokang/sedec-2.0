// dvb_ait_transcoder.cpp: implementation of the ApplicationInformationTableTranscoder class.
//
//////////////////////////////////////////////////////////////////////

#include "section_common.h"
#include "dvb_ait_transcoder.h"
#include "descriptors/dvb/descriptor.h"
#include "descriptors/dvb/application.h"
#include "descriptors/dvb/descriptor_factory.h"
#include "descriptors/dvb/simple_application_location_descriptor.h"
#include "descriptors/dvb/transport_protocol_descriptor.h"
#include "descriptors/dvb/application_descriptor.h"

#include <string.h>
#include <cstddef>
#include <stdlib.h>

namespace sedec
{

using namespace dvb;

ApplicationInformationTableTranscoder::ApplicationInformationTableTranscoder()
{
    m_section_name = strdup("ApplicationInformationTable");
}

ApplicationInformationTableTranscoder::ApplicationInformationTableTranscoder(unsigned char *raw_buffer)
    : DVBAit(raw_buffer, (( raw_buffer[1] << 8 | raw_buffer[2] ) & 0x0fff ) + 3)
{

}


ApplicationInformationTableTranscoder::ApplicationInformationTableTranscoder(unsigned char *raw_buffer, unsigned int raw_length)
    : DVBAit(raw_buffer, raw_length)
{

}

ApplicationInformationTableTranscoder::~ApplicationInformationTableTranscoder()
{
    if(m_section_name) {
        free(m_section_name);
        m_section_name = NULL;
    }
}

Descriptor* ApplicationInformationTableTranscoder::findDescriptor(list<Descriptor*>descriptors,
        Descriptor::DESCRIPTOR_TAG tag)
{
    for (std::list<Descriptor*>::iterator it=descriptors.begin();
        it != descriptors.end(); ++it)
    {
        Descriptor *desc = (Descriptor*)*it;
        if( tag == desc->GetDescriptorTag())
            return desc;
    }
    return NULL;
}

void ApplicationInformationTableTranscoder::SetApplicationUrl(const char *base_url, const char *init_path)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
            it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                Descriptor::SIMPLE_APPLICATION_LOCATION_DESCRIPTOR);
        ((SimpleApplicationLocationDescriptor*)desc)->SetInitialPath(init_path);

        desc = findDescriptor(app->GetDescriptors(),
                Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetBaseUrl(base_url);
    }
}

void ApplicationInformationTableTranscoder::SetApplicationVisibility(const int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
            it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                Descriptor::APPLICATION_DESCRIPTOR);
        ((ApplicationDescriptor*)desc)->SetVisibility(value);
    }
}

void ApplicationInformationTableTranscoder::SetApplicationVersion(const int major, const int minor, const int micro)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
        it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                Descriptor::APPLICATION_DESCRIPTOR);
        ((ApplicationDescriptor*)desc)->SetApplicationVersion(major, minor, micro);
    }
}

void ApplicationInformationTableTranscoder::GetApplicationVersion(int &major, int &minor, int &micro)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
            it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                Descriptor::APPLICATION_DESCRIPTOR);
        ((ApplicationDescriptor*)desc)->GetApplicationVersion(&major, &minor, &micro);
    }
}

void ApplicationInformationTableTranscoder::GetApplicationUrl(const char **base_url, const char **init_path)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
            it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                Descriptor::SIMPLE_APPLICATION_LOCATION_DESCRIPTOR);
        *init_path = ((SimpleApplicationLocationDescriptor*)desc)->GetInitialPath();

        desc = findDescriptor(app->GetDescriptors(),
                Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
        *base_url = ((TransportProtocolDescriptor*)desc)->GetBaseUrl();
    }
}

void ApplicationInformationTableTranscoder::SetTransportProtocolLabel(const char *label)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
            it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                Descriptor::APPLICATION_DESCRIPTOR);
        ((ApplicationDescriptor*)desc)->SetTransportProtocolLabel(label);

        desc = findDescriptor(app->GetDescriptors(),
                Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetTransportProtocolLabel((unsigned char)atoi(label));
    }
}

void ApplicationInformationTableTranscoder::SetApplicationId(const int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
            it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        app->SetApplicationId(value);
    }
}

void ApplicationInformationTableTranscoder::SetOrganizationId(const int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
            it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        app->SetOrganizationId(value);
    }
}

void ApplicationInformationTableTranscoder::SetProtocolId(int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
                it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                                Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetProtocolId(value);
    }
}

void ApplicationInformationTableTranscoder::SetRemoteConnection(const int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
                it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                                Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetRemoteConnection(value);
    }
}

void ApplicationInformationTableTranscoder::SetOriginalNetworkId(const int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
                it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                                Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetOriginalNetworkId(value);
    }
}

void ApplicationInformationTableTranscoder::SetTransportStreamId(const int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
                it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                                Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetTransportStreamId(value);
    }
}

void ApplicationInformationTableTranscoder::SetServiceId(const int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
                it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                                Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetServiceId(value);
    }
}

void ApplicationInformationTableTranscoder::SetComponentTag(const int value)
{
    for (std::list<Application*>::iterator it=m_applications.begin();
                it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                                Descriptor::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetComponentTag(value);
    }
}

void ApplicationInformationTableTranscoder::SetCommonDescriptors(list<Descriptor*> value)
{
    common_descriptors_length = 0;
    for (list<Descriptor*>::iterator it=value.begin();
        it != value.end(); ++it)
    {
        Descriptor *desc = (Descriptor*)*it;
        common_descriptors_length+=desc->GetDescriptorLength();
    }
    m_common_descriptors = value;
}

void ApplicationInformationTableTranscoder::SetApplications(list<Application*> value)
{
    application_loop_length = 0;
    for (list<Application*>::iterator it=value.begin();
            it != value.end(); ++it)
    {
        Application *app = (Application*)*it;
        application_loop_length += app->GetApplicationLength();
    }
    m_applications = value;
}

} // end of sedec namespace

