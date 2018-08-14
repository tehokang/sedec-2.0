#include <stdlib.h>
#include <string.h>

#include "base/macro.h"
#include "descriptors/simple_application_location_descriptor.h"

namespace sedec
{

namespace dvb
{

SimpleApplicationLocationDescriptor::SimpleApplicationLocationDescriptor()
{
    descriptor_tag = 0x15;
    descriptor_length = 0;
    memset(initial_path_bytes, 0x00, sizeof(initial_path_bytes));
}

SimpleApplicationLocationDescriptor::SimpleApplicationLocationDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    memset(initial_path_bytes, 0x00, sizeof(initial_path_bytes));

    if( 0<descriptor_length )
    {
        for(int i=0;i<descriptor_length;i++)
        {
            initial_path_bytes[i] = rw->Read_On_Buffer(8);
        }
    }
}

SimpleApplicationLocationDescriptor::~SimpleApplicationLocationDescriptor()
{

}

void SimpleApplicationLocationDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    Descriptor::PrintDescriptor();
    SECTION_DEBUG("\tinitial_path_bytes : %s \n", initial_path_bytes);
    SECTION_DEBUG("\n");
}

void SimpleApplicationLocationDescriptor::updateDescriptorLength()
{
    descriptor_length = strlen((char*)initial_path_bytes);
}

void SimpleApplicationLocationDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    if( 0<descriptor_length )
    {
        for( int i=0; i<descriptor_length; i++ )
        {
            rw->Write_On_Buffer(initial_path_bytes[i], 8);
        }
    }
}

} // end of dvb namespace

} // end of sedec namespace
