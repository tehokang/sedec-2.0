// descriptor_factory.h: interface for the DescriptorFactory class.
//
//////////////////////////////////////////////////////////////////////
#if !defined __MH_DESCRIPTOR_FACTORY_H__
#define __MH_DESCRIPTOR_FACTORY_H__

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

} // end of mh namespace

/** @} */

} // end of sedec namespace
#endif 
