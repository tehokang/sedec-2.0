// autostart_priority_descriptor.h: interface for the AutostartPriorityDescriptor class.
//
//////////////////////////////////////////////////////////////////////
#if !defined __MH_AUTOSTART_PRIORITY_DESCRIPTOR_H__
#define __MH_AUTOSTART_PRIORITY_DESCRIPTOR_H__

#include <list>
#include <string.h>
#include <stdlib.h>
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

class AutostartPriorityDescriptor : public Descriptor
{
public:
    AutostartPriorityDescriptor();
    AutostartPriorityDescriptor(BitReadWriter *rw);
    virtual ~AutostartPriorityDescriptor();

    virtual void WriteDescriptor(BitReadWriter* rw);
    virtual void PrintDescriptor();

    void SetAutostartPriority(char value) { autostart_priority = value;}
    char GetAutostartPriority() { return autostart_priority;}

protected:
    virtual void calcLength();

    unsigned char autostart_priority;
};

/** @} */

} // end of mh namespace

/** @} */

} // end of sedec namespace
#endif 
