#if !defined __DVB_DESCRIPTOR_FACTORY_H__
#define __DVB_DESCRIPTOR_FACTORY_H__

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

} // end of dvb namespace

/** @} */

} // end of sedec namespace
#endif
