#include <stdlib.h>
#include <string.h>

#include "base/macro.h"
#include "base/bit_readwriter.h"
#include "descriptors/expire_descriptor.h"

namespace sedec
{

namespace mpegh
{

ExpireDescriptor::ExpireDescriptor()
{
    descriptor_tag = 0x801e;
    descriptor_length = 0;

    time_mode = 0x00;
    UTC_time = 0;
    UTC_time = 0;
}

ExpireDescriptor::ExpireDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    time_mode = rw->Read_On_Buffer(8);

    if ( time_mode == 0x01 )
    {
        UTC_time = rw->Read_On_Buffer(64);
    }
    else if ( time_mode == 0x04 )
    {
        rw->Skip_On_Buffer(8);
        passed_seconds = rw->Read_On_Buffer(32);
    }
}

ExpireDescriptor::~ExpireDescriptor()
{

}

void ExpireDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    SECTION_DEBUG("\tdescriptor_tag : 0x%04x (expire_descriptor)\n", descriptor_tag);
    SECTION_DEBUG("\tdescriptor_length : 0x%x \n", descriptor_length);

    SECTION_DEBUG("\ttime_mode : 0x%x \n", time_mode);

    if ( time_mode == 0x01 )
    {
        SECTION_DEBUG("\tUTC_time : %lf \n", UTC_time);
    }
    else if ( time_mode == 0x04 )
    {
        SECTION_DEBUG("\tpassed_seconds : %d \n", passed_seconds);
    }
    SECTION_DEBUG("\n");
}

void ExpireDescriptor::updateDescriptorLength()
{
    if ( time_mode == 0x01 )
    {
        descriptor_length = 1 + 8;
    }
    else if ( time_mode == 0x04 )
    {
        descriptor_length = 1 + 5;
    }
}

void ExpireDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    if( 0 < descriptor_length )
    {
        rw->Write_On_Buffer(time_mode, 8);

        if ( time_mode == 0x01 )
        {
            rw->Write_On_Buffer(UTC_time, 64);
        }
        else if ( time_mode == 0x04 )
        {
            rw->Write_On_Buffer(0x0f, 8);
            rw->Write_On_Buffer(passed_seconds, 32);
        }
    }
}

} // end of mpegh namespace

} // end of sedec namespace
