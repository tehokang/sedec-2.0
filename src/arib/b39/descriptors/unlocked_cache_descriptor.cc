#include <stdlib.h>
#include <string.h>

#include "base/macro.h"
#include "descriptors/unlocked_cache_descriptor.h"

namespace sedec
{

namespace arib::b39
{

UnlockedCacheDescriptor::UnlockedCacheDescriptor()
{
    descriptor_tag = 0x8032;
    descriptor_length = 0;
    num_of_unlocked_cache_node = 0;
    memset(node_tag, 0x00, sizeof(node_tag));
}

UnlockedCacheDescriptor::UnlockedCacheDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    memset(node_tag, 0x00, sizeof(node_tag));

    if( 0<descriptor_length )
    {
        num_of_unlocked_cache_node = rw->Read_On_Buffer(8);

        for(int i=0;i<num_of_unlocked_cache_node;i++)
        {
            node_tag[i] = rw->Read_On_Buffer(16);
        }
    }
}

UnlockedCacheDescriptor::~UnlockedCacheDescriptor()
{

}

void UnlockedCacheDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    Descriptor::PrintDescriptor("UnlockedCacheDescriptor");

    SECTION_DEBUG("\tnum_of_unlocked_cache_node : 0x%x \n",num_of_unlocked_cache_node);
    for (int i=0;i<num_of_unlocked_cache_node;i++)
    {
        SECTION_DEBUG("\tnode_tag[%d] : 0x%x \n",i,node_tag[i]);
    }

    SECTION_DEBUG("\n");
}

void UnlockedCacheDescriptor::updateDescriptorLength()
{
    descriptor_length = 1 + num_of_unlocked_cache_node*2;
}

void UnlockedCacheDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    if( 0<descriptor_length )
    {
        rw->Write_On_Buffer(num_of_unlocked_cache_node, 8);

        for( int i=0; i<num_of_unlocked_cache_node; i++ )
        {
            rw->Write_On_Buffer(node_tag[i], 16);
        }
    }
}

} // end of mpegh namespace

} // end of sedec namespace
