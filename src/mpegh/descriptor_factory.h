#if !defined __MH_DESCRIPTOR_FACTORY_H__
#define __MH_DESCRIPTOR_FACTORY_H__

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
    @addtogroup mpegh
    @{
*/
class Descriptor;
class DescriptorFactory
{
public:
    static Descriptor* CreateDescriptor(base::BitReadWriter *rw);

private:
    DescriptorFactory(){};
    virtual ~DescriptorFactory(){};
};

/** @} */

} // end of mh namespace

/** @} */

} // end of sedec namespace
#endif
