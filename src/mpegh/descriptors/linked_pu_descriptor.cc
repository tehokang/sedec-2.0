#include <stdlib.h>
#include <string.h>

#include "base/macro.h"
#include "descriptors/linked_pu_descriptor.h"

namespace sedec
{

namespace mpegh
{

LinkedPuDescriptor::LinkedPuDescriptor()
{
    descriptor_tag = 0x8030;
    descriptor_length = 0;
    num_of_linked_PU = 0;
    memset(linked_PU_tag, 0x00, sizeof(linked_PU_tag));
}

LinkedPuDescriptor::LinkedPuDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    memset(linked_PU_tag, 0x00, sizeof(linked_PU_tag));

    if( 0<descriptor_length )
    {
        num_of_linked_PU = rw->Read_On_Buffer(8);

        for(int i=0;i<num_of_linked_PU;i++)
        {
            linked_PU_tag[i] = rw->Read_On_Buffer(8);
        }
    }
}

LinkedPuDescriptor::~LinkedPuDescriptor()
{

}

void LinkedPuDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    Descriptor::PrintDescriptor("LinkedPuDescriptor");

    SECTION_DEBUG("\tnum_of_linked_PU : 0x%x \n",num_of_linked_PU);
    SECTION_DEBUG("\tlinked_PU_tag : %s \n",linked_PU_tag);

    SECTION_DEBUG("\n");
}

void LinkedPuDescriptor::updateDescriptorLength()
{
    descriptor_length = 1 + strlen((char*)linked_PU_tag);
}

void LinkedPuDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    if( 0<descriptor_length )
    {
        rw->Write_On_Buffer(num_of_linked_PU, 8);

        for( int i=0; i<num_of_linked_PU; i++ )
        {
            rw->Write_On_Buffer(linked_PU_tag[i], 8);
        }
    }
}

} // end of mpegh namespace

} // end of sedec namespace
