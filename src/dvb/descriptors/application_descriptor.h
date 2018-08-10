// application_descriptor.h: interface for the ApplicationDescriptor class.
//
//////////////////////////////////////////////////////////////////////
#if !defined __DVB_APPLICATION_DESCRIPTOR_H__
#define __DVB_APPLICATION_DESCRIPTOR_H__

#include <list>
#include <string.h>
#include <stdlib.h>
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

class ApplicationDescriptor : public Descriptor
{
public:
    ApplicationDescriptor();
    ApplicationDescriptor(base::BitReadWriter *rw);
    virtual ~ApplicationDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw);
    virtual void PrintDescriptor();

    struct ApplicationProfile {
        int applicaton_profile;
        int version_major;
        int version_minor;
        int version_micro;
    };

    /* Interface to encode (setter) */
    void SetApplicationVersion(int major, int minor, int micro)
    {
        application_profiles.version_major = major;
        application_profiles.version_minor = minor;
        application_profiles.version_micro = micro;
    }
    void SetServiceBoundFlag(int value) { service_bound_flag = value;}
    void SetVisibility(int value) { visibility = value;}
    void SetApplicationPriority(int value) { application_priority = value;}
    void SetTransportProtocolLabel(const char *value)
    {
        transport_protocol_label[0] = atoi(value);
        transport_protocol_label_length = 1;
        //memset(transport_protocol_label, 0x00, sizeof(transport_protocol_label));
        //snprintf(transport_protocol_label, sizeof(transport_protocol_label),"%s", value);
    }

    /* Interface to decode (getter) */
    void GetApplicationVersion(int *major, int *minor, int *micro)
    {
        *major = application_profiles.version_major;
        *minor = application_profiles.version_minor;
        *micro = application_profiles.version_micro;
    }
    int GetServiceBoundFlag() { return service_bound_flag;}
    int GetVisibility() { return visibility;}
    int GetApplicationPriority(){ return application_priority;}
    char* GetTransportProtocolLabel() { return transport_protocol_label;}
    int GetTransportProtocolLabelLength(){ return transport_protocol_label_length;}

protected:
    virtual void calcLength();

    int application_profiles_length;
    ApplicationProfile application_profiles;
    int service_bound_flag;
    int visibility;
    int application_priority;
    char transport_protocol_label[256];
    int transport_protocol_label_length;
};

/** @} */

} // end of dvb namespace

/** @} */

} // end of sedec namespace
#endif
