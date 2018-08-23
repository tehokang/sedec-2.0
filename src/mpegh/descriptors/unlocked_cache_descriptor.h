#if !defined __MH_UNLOCKED_CACHE_DESCRIPTOR_H__
#define __MH_UNLOCKED_CACHE_DESCRIPTOR_H__

#include <string.h>
#include "base/bit_readwriter.h"
#include "descriptors/descriptor.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace mpegh
{
/**
    @addtogroup mpegh
    @{
*/

class UnlockedCacheDescriptor : public Descriptor
{
public:
    UnlockedCacheDescriptor();
    UnlockedCacheDescriptor(base::BitReadWriter *rw);
    virtual ~UnlockedCacheDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw) override;
    virtual void PrintDescriptor() override;

    /* Interface to encode (setter) */
    void SetNodeTag(int value[], int length)
    {
        memset(node_tag, 0x00, sizeof(node_tag));

        num_of_unlocked_cache_node = length;
        for (int i=0; i<num_of_unlocked_cache_node; i++)
        {
            node_tag[i] = value[i];
        }
    }

    /* Interface to decode (getter) */
    int GetNumOfUnlockedCache() { return num_of_unlocked_cache_node;}
    int GetNodeTag() { return node_tag[0];}

protected:
    virtual void updateDescriptorLength() override;

    int num_of_unlocked_cache_node;
    int node_tag[128];
};

/** @} */

} // end of mpegh namespace

/** @} */

} // end of sedec namespace

#endif
