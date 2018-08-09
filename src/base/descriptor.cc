#include "macro.h"
#include "descriptor.h"
#include "bit_readwriter.h"

namespace sedec
{

namespace base
{

Descriptor::Descriptor()
{
    descriptor_tag = UNKNOWN_DESCRIPTOR;
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
    calcLength();
    return descriptor_length + DESCRIPTOR_HEADER_LENGTH;
}

void Descriptor::WriteDescriptor(BitReadWriter* rw)
{
    calcLength();
    rw->Write_On_Buffer(descriptor_tag, 8);
    rw->Write_On_Buffer(descriptor_length, 8);
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

void UnknownDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    SECTION_DEBUG("\tdescriptor_tag : 0x%02x (unknown descriptor) \n", descriptor_tag);
    SECTION_DEBUG("\tdescriptor_length : 0x%x \n", descriptor_length);
    SECTION_DEBUG("\n");
}

} // end of base namespace

} // end of sedec namespace