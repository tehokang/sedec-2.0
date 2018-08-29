#if !defined __MH_LINKED_PU_DESCRIPTOR_H__
#define __MH_LINKED_PU_DESCRIPTOR_H__

#include <string.h>
#include "base/bit_readwriter.h"
#include "descriptors/descriptor.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace arib::b39
{
/**
    @addtogroup mpegh
    @{
*/

class LinkedPuDescriptor : public Descriptor
{
public:
    LinkedPuDescriptor();
    LinkedPuDescriptor(base::BitReadWriter *rw);
    virtual ~LinkedPuDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw) override;
    virtual void PrintDescriptor() override;

    /* Interface to encode (setter) */
    void SetLinkedPUTag(char *value)
    {
        memset(linked_PU_tag, 0x00, sizeof(linked_PU_tag));
        snprintf(linked_PU_tag, sizeof(linked_PU_tag),"%s", value);
        num_of_linked_PU = strlen(linked_PU_tag);
    }

    /* Interface to decode (getter) */
    int GetNumOfLinkedPU() { return num_of_linked_PU;}
    char *GetLinkedPUTag() { return linked_PU_tag;}

protected:
    virtual void updateDescriptorLength() override;

    int num_of_linked_PU;
    char linked_PU_tag[256];
};

/** @} */

} // end of mpegh namespace

/** @} */

} // end of sedec namespace

#endif
