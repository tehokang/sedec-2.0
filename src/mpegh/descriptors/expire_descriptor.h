#if !defined __MH_EXPIRE_DESCRIPTOR_H__
#define __MH_EXPIRE_DESCRIPTOR_H__

#include <string.h>
#include "base/bit_readwriter.h"
#include "descriptors/descriptor.h"

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

class ExpireDescriptor : public Descriptor
{
public:
    ExpireDescriptor();
    ExpireDescriptor(base::BitReadWriter *rw);
    virtual ~ExpireDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw) override;
    virtual void PrintDescriptor() override;

    /* Interface to encode (setter) */
    void SetUTCTime(double value)
    {
        time_mode = 0x01;
        UTC_time = value;
    }
    void SetPassedSeconds(int value)
    {
        time_mode = 0x04;
        passed_seconds = value;
    }

    /* Interface to decode (getter) */
    int GetTimeMode(){ return time_mode;}
    double GetUTCTime() { return UTC_time;}
    int GetPassedSeconds() { return passed_seconds;}

protected:
    virtual void updateDescriptorLength() override;

    int time_mode;
    double UTC_time;
    int passed_seconds;
};

/** @} */

} // end of mpegh namespace

/** @} */

} // end of sedec namespace

#endif
