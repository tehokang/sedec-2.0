#include "base/macro.h"
#include "descriptors/connection_requirement_descriptor.h"

namespace sedec
{


namespace dvb
{

ConnectionRequirementDescriptor::ConnectionRequirementDescriptor()
{
    descriptor_tag = 0x72;
    descriptor_length = 0;

    IP_connection_requirement_flag = false;
}

ConnectionRequirementDescriptor::ConnectionRequirementDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    rw->Read_On_Buffer(7);
    IP_connection_requirement_flag = rw->Read_On_Buffer(1);

    for (int i=0; i<descriptor_length-1;i++)
        rw->Read_On_Buffer(8);
}

ConnectionRequirementDescriptor::~ConnectionRequirementDescriptor()
{

}

void ConnectionRequirementDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    Descriptor::PrintDescriptor("ConnectionRequirementDescriptor");

    SECTION_DEBUG("\tIP_connection_requirement_flag : %x \n", IP_connection_requirement_flag);

    SECTION_DEBUG("\n");
}

void ConnectionRequirementDescriptor::updateDescriptorLength()
{
    descriptor_length = 3;
}

void ConnectionRequirementDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    rw->Write_On_Buffer(0x7f, 7);
    rw->Write_On_Buffer(IP_connection_requirement_flag, 1);
}

} // end of dvb namespace

} // end of sedec namespace


