#if !defined __HYBRIDCAST_SIMPLE_APP_BOUNDARY_DESCRIPTOR_H__
#define __HYBRIDCAST_SIMPLE_APP_BOUNDARY_DESCRIPTOR_H__

#include <list>
#include <string.h>
#include "descriptor.h"
#include "base/bit_readwriter.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace hybridcast
{
/**
    @addtogroup hybridcast
    @{
*/

class SimpleApplicationBoundaryDescriptor : public Descriptor
{
public:
    SimpleApplicationBoundaryDescriptor();
    SimpleApplicationBoundaryDescriptor(base::BitReadWriter *rw);
    virtual ~SimpleApplicationBoundaryDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw);
    virtual void PrintDescriptor();

    /* Interface to encode (setter) */
    void SetBoundaryExtension(unsigned char ext_count,
                                unsigned char* ext_length,
                                unsigned char** ext_byte)
    {
        boundary_extension_count = ext_count;
        memset(boundary_extension_length, 0x00, sizeof(boundary_extension_length));
        memcpy((unsigned char*)boundary_extension_length,
                (unsigned char*)ext_length, sizeof(boundary_extension_length));
        memcpy((unsigned char**)boundary_extension_byte,
                (unsigned char**)ext_byte, sizeof(boundary_extension_byte));

    }
    /* Interface to decode (getter) */

protected:
    virtual void calcLength();

    unsigned char boundary_extension_count;
    unsigned char boundary_extension_length[256];
    unsigned char boundary_extension_byte[256][256];
};

/** @} */

} // end of hybridcast namespace
/** @} */

} // end of sedec namespace
#endif
