#if !defined __HYBRIDCAST_APPLICATION_RECORDING_DESCRIPTOR_H__
#define __HYBRIDCAST_APPLICATION_RECORDING_DESCRIPTOR_H__

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

class ApplicationRecordingDescriptor : public Descriptor
{
public:
    ApplicationRecordingDescriptor();
    ApplicationRecordingDescriptor(base::BitReadWriter *rw);
    virtual ~ApplicationRecordingDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw);
    virtual void PrintDescriptor();

    void SetScheduledRecordingFlag(int value) { scheduled_recording_flag = value;}
    void SetTrickModeAwareFlag(int value){ trick_mode_aware_flag = value;}
    void SetTimeShiftFlag(int value){ time_shift_flag = value;}
    void SetDynamicFlag(int value) { dynamic_flag = value;}
    void SetAVSyncedFlag(int value) { av_synced_flag = value;}
    void SetInitiatingReplayFlag(int value) { initiating_replay_flag = value;}

    int GetScheduledRecordingFlag() { return scheduled_recording_flag;}
    int GetTrickModeAwareFlag() { return trick_mode_aware_flag;}
    int GetTimeShiftFlag() { return time_shift_flag;}
    int GetDynamicFlag() { return dynamic_flag;}
    int GetAVSyncedFlag() { return av_synced_flag;}
    int GetInitiatingReplayFlag() { return initiating_replay_flag;}

protected:
    virtual void updateDescriptorLength() override;

    int scheduled_recording_flag;
    int trick_mode_aware_flag;
    int time_shift_flag;
    int dynamic_flag;
    int av_synced_flag;
    int initiating_replay_flag;

    unsigned char label_count;
    unsigned int label_length[256];
    unsigned char label_char[256][256];
    unsigned char storage_properties[256];

    unsigned char component_tag_list_length;
    unsigned char component_tag[256];

    unsigned char private_length;
    unsigned char __private[256];
};

/** @} */

} // end of hybridcast namespace

/** @} */

} // end of sedec namespace
#endif
