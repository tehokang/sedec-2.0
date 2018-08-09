// application_usage_descriptor.cpp: implementation of the ApplicationUsageDescriptor class.
//
//////////////////////////////////////////////////////////////////////
#include "section_common.h"
#include "descriptors/dvb/application_usage_descriptor.h"
#include "bit_readwriter.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace sedec
{

namespace dvb
{

ApplicationUsageDescriptor::ApplicationUsageDescriptor()
{
    descriptor_tag = APPLICATION_USAGE_DESCRIPTOR;
    descriptor_length = 0;
    usage_type = 0;
}

ApplicationUsageDescriptor::ApplicationUsageDescriptor(BitReadWriter *rw) : Descriptor(rw)
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

void ApplicationUsageDescriptor::calcLength()
{
    descriptor_length = 1;
}

void ApplicationUsageDescriptor::WriteDescriptor(BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    rw->Write_On_Buffer(usage_type, 8);
}

} // end of dvb namespace

} // end of sedec namespace
