#include <stdlib.h>
#include <string.h>

#include "base/macro.h"
#include "base/bit_readwriter.h"
#include "descriptors/compression_type_descriptor.h"

namespace sedec
{

namespace mpegh
{

CompressionTypeDescriptor::CompressionTypeDescriptor()
{
    descriptor_tag = 0x801f;
    descriptor_length = 0;
    compression_type = 0;
    original_size = 0;
}

CompressionTypeDescriptor::CompressionTypeDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    compression_type = rw->Read_On_Buffer(8);
    original_size = rw->Read_On_Buffer(32);
}

CompressionTypeDescriptor::~CompressionTypeDescriptor()
{

}

void CompressionTypeDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    Descriptor::PrintDescriptor("CompressionTypeDescriptor");

    SECTION_DEBUG("\tcompression_type : 0x%x \n", compression_type);
    SECTION_DEBUG("\toriginal_size : 0x%x \n", original_size);
    SECTION_DEBUG("\n");
}

void CompressionTypeDescriptor::updateDescriptorLength()
{
    descriptor_length = 5;
}

void CompressionTypeDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    if( 0 < descriptor_length )
    {
        rw->Write_On_Buffer(compression_type, 8);
        rw->Write_On_Buffer(original_size, 32);
    }
}

} // end of mpegh namespace

} // end of sedec namespace
