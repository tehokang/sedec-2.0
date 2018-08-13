#include "base/macro.h"
#include "base/bit_readwriter.h"
#include "descriptors/descriptor.h"

namespace sedec
{

namespace dvb
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

} // end of base namespace

} // end of sedec namespace