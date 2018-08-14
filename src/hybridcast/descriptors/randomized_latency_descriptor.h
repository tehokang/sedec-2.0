#if !defined __HYBRIDCAST_RANDOMIZED_LATENCY_DESCRIPTOR_H__
#define __HYBRIDCAST_RANDOMIZED_LATENCY_DESCRIPTOR_H__

#include <list>
#include <string.h>
#include <stdlib.h>
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

class RandomizedLatencyDescriptor : public Descriptor
{
public:
    RandomizedLatencyDescriptor();
    RandomizedLatencyDescriptor(base::BitReadWriter *rw);
    virtual ~RandomizedLatencyDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw) override;
    virtual void PrintDescriptor() override;

    void SetRange(unsigned int value) { range = value;}
    void SetRate(unsigned int value) { rate = value;}
    void SetRandomizationEndTimeFlag(unsigned char value) { randomization_end_time_flag = value;}
    void SetRandomizationEndTime(double value) { randomization_end_time = value;}

    unsigned int GetRange() { return range;}
    unsigned int GetRate() { return rate;}
    unsigned char GetRandomizationEndTimeFlag() { return randomization_end_time_flag;}
    double GetRandomizationEndTime() { return randomization_end_time;}

protected:
    virtual void updateDescriptorLength() override;

    unsigned int range;
    unsigned int rate;
    unsigned char randomization_end_time_flag;
    double randomization_end_time;
};

/** @} */

} // end of hybridcast namespace
/** @} */

} // end of sedec namespace
#endif
