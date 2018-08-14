#if !defined __DVB_SIMPLE_APP_LOC_DESC__
#define __DVB_SIMPLE_APP_LOC_DESC__

#include <list>
#include <stdio.h>
#include <string.h>
#include "base/bit_readwriter.h"
#include "descriptors/descriptor.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace dvb
{
/**
    @addtogroup dvb
    @{
*/

class SimpleApplicationLocationDescriptor : public Descriptor
{
public:
    SimpleApplicationLocationDescriptor();
    SimpleApplicationLocationDescriptor(base::BitReadWriter *rw);
    virtual ~SimpleApplicationLocationDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw) override;
    virtual void PrintDescriptor() override;

    /* Interface to encode (setter) */
    void SetInitialPath(const char *init_path)
    {
        memset(initial_path_bytes, 0x00, sizeof(initial_path_bytes));
        snprintf(initial_path_bytes, sizeof(initial_path_bytes), "%s", init_path);
    }

    /* Interface to decode (getter) */
    char* GetInitialPath(){ return initial_path_bytes;}

protected:
    virtual void updateDescriptorLength() override;
    char initial_path_bytes[256];
};

/** @} */

} // end of dvb namespace

/** @} */

} // end of sedec namespace
#endif
