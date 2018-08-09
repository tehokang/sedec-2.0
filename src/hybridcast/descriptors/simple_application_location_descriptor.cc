// simple_application_location_descriptor.cpp: implementation of the SimpleApplicationLocationDescriptor class.
//
//////////////////////////////////////////////////////////////////////
#include "section_common.h"
#include "descriptors/hybridcast/simple_application_location_descriptor.h"
#include "bit_readwriter.h"
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace sedec
{

namespace hybridcast
{

SimpleApplicationLocationDescriptor::SimpleApplicationLocationDescriptor()
{
    descriptor_tag = SIMPLE_APPLICATION_LOCATION_DESCRIPTOR;
    descriptor_length = 0;
    memset(initial_path_bytes, 0x00, sizeof(initial_path_bytes));
}

SimpleApplicationLocationDescriptor::SimpleApplicationLocationDescriptor(BitReadWriter *rw) : Descriptor(rw)
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
    SECTION_DEBUG("\tdescriptor_tag : 0x%02x (simple_application_location_descriptor)\n", descriptor_tag);
    SECTION_DEBUG("\tdescriptor_length : 0x%x \n", descriptor_length);
    SECTION_DEBUG("\tinitial_path_bytes : %s \n", initial_path_bytes);
    SECTION_DEBUG("\n");
}

void SimpleApplicationLocationDescriptor::calcLength()
{
    descriptor_length = strlen((char*)initial_path_bytes);
}

void SimpleApplicationLocationDescriptor::WriteDescriptor(BitReadWriter *rw)
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

} // end of hybridcast namespace

} // end of sedec namespace
