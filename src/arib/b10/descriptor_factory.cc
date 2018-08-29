#include "base/macro.h"
#include "descriptor_factory.h"
#include "descriptors/descriptor.h"

namespace sedec
{

using namespace arib::b10;

Descriptor* DescriptorFactory::CreateDescriptor(base::BitReadWriter *rw)
{
    int descriptor_tag = (*(rw->GetCurrentBuffer()) & 0xff);

    switch(descriptor_tag)
    {
        default:
            return new UnknownDescriptor(rw);
    }
}

} // end of sedec namespace
