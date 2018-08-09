
/** **********************************************************************************************************
	@file 		autostart_priority_descriptor.cpp

	@date		2018/01/19
	@author		Humax SW Group
	@breif

    It is related in IPTVFJ STD-0010 version 2.0

*********************************************************************************************************** */
    
#include "section_common.h"
#include "descriptors/hybridcast/autostart_priority_descriptor.h"
#include "bit_readwriter.h"
#include <string.h>

namespace sedec
{

namespace hybridcast
{

AutostartPriorityDescriptor::AutostartPriorityDescriptor()
{
    descriptor_tag = AUTOSTART_PRIORITY_DESCRIPTOR;
    descriptor_length = 0;
    autostart_priority = 0;
}

AutostartPriorityDescriptor::AutostartPriorityDescriptor(BitReadWriter *rw) : Descriptor(rw)
{
    autostart_priority = rw->Read_On_Buffer(8);
}

AutostartPriorityDescriptor::~AutostartPriorityDescriptor()
{

}

void AutostartPriorityDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    SECTION_DEBUG("\tdescriptor_tag : 0x%02x (autostart_priority_descriptor)\n", descriptor_tag);
    SECTION_DEBUG("\tdescriptor_length : 0x%x \n", descriptor_length);
    SECTION_DEBUG("\tautostart_priority : 0x%x \n", autostart_priority);
    SECTION_DEBUG("\n");
}

void AutostartPriorityDescriptor::calcLength()
{
    descriptor_length = 1;
}

void AutostartPriorityDescriptor::WriteDescriptor(BitReadWriter *rw)
{   
    Descriptor::WriteDescriptor(rw);

    rw->Write_On_Buffer(autostart_priority, 8);    
}

} // end of hybridcast namespace

} // end of sedec namespace


