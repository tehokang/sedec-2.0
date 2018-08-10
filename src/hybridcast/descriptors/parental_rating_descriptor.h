#if !defined __HYBRIDCAST_PARENTAL_RATING_DESCRIPTOR_H__
#define __HYBRIDCAST_PARENTAL_RATING_DESCRIPTOR_H__

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

class ParentalRatingDescriptor : public Descriptor
{
public:
    ParentalRatingDescriptor();
    ParentalRatingDescriptor(base::BitReadWriter *rw);
    virtual ~ParentalRatingDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw);
    virtual void PrintDescriptor();

protected:
    virtual void calcLength();

    int country_code[64];
    unsigned char rating[64];
    int m_parent_rating_count;
};

/** @} */

} // end of hybridcast namespace

/** @} */

} // end of sedec namespace
#endif
