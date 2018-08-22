#include <stdlib.h>
#include <string.h>

#include "base/macro.h"
#include "descriptors//locked_cache_descriptor.h"

namespace sedec
{

namespace mpegh
{

LockedCacheDescriptor::LockedCacheDescriptor()
{
    descriptor_tag = 0x8031;
    descriptor_length = 0;
    num_of_locked_cache_node = 0;
    memset(node_tag, 0x00, sizeof(node_tag));
}

LockedCacheDescriptor::LockedCacheDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    memset(node_tag, 0x00, sizeof(node_tag));

    if( 0<descriptor_length )
    {
        num_of_locked_cache_node = rw->Read_On_Buffer(8);

        for(int i=0;i<num_of_locked_cache_node;i++)
        {
            node_tag[i] = rw->Read_On_Buffer(16);
        }
    }
}

LockedCacheDescriptor::~LockedCacheDescriptor()
{

}

void LockedCacheDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    Descriptor::PrintDescriptor("LockedCacheDescriptor");

    SECTION_DEBUG("\tnum_of_locked_cache_node : 0x%x \n",num_of_locked_cache_node);
    for (int i=0;i<num_of_locked_cache_node;i++)
    {
        SECTION_DEBUG("\tnode_tag[%d] : 0x%x \n",i,node_tag[i]);
    }

    SECTION_DEBUG("\n");
}

void LockedCacheDescriptor::updateDescriptorLength()
{
    descriptor_length = 1 + num_of_locked_cache_node*2;
}

void LockedCacheDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    if( 0<descriptor_length )
    {
        rw->Write_On_Buffer(num_of_locked_cache_node, 8);

        for( int i=0; i<num_of_locked_cache_node; i++ )
        {
            rw->Write_On_Buffer(node_tag[i], 16);
        }
    }
}

} // end of mpegh namespace

} // end of sedec namespace
