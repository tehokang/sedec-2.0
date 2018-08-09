// simple_application_boundary_descriptor.cpp: implementation of the SimpleApplicationBoundaryDescriptor class.
//
//////////////////////////////////////////////////////////////////////
#include "section_common.h"
#include "descriptors/hybridcast/simple_application_boundary_descriptor.h"
#include "bit_readwriter.h"
#include <string.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace sedec
{

namespace hybridcast
{

SimpleApplicationBoundaryDescriptor::SimpleApplicationBoundaryDescriptor()
{
    descriptor_tag = SIMPLE_APPLICATION_BOUNDARY_DESCRIPTOR;
    descriptor_length = 0;

    boundary_extension_count = 0;
    memset(boundary_extension_length, 0x00, sizeof(boundary_extension_length));
    memset(boundary_extension_byte, 0x00, sizeof(boundary_extension_byte));
}

SimpleApplicationBoundaryDescriptor::SimpleApplicationBoundaryDescriptor(BitReadWriter *rw) : Descriptor(rw)
{
    boundary_extension_count = 0;
    memset(boundary_extension_length, 0x00, sizeof(boundary_extension_length));
    memset(boundary_extension_byte, 0x00, sizeof(boundary_extension_byte));

    boundary_extension_count = rw->Read_On_Buffer(8);

    for(int i=0;i<boundary_extension_count;i++)
    {
        boundary_extension_length[i] = rw->Read_On_Buffer(8);
        for(int j=0;j<boundary_extension_length[i];j++)
        {
            boundary_extension_byte[i][j] = rw->Read_On_Buffer(8);
        }
    }
}

SimpleApplicationBoundaryDescriptor::~SimpleApplicationBoundaryDescriptor()
{

}

void SimpleApplicationBoundaryDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    SECTION_DEBUG("\tdescriptor_tag : 0x%02x (simple_application_boundary_descriptor)\n", descriptor_tag);
    SECTION_DEBUG("\tdescriptor_length : 0x%x \n", descriptor_length);
    SECTION_DEBUG("\tboundary_extension_count : 0x%x \n", boundary_extension_count);

    for(int i=0;i<boundary_extension_count;i++)
    {
        SECTION_DEBUG("\tboundary_extension_length[%d] = 0x%x \n", i, boundary_extension_length[i]);
        SECTION_DEBUG("\tboundary_extenstion_byte[%d] = %s \n", i, boundary_extension_byte[i]);
    }
    SECTION_DEBUG("\n");
}

void SimpleApplicationBoundaryDescriptor::calcLength()
{
    // boundary_extension_count
    descriptor_length=1;
    for(int i=0;i<boundary_extension_count;i++)
    {
        // boundary_extension_length
        descriptor_length+=1;
        // boundary_extension_byte
        descriptor_length+=boundary_extension_length[i];
    }
}

void SimpleApplicationBoundaryDescriptor::WriteDescriptor(BitReadWriter *rw)
{    
    Descriptor::WriteDescriptor(rw);

    rw->Write_On_Buffer(boundary_extension_count, 8);
    for(int i=0;i<boundary_extension_count;i++)
    {
        rw->Write_On_Buffer(boundary_extension_length[i], 8);
        for(int j=0;j<boundary_extension_length[i];j++)
        {
            rw->Write_On_Buffer(boundary_extension_byte[i][j], 8);
        }
    }
}

} // end of hybridcast namespace

} // end of sedec namespace



