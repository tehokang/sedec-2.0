#include <string.h>
#include "base/macro.h"
#include "descriptors/autostart_priority_descriptor.h"

namespace sedec
{

namespace mpegh
{

AutostartPriorityDescriptor::AutostartPriorityDescriptor()
{
    descriptor_tag = 0X802D;
    descriptor_length = 0;
    autostart_priority = 0;
}

AutostartPriorityDescriptor::AutostartPriorityDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    autostart_priority = rw->Read_On_Buffer(8);
}

AutostartPriorityDescriptor::~AutostartPriorityDescriptor()
{

}

void AutostartPriorityDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    SECTION_DEBUG("\tdescriptor_tag : 0x%04x (autostart_priority_descriptor)\n", descriptor_tag);
    SECTION_DEBUG("\tdescriptor_length : 0x%x \n", descriptor_length);
    SECTION_DEBUG("\tautostart_priority : 0x%x \n", autostart_priority);
    SECTION_DEBUG("\n");
}

void AutostartPriorityDescriptor::updateDescriptorLength()
{
    descriptor_length = 1;
}

void AutostartPriorityDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    rw->Write_On_Buffer(autostart_priority, 8);
}

} // end of mh namespace

} // end of sedec namespace


