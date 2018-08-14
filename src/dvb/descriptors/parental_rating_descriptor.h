#if !defined __DVB_PARENTAL_RATING_DESCRIPTOR_H__
#define __DVB_PARENTAL_RATING_DESCRIPTOR_H__

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

class ParentalRatingDescriptor : public Descriptor
{
public:
    ParentalRatingDescriptor();
    ParentalRatingDescriptor(base::BitReadWriter *rw);
    virtual ~ParentalRatingDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw) override;
    virtual void PrintDescriptor() override;

protected:
    virtual void updateDescriptorLength() override;

    int country_code[64];
    unsigned char rating[64];
    int m_parent_rating_count;
};

/** @} */

} // end of dvb namespace

/** @} */

} // end of sedec namespace
#endif
