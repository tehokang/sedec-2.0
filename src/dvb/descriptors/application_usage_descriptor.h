#if !defined __DVB_APPLICATION_USAGE_DESCRIPTOR_H__
#define __DVB_APPLICATION_USAGE_DESCRIPTOR_H__

#include <list>
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

class ApplicationUsageDescriptor : public Descriptor
{
public:
    ApplicationUsageDescriptor();
    ApplicationUsageDescriptor(base::BitReadWriter *rw);
    virtual ~ApplicationUsageDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw) override;
    virtual void PrintDescriptor() override;

    void SetUsageType(int value) { usage_type = value;}
    unsigned char GetUsageType() { return usage_type;}

protected:
    virtual void updateDescriptorLength() override;

    unsigned char usage_type;
};

/** @} */

} // end of dvb namespace

/** @} */

} // end of sedec namespace
#endif
