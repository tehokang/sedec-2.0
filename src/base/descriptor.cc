#include "macro.h"
#include "descriptor.h"
#include "bit_readwriter.h"

namespace sedec
{

namespace base
{

Descriptor::Descriptor()
{
    descriptor_tag = 0xff;
    descriptor_length = 0;
}

Descriptor::Descriptor(BitReadWriter *rw)
{
    descriptor_tag = rw->Read_On_Buffer(8);
    descriptor_length = rw->Read_On_Buffer(8);
}

Descriptor::~Descriptor()
{

}

int Descriptor::GetDescriptorTag()
{
    return descriptor_tag;
}

int Descriptor::GetDescriptorLength()
{
    updateDescriptorLength();
    return descriptor_length + 2;
}

void Descriptor::WriteDescriptor(BitReadWriter* rw)
{
    rw->Write_On_Buffer(descriptor_tag, 8);
    rw->Write_On_Buffer(descriptor_length, 8);
}

void Descriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    SECTION_DEBUG("\tdescriptor_tag : 0x%02x (unknown descriptor) \n", descriptor_tag);
    SECTION_DEBUG("\tdescriptor_length : 0x%x \n", descriptor_length);
    SECTION_DEBUG("\n");
}

UnknownDescriptor::UnknownDescriptor()
{

}

UnknownDescriptor::UnknownDescriptor(BitReadWriter *rw) : Descriptor(rw)
{
    rw->Skip_On_Buffer(descriptor_length*8);
}

UnknownDescriptor::~UnknownDescriptor()
{

}

} // end of base namespace

} // end of sedec namespace