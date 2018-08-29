#include "base/macro.h"
#include "descriptors/descriptor.h"

namespace sedec
{

namespace arib::b24
{

Descriptor::Descriptor()
{
    descriptor_tag = 0xff;
    descriptor_length = 0;
}

Descriptor::Descriptor(base::BitReadWriter *rw)
{
    descriptor_tag = rw->Read_On_Buffer(8);
    descriptor_length = rw->Read_On_Buffer(8);
}

Descriptor::~Descriptor()
{

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
    SECTION_DEBUG("\tdescriptor_tag : 0x%02x (unknown descriptor) \n", descriptor_tag);
    SECTION_DEBUG("\tdescriptor_length : 0x%x \n", descriptor_length);
    SECTION_DEBUG("\n");
}

} // end of hybridcast namespace

} // end of sedec namespace
