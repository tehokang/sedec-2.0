#include "base/macro.h"
#include "descriptors/descriptor.h"

namespace sedec
{

namespace arib::b39
{

Descriptor::Descriptor()
{
    descriptor_tag = 0xffff;
    descriptor_length = 0;
}

Descriptor::Descriptor(base::BitReadWriter *rw)
{
    descriptor_tag = rw->Read_On_Buffer(16);
    descriptor_length = rw->Read_On_Buffer(8);
}

Descriptor::~Descriptor()
{

}

int Descriptor::GetDescriptorLength()
{
    updateDescriptorLength();
    return descriptor_length + 3;
}

void Descriptor::WriteDescriptor(base::BitReadWriter* rw)
{
    rw->Write_On_Buffer(descriptor_tag, 16);
    rw->Write_On_Buffer(descriptor_length, 8);
}

UnknownDescriptor::UnknownDescriptor()
{

}

UnknownDescriptor::UnknownDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    rw->Skip_On_Buffer(descriptor_length*8);
}

UnknownDescriptor::~UnknownDescriptor()
{

}

void UnknownDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    SECTION_DEBUG("\tdescriptor_tag : 0x%04x (unknown descriptor) \n", descriptor_tag);
    SECTION_DEBUG("\tdescriptor_length : 0x%x \n", descriptor_length);
    SECTION_DEBUG("\n");
}


} // end of mh namespace

} // end of sedec namespace
