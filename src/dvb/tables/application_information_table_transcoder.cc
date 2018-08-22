#include <string.h>
#include <cstddef>
#include <stdlib.h>

#include "base/macro.h"
#include "application_information_table_transcoder.h"

#include "descriptor_factory.h"
#include "descriptors/descriptor.h"
#include "descriptors/application.h"
#include "descriptors/application_descriptor.h"
#include "descriptors/transport_protocol_descriptor.h"
#include "descriptors/simple_application_location_descriptor.h"

namespace sedec
{

using namespace dvb;

ApplicationInformationTableTranscoder::ApplicationInformationTableTranscoder()
{
}

ApplicationInformationTableTranscoder::ApplicationInformationTableTranscoder(
      unsigned char *raw_buffer)
    : ApplicationInformationTable(raw_buffer,
            (( raw_buffer[1] << 8 | raw_buffer[2] ) & 0x0fff ) + 3)
{

}


ApplicationInformationTableTranscoder::ApplicationInformationTableTranscoder(
      unsigned char *raw_buffer, unsigned int raw_length)
    : ApplicationInformationTable(raw_buffer, raw_length)
{

}

ApplicationInformationTableTranscoder::~ApplicationInformationTableTranscoder()
{
}

Descriptor* ApplicationInformationTableTranscoder::findDescriptor(
    list<Descriptor*>descriptors, int tag)
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

void ApplicationInformationTableTranscoder::__encode_preprare_section__()
{
    common_descriptors_length = 0;
    for (std::list<Descriptor*>::iterator it=common_descriptors.begin();
            it != common_descriptors.end(); ++it)
    {
        Descriptor *desc = (Descriptor*)*it;
        common_descriptors_length+=desc->GetDescriptorLength();
    }

    application_loop_length = 0;
    for (std::list<Application*>::iterator it=applications.begin();
            it != applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        application_loop_length += app->GetApplicationLength();
    }
}

void ApplicationInformationTableTranscoder::__encode_update_section_length__()
{
    section_length = 0;
    for (std::list<Descriptor*>::iterator it=common_descriptors.begin();
            it != common_descriptors.end(); ++it)
    {
        Descriptor *desc = (Descriptor*)*it;
        section_length += desc->GetDescriptorLength();
    }

    for (std::list<Application*>::iterator it=applications.begin();
            it != applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        section_length += app->GetApplicationLength();
    }
    section_length += 13; /* 9 + crc(4) */
}

void ApplicationInformationTableTranscoder::__encode_write_section_body__()
{
    Write_On_Buffer(test_application_flag, 1);
    Write_On_Buffer(application_type, 15);
    Write_On_Buffer(0x03, 2);
    Write_On_Buffer(version_number, 5);
    Write_On_Buffer(current_next_indicator, 1);
    Write_On_Buffer(section_number, 8);
    Write_On_Buffer(last_section_number, 8);
    Write_On_Buffer(0x0f, 4);
    Write_On_Buffer(common_descriptors_length, 12);

    for (std::list<Descriptor*>::iterator it=common_descriptors.begin();
            it != common_descriptors.end(); ++it)
    {
        Descriptor *desc = (Descriptor*)*it;
        desc->WriteDescriptor(this);
    }

    Write_On_Buffer(0x0f, 4);
    Write_On_Buffer(application_loop_length, 12);

    for (std::list<Application*>::iterator it=applications.begin();
            it != applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        app->WriteApplication(this);
    }
}

void ApplicationInformationTableTranscoder::SetApplicationUrl(
        const char *base_url, const char *init_path)
{
    for (std::list<Application*>::iterator it=applications.begin();
            it != applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                DescriptorFactory::SIMPLE_APPLICATION_LOCATION_DESCRIPTOR);
        ((SimpleApplicationLocationDescriptor*)desc)->SetInitialPath(init_path);

        desc = findDescriptor(app->GetDescriptors(),
                DescriptorFactory::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetBaseUrl(base_url);
    }
}

void ApplicationInformationTableTranscoder::SetApplicationVisibility(
        const int value)
{
    for (std::list<Application*>::iterator it=applications.begin();
            it != applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                DescriptorFactory::APPLICATION_DESCRIPTOR);
        ((ApplicationDescriptor*)desc)->SetVisibility(value);
    }
}

void ApplicationInformationTableTranscoder::SetApplicationVersion(
        const int major, const int minor, const int micro)
{
    for (std::list<Application*>::iterator it=applications.begin();
        it != applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                DescriptorFactory::APPLICATION_DESCRIPTOR);
        ((ApplicationDescriptor*)desc)->SetApplicationVersion(major, minor, micro);
    }
}

void ApplicationInformationTableTranscoder::GetApplicationVersion(
        int &major, int &minor, int &micro)
{
    for (std::list<Application*>::iterator it=applications.begin();
            it != applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                DescriptorFactory::APPLICATION_DESCRIPTOR);
        ((ApplicationDescriptor*)desc)->GetApplicationVersion(&major, &minor, &micro);
    }
}

void ApplicationInformationTableTranscoder::GetApplicationUrl(
        const char **base_url, const char **init_path)
{
    for (std::list<Application*>::iterator it=applications.begin();
            it != applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                DescriptorFactory::SIMPLE_APPLICATION_LOCATION_DESCRIPTOR);
        *init_path = ((SimpleApplicationLocationDescriptor*)desc)->GetInitialPath();

        desc = findDescriptor(app->GetDescriptors(),
                DescriptorFactory::TRANSPORT_PROTOCOL_DESCRIPTOR);
        *base_url = ((TransportProtocolDescriptor*)desc)->GetBaseUrl();
    }
}

void ApplicationInformationTableTranscoder::SetTransportProtocolLabel(
        const char *label)
{
    for (std::list<Application*>::iterator it=applications.begin();
            it != applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                DescriptorFactory::APPLICATION_DESCRIPTOR);
        ((ApplicationDescriptor*)desc)->SetTransportProtocolLabel(label);

        desc = findDescriptor(app->GetDescriptors(),
                DescriptorFactory::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetTransportProtocolLabel(
                (unsigned char)atoi(label));
    }
}

void ApplicationInformationTableTranscoder::SetApplicationId(const int value)
{
    for (std::list<Application*>::iterator it=applications.begin();
            it != applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        app->SetApplicationId(value);
    }
}

void ApplicationInformationTableTranscoder::SetOrganizationId(const int value)
{
    for (std::list<Application*>::iterator it=applications.begin();
            it != applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        app->SetOrganizationId(value);
    }
}

void ApplicationInformationTableTranscoder::SetProtocolId(int value)
{
    for (std::list<Application*>::iterator it=applications.begin();
                it != applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                DescriptorFactory::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetProtocolId(value);
    }
}

void ApplicationInformationTableTranscoder::SetRemoteConnection(const int value)
{
    for (std::list<Application*>::iterator it=applications.begin();
                it != applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                                DescriptorFactory::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetRemoteConnection(value);
    }
}

void ApplicationInformationTableTranscoder::SetOriginalNetworkId(const int value)
{
    for (std::list<Application*>::iterator it=applications.begin();
                it != applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                                DescriptorFactory::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetOriginalNetworkId(value);
    }
}

void ApplicationInformationTableTranscoder::SetTransportStreamId(const int value)
{
    for (std::list<Application*>::iterator it=applications.begin();
                it != applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                                DescriptorFactory::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetTransportStreamId(value);
    }
}

void ApplicationInformationTableTranscoder::SetServiceId(const int value)
{
    for (std::list<Application*>::iterator it=applications.begin();
                it != applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                                DescriptorFactory::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetServiceId(value);
    }
}

void ApplicationInformationTableTranscoder::SetComponentTag(const int value)
{
    for (std::list<Application*>::iterator it=applications.begin();
                it != applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        Descriptor *desc = findDescriptor(app->GetDescriptors(),
                                DescriptorFactory::TRANSPORT_PROTOCOL_DESCRIPTOR);
        ((TransportProtocolDescriptor*)desc)->SetComponentTag(value);
    }
}

void ApplicationInformationTableTranscoder::SetCommonDescriptors(
        list<Descriptor*> value)
{
    common_descriptors_length = 0;
    for (list<Descriptor*>::iterator it=value.begin();
        it != value.end(); ++it)
    {
        Descriptor *desc = (Descriptor*)*it;
        common_descriptors_length+=desc->GetDescriptorLength();
    }
    common_descriptors = value;
}

void ApplicationInformationTableTranscoder::SetApplications(
        list<Application*> value)
{
    application_loop_length = 0;
    for (list<Application*>::iterator it=value.begin();
            it != value.end(); ++it)
    {
        Application *app = (Application*)*it;
        application_loop_length += app->GetApplicationLength();
    }
    applications = value;
}

} // end of sedec namespace

