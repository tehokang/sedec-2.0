#include "base/macro.h"
#include "descriptors/application_usage_descriptor.h"

namespace sedec
{

namespace hybridcast
{

ApplicationUsageDescriptor::ApplicationUsageDescriptor()
{
    descriptor_tag = 0x16;
    descriptor_length = 0;
    usage_type = 0;
}

ApplicationUsageDescriptor::ApplicationUsageDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    usage_type = rw->Read_On_Buffer(8);
}

ApplicationUsageDescriptor::~ApplicationUsageDescriptor()
{

}

void ApplicationUsageDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    SECTION_DEBUG("\tdescriptor_tag : 0x%02x (application_usage_descriptor)\n", descriptor_tag);
    SECTION_DEBUG("\tdescriptor_length : 0x%x \n", descriptor_length);
    SECTION_DEBUG("\tusage_type : 0x%x \n", usage_type);
    SECTION_DEBUG("\n");
}

void ApplicationUsageDescriptor::updateDescriptorLength()
{
    descriptor_length = 1;
}

void ApplicationUsageDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    rw->Write_On_Buffer(usage_type, 8);
}

} // end of hybridcast namespace

} // end of sedec namespace
