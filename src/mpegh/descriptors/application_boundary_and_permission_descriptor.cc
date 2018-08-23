#include <string.h>
#include "base/macro.h"
#include "descriptors/application_boundary_and_permission_descriptor.h"

namespace sedec
{

namespace mpegh
{

ApplicationBoundaryAndPermissionDescriptor::ApplicationBoundaryAndPermissionDescriptor()
{
    descriptor_tag = 0x802c;
    descriptor_length = 0;
}

ApplicationBoundaryAndPermissionDescriptor::ApplicationBoundaryAndPermissionDescriptor(
        base::BitReadWriter *rw) : Descriptor(rw)
{
    if ( 0 < descriptor_length )
    {
        permission_bitmap_count = rw->Read_On_Buffer(8);

        for ( int i=0; i<permission_bitmap_count; i++ )
        {
            permission_bitmap[i] = rw->Read_On_Buffer(16);
        }

        managed_URL_count = rw->Read_On_Buffer(8);
        for ( int i=0; i<managed_URL_count; i++ )
        {
            managed_URL_length[i] = rw->Read_On_Buffer(8);
            for ( int j=0; i<managed_URL_length[i]; j++ )
            {
                managed_URL_byte[i][j] = rw->Read_On_Buffer(8);
            }
        }
    }
}

ApplicationBoundaryAndPermissionDescriptor::~ApplicationBoundaryAndPermissionDescriptor()
{
}

void ApplicationBoundaryAndPermissionDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    Descriptor::PrintDescriptor("ApplicationBoundaryAndPermissionDescriptor");

    if ( 0 < descriptor_length ) {
        SECTION_DEBUG("\tpermission_bitmap_count : 0x%x \n", permission_bitmap_count);

        for ( int i=0; i<permission_bitmap_count; i++ ) {
            SECTION_DEBUG("\tpermission_bitmap[%d] : 0x%x \n", i, permission_bitmap[i]);
        }

        SECTION_DEBUG("\tmanaged_URL_count : 0x%x \n", managed_URL_count);

        for ( int i=0;i<managed_URL_count; i++ ) {
            SECTION_DEBUG("\tmanaged_URL_count : 0x%x \n", managed_URL_length[i]);
            SECTION_DEBUG("\tmanaged_URL_byte : %s \n", managed_URL_byte[i]);
        }
    }

    SECTION_DEBUG("\n");
}

void ApplicationBoundaryAndPermissionDescriptor::updateDescriptorLength()
{
    descriptor_length = 1 + (permission_bitmap_count * 2) + 1;

    for ( int i=0; i<managed_URL_count; i++ ) {
        descriptor_length += 1 + managed_URL_length[i];
    }
}

void ApplicationBoundaryAndPermissionDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    if ( 0 < descriptor_length ) {
        rw->Write_On_Buffer(permission_bitmap_count, 8);

        for ( int i=0; i<permission_bitmap_count; i++ ) {
            rw->Write_On_Buffer(permission_bitmap[i], 16);
        }

        rw->Write_On_Buffer(managed_URL_count, 8);
        for ( int i=0;i<managed_URL_count; i++ ) {
            rw->Write_On_Buffer(managed_URL_length[i], 8);

            for ( int j=0; i<managed_URL_length[i]; j++ ) {
                rw->Write_On_Buffer(managed_URL_byte[i][j], 8);
            }
        }
    }
}

} // end of mh namespace

} // end of sedec namespace


