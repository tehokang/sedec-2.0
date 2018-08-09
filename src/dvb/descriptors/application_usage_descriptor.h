// application_usage_descriptor.h: interface for the ApplicationUsageDescriptor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined __DVB_APPLICATION_USAGE_DESCRIPTOR_H__
#define __DVB_APPLICATION_USAGE_DESCRIPTOR_H__

#include <list>
#include <string.h>
#include "descriptor.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

class BitReadWriter;

namespace dvb
{
/**
    @addtogroup dvb
    @{
*/

class ApplicationUsageDescriptor : public Descriptor
{
public:
    ApplicationUsageDescriptor();
    ApplicationUsageDescriptor(BitReadWriter *rw);
    virtual ~ApplicationUsageDescriptor();

    virtual void WriteDescriptor(BitReadWriter* rw);
    virtual void PrintDescriptor();

    void SetUsageType(int value) { usage_type = value;}
    unsigned char GetUsageType() { return usage_type;}

protected:
    virtual void calcLength();

    unsigned char usage_type;
};

/** @} */

} // end of dvb namespace

/** @} */

} // end of sedec namespace
#endif
