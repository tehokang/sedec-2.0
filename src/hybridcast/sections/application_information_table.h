#if !defined(__HC_AIT_SECTION_H__)
#define __HC_AIT_SECTION_H__

using namespace std;
#include <list>

#include "base/section.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace hybridcast
{

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
    unsigned int GetApplicationType() const { return application_type;}
    unsigned int GetVersionNumber() const { return version_number; }
    int GetCurrentNextIndicator() const {return current_next_indicator;}
    unsigned int GetSectionNumber() const { return section_number;}
    unsigned int GetLastSectionNumber() const { return last_section_number;}
    unsigned int GetCommonDescriptorLength() const { return common_descriptors_length;}
    list<hybridcast::Descriptor*> GetCommonDescriptors() const { return m_common_descriptors;}
    unsigned int GetApplicationLoopLength() const { return application_loop_length;}
    list<hybridcast::Application*> GetApplications() const { return m_applications;}

protected:
    unsigned int application_type;
    unsigned int version_number;
    int current_next_indicator;
    unsigned int section_number;
    unsigned int last_section_number;
    unsigned int common_descriptors_length;
    list<hybridcast::Descriptor*> m_common_descriptors;
    unsigned int application_loop_length;
    list<hybridcast::Application*> m_applications;

    virtual void __decode_section_body__();
};

/** @} */
} // end of hybridcast namespace

/** @} */
} // end of sedec namespace

#endif
