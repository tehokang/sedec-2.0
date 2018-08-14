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
namespace hybridcast
{
/**
    @addtogroup hybridcast
    @{
*/

class ApplicationBoundaryAndPermissionDescriptor : public Descriptor
{
private:
    struct ManagedURL
    {
        unsigned char managed_URL_length;
        unsigned char managed_URL_byte[256];
    };

    struct ApplicationBoundaryAndPermission
    {
        unsigned char permission_bitmap_count;
        std::list<uint16_t> permission_bitmaps;
        unsigned char managed_URL_count;
        std::list<ManagedURL *> managed_urls;
    };


public:
    ApplicationBoundaryAndPermissionDescriptor();
    ApplicationBoundaryAndPermissionDescriptor(base::BitReadWriter *rw);
    virtual ~ApplicationBoundaryAndPermissionDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw) override;
    virtual void PrintDescriptor() override;

    int GetApplicationBoundaryAndPermissionCount()
    {
        return infos.size();
    }

    std::list<ApplicationBoundaryAndPermission *>& GetBoundaryAndPermissions()
    {
        return infos;
    }

protected:
    virtual void updateDescriptorLength() override;
    std::list<ApplicationBoundaryAndPermission *> infos;
};

/** @} */

} // end of hybridcast namespace

/** @} */

} // end of sedec namespace
#endif