#include <string.h>
#include "base/macro.h"
#include "descriptors/randomized_latency_descriptor.h"

namespace sedec
{

namespace hybridcast
{

RandomizedLatencyDescriptor::RandomizedLatencyDescriptor()
{
    descriptor_tag = RANDOMIZED_LATENCY_DESCRIPTOR;
    descriptor_length = 0;
    range = 0;
    rate = 0;
    randomization_end_time_flag = 0;
    randomization_end_time = 0;
}

RandomizedLatencyDescriptor::RandomizedLatencyDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    range = rw->Read_On_Buffer(16);
    rate = rw->Read_On_Buffer(8);
    randomization_end_time_flag = rw->Read_On_Buffer(1);
    rw->Skip_On_Buffer(7);
    if ( randomization_end_time_flag ) randomization_end_time = rw->Read_On_Buffer(40);
}

RandomizedLatencyDescriptor::~RandomizedLatencyDescriptor()
{

}

void RandomizedLatencyDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    SECTION_DEBUG("\tdescriptor_tag : 0x%02x (cache_control_info_descriptor)\n", descriptor_tag);
    SECTION_DEBUG("\tdescriptor_length : 0x%x \n", descriptor_length);
    SECTION_DEBUG("\trange : 0x%x \n", range);
    SECTION_DEBUG("\trate : 0x%x \n", rate);
    SECTION_DEBUG("\trandomization_end_time_flag : 0x%x \n", randomization_end_time_flag);
    if ( randomization_end_time_flag )
    {
        SECTION_DEBUG("\trandomization_end_time : 0x%lf \n", randomization_end_time);
    }
    SECTION_DEBUG("\n");
}

void RandomizedLatencyDescriptor::calcLength()
{
    descriptor_length = 4 + ( randomization_end_time_flag ? 5 : 0 );
}

void RandomizedLatencyDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    rw->Write_On_Buffer(range, 16);
    rw->Write_On_Buffer(rate, 8);
    rw->Write_On_Buffer(randomization_end_time_flag, 1);
    rw->Write_On_Buffer(0x0f, 7);
    if ( randomization_end_time_flag )
    {
        rw->Write_On_Buffer(randomization_end_time, 40);
    }
}

} // end of hybridcast namespace

} // end of sedec namespace


