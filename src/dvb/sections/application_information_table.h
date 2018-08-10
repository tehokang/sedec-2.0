#if !defined(__DVB_AIT_SECTION_H__)
#define __DVB_AIT_SECTION_H__

#include <list>
#include "base/section.h"

using namespace std;

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

class Application;
class Descriptor;

class ApplicationInformationTable : public base::Section
{
public:
    ApplicationInformationTable();
    ApplicationInformationTable(unsigned char *raw_buffer);
    ApplicationInformationTable(unsigned char *raw_buffer, unsigned int raw_length);
    virtual ~ApplicationInformationTable();
    virtual void PrintSection();

    /* Interfaces to get information (e.g. getter) */
    int GetTestApplicationFlag() const { return test_application_flag;}
    unsigned int GetApplicationType() const { return application_type;}
    unsigned int GetVersionNumber() const { return version_number; }
    int GetCurrentNextIndicator() const {return current_next_indicator;}
    unsigned int GetSectionNumber() const { return section_number;}
    unsigned int GetLastSectionNumber() const { return last_section_number;}
    unsigned int GetCommonDescriptorLength() const { return common_descriptors_length;}
    list<dvb::Descriptor*> GetCommonDescriptors() const { return m_common_descriptors;}
    unsigned int GetApplicationLoopLength() const { return application_loop_length;}
    list<dvb::Application*> GetApplications() const { return m_applications;}

protected:
    int test_application_flag;
    unsigned int application_type;
    unsigned int version_number;
    int current_next_indicator;
    unsigned int section_number;
    unsigned int last_section_number;
    unsigned int common_descriptors_length;
    list<dvb::Descriptor*> m_common_descriptors;
    unsigned int application_loop_length;
    list<dvb::Application*> m_applications;

    virtual void decode();
};

/** @} */

} // end of dvb namespace

/** @} */

} // end of sedec namespace

#endif
