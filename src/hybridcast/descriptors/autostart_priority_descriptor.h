#if !defined __HYBRIDCAST_AUTOSTART_PRIORITY_DESCRIPTOR_H__
#define __HYBRIDCAST_AUTOSTART_PRIORITY_DESCRIPTOR_H__

#include <list>
#include <string.h>
#include <stdlib.h>
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

class AutostartPriorityDescriptor : public Descriptor
{
public:
    AutostartPriorityDescriptor();
    AutostartPriorityDescriptor(base::BitReadWriter *rw);
    virtual ~AutostartPriorityDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw);
    virtual void PrintDescriptor();

    void SetAutostartPriority(char value) { autostart_priority = value;}
    char GetAutostartPriority() { return autostart_priority;}

protected:
    virtual void calcLength();

    unsigned char autostart_priority;
};

/** @} */

} // end of hybridcast namespace

/** @} */

} // end of sedec namespace
#endif
