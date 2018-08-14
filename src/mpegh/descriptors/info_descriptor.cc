#include <stdlib.h>
#include <string.h>

#include "base/macro.h"
#include "base/bit_readwriter.h"
#include "descriptors/info_descriptor.h"

namespace sedec
{

namespace mpegh
{

InfoDescriptor::InfoDescriptor()
{
    descriptor_tag = 0x801d;
    descriptor_length = 0;
    memset(ISO_639_language_code, 0x00, sizeof(ISO_639_language_code));
    memset(text_char, 0x00, sizeof(text_char));
}

InfoDescriptor::InfoDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    memset(ISO_639_language_code, 0x00, sizeof(ISO_639_language_code));
    memset(text_char, 0x00, sizeof(text_char));

    if( 0<descriptor_length )
    {
        ISO_639_language_code[0] = rw->Read_On_Buffer(8);
        ISO_639_language_code[1] = rw->Read_On_Buffer(8);
        ISO_639_language_code[2] = rw->Read_On_Buffer(8);

        for(int i=0;i<(descriptor_length-3);i++)
        {
            text_char[i] = rw->Read_On_Buffer(8);
        }
    }
}

InfoDescriptor::~InfoDescriptor()
{

}

void InfoDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    Descriptor::PrintDescriptor("InfoDescriptor");

    SECTION_DEBUG("\tISO_639_languahe_code[0] : 0x%x(%c) \n",
                ISO_639_language_code[0],ISO_639_language_code[0]);
    SECTION_DEBUG("\tISO_639_languahe_code[1] : 0x%x(%c) \n",
                ISO_639_language_code[1],ISO_639_language_code[1]);
    SECTION_DEBUG("\tISO_639_languahe_code[2] : 0x%x(%c) \n",
                ISO_639_language_code[2],ISO_639_language_code[2]);

    SECTION_DEBUG("\ttext_char : %s \n", text_char);
    SECTION_DEBUG("\n");
}

void InfoDescriptor::updateDescriptorLength()
{
    descriptor_length = 3 + strlen((char*)text_char);
}

void InfoDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    if( 0<descriptor_length )
    {
        rw->Write_On_Buffer(ISO_639_language_code[0], 8);
        rw->Write_On_Buffer(ISO_639_language_code[1], 8);
        rw->Write_On_Buffer(ISO_639_language_code[2], 8);

        for( int i=0; i<(descriptor_length-3); i++ )
        {
            rw->Write_On_Buffer(text_char[i], 8);
        }
    }
}

} // end of mpegh namespace

} // end of sedec namespace
