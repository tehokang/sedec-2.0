#include <string.h>
#include "base/macro.h"
#include "descriptors/application_descriptor.h"

namespace sedec
{

namespace arib::b24
{

ApplicationDescriptor::ApplicationDescriptor()
{
    descriptor_tag = 0x00;
    descriptor_length = 0;

    service_bound_flag = 0x00;
    visibility = 0x00;
    application_priority = 0x00;
    transport_protocol_label_length = 0x00;
    memset(&application_profiles, 0x00, sizeof(ApplicationProfile));
    memset(transport_protocol_label, 0x00, sizeof(transport_protocol_label));
}

ApplicationDescriptor::ApplicationDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    application_profiles_length = rw->Read_On_Buffer(8);
    for(int i=application_profiles_length;i>0;i-=5)
    {
        application_profiles.applicaton_profile = rw->Read_On_Buffer(16);
        application_profiles.version_major = rw->Read_On_Buffer(8);
        application_profiles.version_minor = rw->Read_On_Buffer(8);
        application_profiles.version_micro = rw->Read_On_Buffer(8);
    }
    service_bound_flag = rw->Read_On_Buffer(1);
    visibility = rw->Read_On_Buffer(2);
    rw->Skip_On_Buffer(5);
    application_priority = rw->Read_On_Buffer(8);

    transport_protocol_label_length =
        descriptor_length - 1 - (application_profiles_length>0 ? 5:0) - 2;
    memset(transport_protocol_label, 0x00, sizeof(transport_protocol_label));
    for(int i=0;i<transport_protocol_label_length;i++)
    {
        transport_protocol_label[i] = rw->Read_On_Buffer(8);
    }
}

ApplicationDescriptor::~ApplicationDescriptor()
{

}

void ApplicationDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    Descriptor::PrintDescriptor("ApplicationDescriptor");

    SECTION_DEBUG("\tapplication_profiles_length : 0x%x \n", application_profiles_length);

    SECTION_DEBUG("\tapplication_profile : 0x%04x \n", application_profiles.applicaton_profile);
    SECTION_DEBUG("\tversion_major : 0x%02x \n", application_profiles.version_major);
    SECTION_DEBUG("\tversion_minor : 0x%02x \n", application_profiles.version_minor);
    SECTION_DEBUG("\tversion_micro : 0x%02x \n", application_profiles.version_micro);
    SECTION_DEBUG("\tservice_bound_flag : %x \n", service_bound_flag);
    SECTION_DEBUG("\tvisibility : %x \n", visibility);
    SECTION_DEBUG("\tapplication_priority : %x \n", application_priority);
    for(int i=0;i<transport_protocol_label_length;i++)
    {
        SECTION_DEBUG("\ttransport_protocol_label[%d] : %x \n", i, transport_protocol_label[i]);
    }
    SECTION_DEBUG("\n");
}

void ApplicationDescriptor::updateDescriptorLength()
{
    descriptor_length =
            1 + (application_profiles_length>0 ? 5:0) + 2 + transport_protocol_label_length;
}

void ApplicationDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    rw->Write_On_Buffer(application_profiles_length, 8);
    for(int i=application_profiles_length;i>0;i-=5)
    {
        rw->Write_On_Buffer(application_profiles.applicaton_profile, 16);
        rw->Write_On_Buffer(application_profiles.version_major, 8);
        rw->Write_On_Buffer(application_profiles.version_minor, 8);
        rw->Write_On_Buffer(application_profiles.version_micro, 8);
    }
    rw->Write_On_Buffer(service_bound_flag, 1);
    rw->Write_On_Buffer(visibility, 2);
    rw->Write_On_Buffer(0x1f, 5);
    rw->Write_On_Buffer(application_priority, 8);

    for(int i=0;i<transport_protocol_label_length;i++)
    {
        rw->Write_On_Buffer(transport_protocol_label[i], 8);
    }
}

} // end of hybridcast namespace

} // end of sedec namespace


