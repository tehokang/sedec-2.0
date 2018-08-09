// transport_protocol_descriptor.cpp: implementation of the ConnectionRequirementDescriptor class.
//
//////////////////////////////////////////////////////////////////////
#include "section_common.h"
#include "descriptors/dvb/connection_requirement_descriptor.h"
#include "bit_readwriter.h"


//#include <stdlib.h>
//#include <string.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace sedec
{


namespace dvb
{

ConnectionRequirementDescriptor::ConnectionRequirementDescriptor()
{
    descriptor_tag = CONNECTION_REQUIREMENT_DESCRIPTOR;
    descriptor_length = 0;

    IP_connection_requirement_flag = false;
}

ConnectionRequirementDescriptor::ConnectionRequirementDescriptor(BitReadWriter *rw) : Descriptor(rw)
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
    SECTION_DEBUG("\tdescriptor_tag : 0x%02x (connection_requirement_descriptor)\n", descriptor_tag);
    SECTION_DEBUG("\tdescriptor_length : 0x%x \n", descriptor_length);
    SECTION_DEBUG("\tIP_connection_requirement_flag : %x \n", IP_connection_requirement_flag);

    SECTION_DEBUG("\n");
}

void ConnectionRequirementDescriptor::calcLength()
{
    descriptor_length = 3;
}

void ConnectionRequirementDescriptor::WriteDescriptor(BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    rw->Write_On_Buffer(0x7f, 7);
    rw->Write_On_Buffer(IP_connection_requirement_flag, 1);
}

} // end of dvb namespace

} // end of sedec namespace


