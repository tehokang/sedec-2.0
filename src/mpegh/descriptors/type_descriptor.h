#if !defined __MH_TYPE_DESCRIPTOR_H__
#define __MH_TYPE_DESCRIPTOR_H__

#include <list>
#include <stdio.h>
#include <string.h>
#include "descriptors/descriptor.h"
#include "base/bit_readwriter.h"

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

class TypeDescriptor : public Descriptor
{
public:
    TypeDescriptor();
    TypeDescriptor(base::BitReadWriter *rw);
    virtual ~TypeDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw) override;
    virtual void PrintDescriptor() override;

    /* Interface to encode (setter) */
    void SetTypeText(const char *type_text)
    {
        memset(text_char, 0x00, sizeof(text_char));
        snprintf(text_char, sizeof(text_char), "%s", type_text);
    }

    /* Interface to decode (getter) */
    char* GetTypeText(){ return text_char;}

protected:
    virtual void updateDescriptorLength() override;
    char text_char[256];
};

/** @} */

} // end of mpegh namespace

/** @} */

} // end of sedec namespace
#endif
