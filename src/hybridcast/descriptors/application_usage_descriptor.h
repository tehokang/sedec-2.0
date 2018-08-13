#if !defined __HYBRIDCAST_APPLICATION_USAGE_DESCRIPTOR_H__
#define __HYBRIDCAST_APPLICATION_USAGE_DESCRIPTOR_H__

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

class ApplicationUsageDescriptor : public Descriptor
{
public:
    ApplicationUsageDescriptor();
    ApplicationUsageDescriptor(base::BitReadWriter *rw);
    virtual ~ApplicationUsageDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw);
    virtual void PrintDescriptor();

    void SetUsageType(int value) { usage_type = value;}
    unsigned char GetUsageType() { return usage_type;}

protected:
    virtual void updateDescriptorLength() override;

    unsigned char usage_type;
};

/** @} */

} // end of hybridcast namespace
/** @} */

} // end of sedec namespace
#endif
