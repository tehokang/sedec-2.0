// application_boundary_and_permission_descriptor.h: interface for the ApplicationBoundaryAndPermissionDescriptor class.
//
//////////////////////////////////////////////////////////////////////
#if !defined __MH_APPLICATION_BOUNDARY_AND_PERMISSION_DESCRIPTOR_H__
#define __MH_APPLICATION_BOUNDARY_AND_PERMISSION_DESCRIPTOR_H__

#include <list>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "descriptor.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

class BitReadWriter;

namespace mh
{
/**
    @addtogroup mh
    @{
*/

class ApplicationBoundaryAndPermissionDescriptor : public Descriptor
{
private:
    struct ManagedURL {
        unsigned char managed_URL_length;
        unsigned char managed_URL_byte[256];
    };

    struct ApplicationBoundaryAndPermission {
        unsigned char permission_bitmap_count;
        std::list<uint16_t> permission_bitmaps;
        unsigned char managed_URL_count;
        std::list<ManagedURL *> managed_urls;
    };


public:
    ApplicationBoundaryAndPermissionDescriptor();
    ApplicationBoundaryAndPermissionDescriptor(BitReadWriter *rw);
    virtual ~ApplicationBoundaryAndPermissionDescriptor();

    virtual void WriteDescriptor(BitReadWriter* rw);
    virtual void PrintDescriptor();

    int GetApplicationBoundaryAndPermissionCount()
    {
        return infos.size();
    }
    
    std::list<ApplicationBoundaryAndPermission *>& GetBoundaryAndPermissions()
    {
        return infos;
    }

protected:
    virtual void calcLength();
    std::list<ApplicationBoundaryAndPermission *> infos;
};

/** @} */

} // end of mh namespace

/** @} */

} // end of sedec namespace
#endif 