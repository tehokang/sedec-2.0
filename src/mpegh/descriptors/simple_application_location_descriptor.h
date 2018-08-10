#if !defined __MH_SIMPLE_APP_LOC_DESC__
#define __MH_SIMPLE_APP_LOC_DESC__

#include <list>
#include <stdio.h>
#include <string.h>
#include "descriptor.h"
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
    @addtogroup mh
    @{
*/

class SimpleApplicationLocationDescriptor : public Descriptor
{
public:
    SimpleApplicationLocationDescriptor();
    SimpleApplicationLocationDescriptor(base::BitReadWriter *rw);
    virtual ~SimpleApplicationLocationDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw);
    virtual void PrintDescriptor();

    /* Interface to encode (setter) */
    void SetInitialPath(const char *init_path)
    {
        memset(initial_path_bytes, 0x00, sizeof(initial_path_bytes));
        snprintf(initial_path_bytes, sizeof(initial_path_bytes), "%s", init_path);
    }

    /* Interface to decode (getter) */
    char* GetInitialPath(){ return initial_path_bytes;}

protected:
    virtual void calcLength();
    char initial_path_bytes[256];
};

/** @} */

} // end of mh namespace

/** @} */

} // end of sedec namespace
#endif
