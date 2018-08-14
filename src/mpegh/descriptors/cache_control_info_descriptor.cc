#include <string.h>
#include "base/macro.h"
#include "descriptors/cache_control_info_descriptor.h"

namespace sedec
{

namespace mpegh
{

CacheControlInfoDescriptor::CacheControlInfoDescriptor()
{
    descriptor_tag = 0x802e;
    descriptor_length = 0;
    application_size = 0;
    cache_priority = 0;
    package_flag = false;
    application_version = 0;
    expire_date = 0;
}

CacheControlInfoDescriptor::CacheControlInfoDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    application_size = rw->Read_On_Buffer(16);
    cache_priority = rw->Read_On_Buffer(8);
    package_flag = rw->Read_On_Buffer(1);
    application_version = rw->Read_On_Buffer(7);
    expire_date = rw->Read_On_Buffer(16);
}

CacheControlInfoDescriptor::~CacheControlInfoDescriptor()
{

}

void CacheControlInfoDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    Descriptor::PrintDescriptor("CacheControlInfoDescriptor");

    SECTION_DEBUG("\tapplication_size : 0x%x \n", application_size);
    SECTION_DEBUG("\tcache_priority : 0x%x \n", cache_priority);
    SECTION_DEBUG("\tpackage_flag : 0x%x \n", package_flag);
    SECTION_DEBUG("\tapplication_version : 0x%x \n", application_version);
    SECTION_DEBUG("\texpire_date : 0x%x \n", expire_date);
    SECTION_DEBUG("\n");
}

void CacheControlInfoDescriptor::updateDescriptorLength()
{
    descriptor_length = 6;
}

void CacheControlInfoDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    rw->Write_On_Buffer(application_size, 16);
    rw->Write_On_Buffer(cache_priority, 8);
    rw->Write_On_Buffer(package_flag, 1);
    rw->Write_On_Buffer(application_version, 7);
    rw->Write_On_Buffer(expire_date, 16);
}

} // end of mh namespace

} // end of sedec namespace


