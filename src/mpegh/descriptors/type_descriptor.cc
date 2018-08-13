#include <stdlib.h>
#include <string.h>

#include "base/macro.h"
#include "descriptors/type_descriptor.h"

namespace sedec
{

namespace mpegh
{

TypeDescriptor::TypeDescriptor()
{
    descriptor_tag = 0x801c;
    descriptor_length = 0;
    memset(text_char, 0x00, sizeof(text_char));
}

TypeDescriptor::TypeDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    memset(text_char, 0x00, sizeof(text_char));

    if( 0<descriptor_length )
    {
        for(int i=0;i<descriptor_length;i++)
        {
            text_char[i] = rw->Read_On_Buffer(8);
        }
    }
}

TypeDescriptor::~TypeDescriptor()
{

}

void TypeDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    SECTION_DEBUG("\tdescriptor_tag : 0x%04x (type_descriptor)\n", descriptor_tag);
    SECTION_DEBUG("\tdescriptor_length : 0x%x \n", descriptor_length);
    SECTION_DEBUG("\ttext_char : %s \n", text_char);
    SECTION_DEBUG("\n");
}

void TypeDescriptor::calcLength()
{
    descriptor_length = strlen((char*)text_char);
}

void TypeDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    if( 0<descriptor_length )
    {
        for( int i=0; i<descriptor_length; i++ )
        {
            rw->Write_On_Buffer(text_char[i], 8);
        }
    }
}

} // end of mpegh namespace

} // end of sedec namespace