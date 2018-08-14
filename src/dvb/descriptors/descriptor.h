#if !defined __DVB_DESCRIPTOR_H__
#define __DVB_DESCRIPTOR_H__

#include "base/bit_readwriter.h"
#include "base/descriptor.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace dvb
{
/**
    @addtogroup base
    @{
*/

class Descriptor : public base::Descriptor
{
public:
    Descriptor();
    Descriptor(base::BitReadWriter *rw);
    virtual ~Descriptor();
};

class UnknownDescriptor : public Descriptor
{
public:
    UnknownDescriptor();
    UnknownDescriptor(base::BitReadWriter *rw);
    virtual ~UnknownDescriptor();

    virtual void PrintDescriptor() override;

protected:
    virtual void updateDescriptorLength() override {};
};

/** @} */

} // end of base namespace

/** @} */

} // end of sedec namespace
#endif
