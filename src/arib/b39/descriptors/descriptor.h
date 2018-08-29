#if !defined __MH_DESCRIPTOR_H__
#define __MH_DESCRIPTOR_H__

#include "base/bit_readwriter.h"
#include "base/descriptor.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace arib::b39
{
/**
    @addtogroup mh
    @{
*/

class Descriptor : public base::Descriptor
{
public:
    Descriptor();
    Descriptor(base::BitReadWriter *rw);
    virtual ~Descriptor();

    int GetDescriptorLength();
    virtual void WriteDescriptor(base::BitReadWriter* rw);
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

} // end of mh namespace

/** @} */

} // end of sedec namespace
#endif
