// descriptor_factory.h: interface for the DescriptorFactory class.
//
//////////////////////////////////////////////////////////////////////
#if !defined __HYBRIDCAST_DESCRIPTOR_FACTORY_H__
#define __HYBRIDCAST_DESCRIPTOR_FACTORY_H__

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

class BitReadWriter;

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
    static Descriptor* CreateDescriptor(BitReadWriter *rw);

private:	
    DescriptorFactory(){};
    virtual ~DescriptorFactory(){};
};

/** @} */

} // end of hybridcast namespace
/** @} */

} // end of sedec namespace
#endif 
