#if !defined(__DVB_AIT_SECTION_TRANSCODER_H__)
#define __DVB_AIT_SECTION_TRANSCODER_H__

#include <list>

#include "descriptors/application.h"
#include "descriptors/descriptor.h"
#include "sections/application_information_table.h"

using namespace std;

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace dvb
{

class Descriptor;
class Application;

class ApplicationInformationTableTranscoder : public ApplicationInformationTable
{
public:
    ApplicationInformationTableTranscoder();
    ApplicationInformationTableTranscoder(unsigned char *raw_buffer);
    ApplicationInformationTableTranscoder(
            unsigned char *raw_buffer, unsigned int raw_length);
    virtual ~ApplicationInformationTableTranscoder();

    /* Scenario Interfaces to encode (setter) */
    void SetApplicationUrl(const char *base_url, const char *init_path);
    void SetApplicationVersion(const int major, const int minor, const int micro);
    void SetApplicationVisibility(const int value);
    void SetApplicationId(const int value);
    void SetOrganizationId(const int value);
    void SetRemoteConnection(const int value);
    void SetProtocolId(const int value);
    void SetOriginalNetworkId(const int value);
    void SetTransportStreamId(const int value);
    void SetServiceId(const int value);
    void SetComponentTag(const int value);

    /* Scenario Interfaces to encode (getter) */
    void GetApplicationVersion(int &major, int &minor, int &micro);
    void GetApplicationUrl(const char **base_url, const char **init_path);

    /* Interfaces to encode (setter) */
    void SetTestApplicationFlag(const int value) { test_application_flag = value;}
    void SetApplicationType(const int value) { application_type = value;}
    void SetVersionNumber(const int value) { version_number = value;}
    void SetCurrentNextIndicator(const int value) { current_next_indicator = value;}
    void SetSectionNumber(const int value) { section_number = value;}
    void SetLastSectionNumber(const int value) { last_section_number = value;}
    void SetTransportProtocolLabel(const char *label);
    void SetCommonDescriptors(const list<dvb::Descriptor*> value);
    void SetApplications(const list<dvb::Application*> value);

protected:
    virtual void __encode_write_section_body__() override;
    virtual void __encode_preprare_section__() override;
    virtual void __encode_update_section_length__() override;

private:
    Descriptor* findDescriptor(list<Descriptor*>descriptors, int tag);
};

/** @} */

} // end of dvb namespace

/** @} */

} // end of sedec namespace

#endif
