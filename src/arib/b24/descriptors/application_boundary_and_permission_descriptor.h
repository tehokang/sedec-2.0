#if !defined __HYBRIDCAST_APPLICATION_BOUNDARY_AND_PERMISSION_DESCRIPTOR_H__
#define __HYBRIDCAST_APPLICATION_BOUNDARY_AND_PERMISSION_DESCRIPTOR_H__

#include <list>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "descriptor.h"
#include "base/bit_readwriter.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/
namespace arib::b24
{
/**
    @addtogroup hybridcast
    @{
*/

class ApplicationBoundaryAndPermissionDescriptor : public Descriptor
{
private:
    unsigned char permission_bitmap_count;
    int permission_bitmap[256];
    unsigned char managed_URL_count;
    unsigned char managed_URL_length[256];
    unsigned char managed_URL_byte[256][256];


public:
    ApplicationBoundaryAndPermissionDescriptor();
    ApplicationBoundaryAndPermissionDescriptor(base::BitReadWriter *rw);
    virtual ~ApplicationBoundaryAndPermissionDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw) override;
    virtual void PrintDescriptor() override;

protected:
    virtual void updateDescriptorLength() override;
};

/** @} */

} // end of hybridcast namespace

/** @} */

} // end of sedec namespace
#endif
