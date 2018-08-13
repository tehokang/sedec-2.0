#if !defined __MH_COMPRESSION_TYPE_DESCRIPTOR_H__
#define __MH_COMPRESSION_TYPE_DESCRIPTOR_H__

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

class CompressionTypeDescriptor : public Descriptor
{
public:
    CompressionTypeDescriptor();
    CompressionTypeDescriptor(base::BitReadWriter *rw);
    virtual ~CompressionTypeDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw);
    virtual void PrintDescriptor();

    /* Interface to encode (setter) */
    void SetCompressionType(unsigned int value) { compression_type = value; }
    void SetOriginalSize(unsigned int value) { original_size = value; }

    /* Interface to decode (getter) */
    int GetCompressionType(){ return compression_type; }
    int GetOriginalSize(){ return original_size; }

protected:
    virtual void updateDescriptorLength() override;

    int compression_type;
    int original_size;
};

/** @} */

} // end of mpegh namespace

/** @} */

} // end of sedec namespace

#endif
