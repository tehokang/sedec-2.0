#include "base/macro.h"
#include "descriptors/application_recording_descriptor.h"

namespace sedec
{

namespace dvb
{

ApplicationRecordingDescriptor::ApplicationRecordingDescriptor()
{
    descriptor_tag = 0x06;
    descriptor_length = 0;

    scheduled_recording_flag = 0;
    trick_mode_aware_flag = 0;
    time_shift_flag = 0;
    dynamic_flag = 0;
    av_synced_flag = 0;
    initiating_replay_flag = 0;

    label_count = 0;
    memset(label_length, 0x00, sizeof(label_length));
    memset(label_char, 0x00, sizeof(label_char));
    memset(storage_properties, 0x00, sizeof(storage_properties));

    component_tag_list_length = 0;
    memset(component_tag, 0x00, sizeof(component_tag));

    private_length = 0;
    memset(__private, 0x00, sizeof(__private));
}

ApplicationRecordingDescriptor::ApplicationRecordingDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    scheduled_recording_flag = rw->Read_On_Buffer(1);
    trick_mode_aware_flag = rw->Read_On_Buffer(1);
    time_shift_flag = rw->Read_On_Buffer(1);
    dynamic_flag = rw->Read_On_Buffer(1);
    av_synced_flag = rw->Read_On_Buffer(1);
    initiating_replay_flag = rw->Read_On_Buffer(1);
    rw->Skip_On_Buffer(2);
    label_count = rw->Read_On_Buffer(8);

    for(int i=0; i<label_count;i++)
    {
        label_length[i] = rw->Read_On_Buffer(8);
        for(int j=0;label_length[i];j++)
        {
            label_char[i][j] = rw->Read_On_Buffer(8);
        }
        storage_properties[i] = rw->Read_On_Buffer(2);
        rw->Skip_On_Buffer(6);
    }
    component_tag_list_length = rw->Read_On_Buffer(8);
    for(int i=0; component_tag_list_length;i++)
    {
        component_tag[i] = rw->Read_On_Buffer(8);
    }
    private_length = rw->Read_On_Buffer(8);
    for(int i=0;i<private_length;i++)
    {
        __private[i] = rw->Read_On_Buffer(8);
    }

    /* TODO::reserved_future_use */
}

ApplicationRecordingDescriptor::~ApplicationRecordingDescriptor()
{

}

void ApplicationRecordingDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    Descriptor::PrintDescriptor();

    SECTION_DEBUG("\tscheduled_recording_flag : 0x%x \n", scheduled_recording_flag);
    SECTION_DEBUG("\ttrick_mode_aware_flag : 0x%x \n", trick_mode_aware_flag);
    SECTION_DEBUG("\ttime_shift_flag : 0x%x \n", time_shift_flag);
    SECTION_DEBUG("\tdynamic_flag : 0x%x \n", dynamic_flag);
    SECTION_DEBUG("\tav_synced_flag : 0x%x \n", av_synced_flag);
    SECTION_DEBUG("\tinitiating_replay_flag : 0x%x \n", initiating_replay_flag);
    SECTION_DEBUG("\tlabel_count : 0x%x \n", label_count);
    for(int i=0; i<label_count;i++)
    {
        SECTION_DEBUG("\t  label_length[%d] = 0x%x \n", i, label_length[i]);
        SECTION_DEBUG("\t  label_char : %s \n", label_char[i]);
        SECTION_DEBUG("\t  storage_properties[%d] : 0x%x \n", i, storage_properties[i]);
    }

    SECTION_DEBUG("\tcomponent_tag_list_length : 0x%x \n", component_tag_list_length);
    for(int i=0; component_tag_list_length;i++)
    {
        SECTION_DEBUG("\tcomponent_tag : 0x%x \n", component_tag[i]);
    }
    SECTION_DEBUG("\n");
}

void ApplicationRecordingDescriptor::updateDescriptorLength()
{
    unsigned char temp_length = 0;
    for(int i=0;label_count;i++)
    {
        temp_length +=(2+label_length[i]);
    }
    temp_length += component_tag_list_length;
    temp_length += private_length;

    descriptor_length = 4 + temp_length;
}

void ApplicationRecordingDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    rw->Write_On_Buffer(scheduled_recording_flag, 1);
    rw->Write_On_Buffer(trick_mode_aware_flag, 1);
    rw->Write_On_Buffer(time_shift_flag, 1);
    rw->Write_On_Buffer(dynamic_flag, 1);
    rw->Write_On_Buffer(av_synced_flag, 1);
    rw->Write_On_Buffer(initiating_replay_flag, 1);
    rw->Write_On_Buffer(0x0, 2);
    rw->Write_On_Buffer(label_count, 8);

    for(int i=0; i<label_count;i++)
    {
        rw->Write_On_Buffer(label_length[i], 8);
        for(int j=0;label_length[i];j++)
        {
            rw->Write_On_Buffer(label_char[i][j], 8);
        }
        rw->Write_On_Buffer(storage_properties[i], 2);
        rw->Write_On_Buffer(0x0, 6);
    }
    rw->Write_On_Buffer(component_tag_list_length, 8);
    for(int i=0; component_tag_list_length;i++)
    {
        rw->Write_On_Buffer(component_tag[i], 8);
    }
    rw->Write_On_Buffer(private_length, 8);
    for(int i=0;i<private_length;i++)
    {
        rw->Write_On_Buffer(__private[i], 8);
    }
}

} // end of dvb namespace

} // end of sedec namespace
