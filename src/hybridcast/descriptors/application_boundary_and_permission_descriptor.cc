#include <string.h>
#include "base/macro.h"
#include "descriptors/application_boundary_and_permission_descriptor.h"

namespace sedec
{

namespace hybridcast
{

ApplicationBoundaryAndPermissionDescriptor::ApplicationBoundaryAndPermissionDescriptor()
{
    descriptor_tag = 0x30;
    descriptor_length = 0;
}

ApplicationBoundaryAndPermissionDescriptor::ApplicationBoundaryAndPermissionDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    for(int i=descriptor_length;i>0;)
    {
        ApplicationBoundaryAndPermission *_info = new ApplicationBoundaryAndPermission;
        _info->permission_bitmap_count = 0;
        _info->permission_bitmaps.clear();
        _info->managed_URL_count = 0;
        _info->managed_urls.clear();

        _info->permission_bitmap_count = rw->Read_On_Buffer(8); i-=8;

        for(int j=0;j<_info->permission_bitmap_count;j++)
        {
            uint16_t bitmap = rw->Read_On_Buffer(16); i-=16;
            _info->permission_bitmaps.push_back(bitmap);
        }

        _info->managed_URL_count = rw->Read_On_Buffer(8); i-=8;

        for(int j=0;j<_info->managed_URL_count;)
        {
            ManagedURL *_url = new ManagedURL;
            _url->managed_URL_length = 0;
            memset(_url->managed_URL_byte, 0x00, sizeof(_url->managed_URL_byte));

            _url->managed_URL_length = rw->Read_On_Buffer(8); i-=8;

            for(int k=0;k<_url->managed_URL_length;k++)
            {
                _url->managed_URL_byte[k] = rw->Read_On_Buffer(8); i-=8;
            }

            _info->managed_urls.push_back(_url);
        }

        infos.push_back(_info);
    }
}

ApplicationBoundaryAndPermissionDescriptor::~ApplicationBoundaryAndPermissionDescriptor()
{
    for (std::list<ApplicationBoundaryAndPermission *>::iterator it=infos.begin();
        it != infos.end(); ++it)
    {
        for (std::list<ManagedURL *>::iterator jt=(*it)->managed_urls.begin();
            jt != (*it)->managed_urls.end(); ++jt)
        {
            delete (*jt);
        }
        delete (*it);
    }
    infos.clear();
}

void ApplicationBoundaryAndPermissionDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    Descriptor::PrintDescriptor("ApplicationBoundaryAndPermissionDescriptor");

    for (std::list<ApplicationBoundaryAndPermission *>::iterator it=infos.begin();
            it != infos.end(); ++it)
    {
        SECTION_DEBUG("\tpermission_bitmap_count : 0x%x \n", (*it)->permission_bitmap_count);
        for (std::list<uint16_t>::iterator jt=(*it)->permission_bitmaps.begin();
            jt != (*it)->permission_bitmaps.end(); ++jt)
        {
            SECTION_DEBUG("\tpermission_bitmap : %hd \n", (*jt));
        }

        SECTION_DEBUG("\tmanaged_URL_count : 0x%x \n", (*it)->managed_URL_count);

        for (std::list<ManagedURL *>::iterator jt=(*it)->managed_urls.begin();
            jt != (*it)->managed_urls.end(); ++jt)
        {
            SECTION_DEBUG("\tmanaged_URL_length : 0x%x \n", (*jt)->managed_URL_length);
            SECTION_DEBUG("\tmanaged_URL_byte : %s \n", (*jt)->managed_URL_byte);
        }
    }
    SECTION_DEBUG("\n");
}

void ApplicationBoundaryAndPermissionDescriptor::updateDescriptorLength()
{
    int len = 0;

    for (std::list<ApplicationBoundaryAndPermission *>::iterator it=infos.begin();
        it != infos.end(); ++it)
    {
        len += 1 + ( (*it)->permission_bitmap_count * 2 ) + 1;

        for (std::list<ManagedURL *>::iterator jt=(*it)->managed_urls.begin();
            jt != (*it)->managed_urls.end(); ++jt)
        {
            len += 1 + (*jt)->managed_URL_length;
        }
    }

    descriptor_length = len;
}

void ApplicationBoundaryAndPermissionDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    for (std::list<ApplicationBoundaryAndPermission *>::iterator it=infos.begin();
        it != infos.end(); ++it)
    {
        rw->Write_On_Buffer((*it)->permission_bitmap_count, 8);

        for (std::list<uint16_t>::iterator jt=(*it)->permission_bitmaps.begin();
            jt != (*it)->permission_bitmaps.end(); ++jt)
        {
            rw->Write_On_Buffer((*jt), 16);
        }

        rw->Write_On_Buffer((*it)->managed_URL_count, 8);

        for (std::list<ManagedURL *>::iterator jt=(*it)->managed_urls.begin();
            jt != (*it)->managed_urls.end(); ++jt)
        {
            rw->Write_On_Buffer((*jt)->managed_URL_length, 8);

            for(int i=0;i<(*jt)->managed_URL_length;i++)
            {
                rw->Write_On_Buffer((*jt)->managed_URL_byte[i], 8);
            }
        }
    }
}

} // end of hybridcast namespace

} // end of sedec namespace


