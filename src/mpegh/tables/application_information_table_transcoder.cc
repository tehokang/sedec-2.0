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

using namespace mpegh;

ApplicationInformationTableTranscoder::ApplicationInformationTableTranscoder()
{
}

ApplicationInformationTableTranscoder::ApplicationInformationTableTranscoder(unsigned char *raw_buffer)
    : ApplicationInformationTable(raw_buffer, (( raw_buffer[1] << 8 | raw_buffer[2] ) & 0x0fff ) + 3)
{

}


ApplicationInformationTableTranscoder::ApplicationInformationTableTranscoder(unsigned char *raw_buffer, unsigned int raw_length)
    : ApplicationInformationTable(raw_buffer, raw_length)
{

}

ApplicationInformationTableTranscoder::~ApplicationInformationTableTranscoder()
{
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

void ApplicationInformationTable::__encode_preprare_section__()
{
    common_descriptors_length = 0;
    for (std::list<Descriptor*>::iterator it=m_common_descriptors.begin();
            it != m_common_descriptors.end(); ++it)
    {
        Descriptor *desc = (Descriptor*)*it;
        common_descriptors_length+=desc->GetDescriptorLength();
    }

    application_loop_length = 0;
    for (std::list<Application*>::iterator it=m_applications.begin();
            it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        application_loop_length += app->GetApplicationLength();
    }
}

void ApplicationInformationTable::__encode_update_section_length__()
{
    section_length = 0;
    for (std::list<Descriptor*>::iterator it=m_common_descriptors.begin();
            it != m_common_descriptors.end(); ++it)
    {
        Descriptor *desc = (Descriptor*)*it;
        section_length += desc->GetDescriptorLength();
    }

    for (std::list<Application*>::iterator it=m_applications.begin();
            it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        section_length += app->GetApplicationLength();
    }
    section_length += 13; /* 9 + crc(4) */
}

void ApplicationInformationTable::__encode_write_section_body__()
{
    Write_On_Buffer(application_type, 16);
    Write_On_Buffer(0x03, 2);
    Write_On_Buffer(version_number, 5);
    Write_On_Buffer(current_next_indicator, 1);
    Write_On_Buffer(section_number, 8);
    Write_On_Buffer(last_section_number, 8);
    Write_On_Buffer(0x0f, 4);
    Write_On_Buffer(common_descriptors_length, 12);

    for (std::list<Descriptor*>::iterator it=m_common_descriptors.begin();
            it != m_common_descriptors.end(); ++it)
    {
        Descriptor *desc = (Descriptor*)*it;
        desc->WriteDescriptor(this);
    }

    Write_On_Buffer(0x0f, 4);
    Write_On_Buffer(application_loop_length, 12);

    for (std::list<Application*>::iterator it=m_applications.begin();
            it != m_applications.end(); ++it)
    {
        Application *app = (Application*)*it;
        app->WriteApplication(this);
    }
}

} // end of sedec namespace

