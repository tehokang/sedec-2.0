// descriptor_factory.h: interface for the DescriptorFactory class.
//
//////////////////////////////////////////////////////////////////////
#if !defined __HYBRIDCAST_DESCRIPTOR_FACTORY_H__
#define __HYBRIDCAST_DESCRIPTOR_FACTORY_H__

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

} // end of hybridcast namespace
/** @} */

} // end of sedec namespace
#endif
