#if !defined(__MH_AIT_SECTION_H__)
#define __MH_AIT_SECTION_H__

using namespace std;
#include <list>

#include "base/table.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace mpegh
{

/**
    @addtogroup mh
    @{
*/
class Application;
class Descriptor;
class ApplicationInformationTable : public base::Table
{
public:
    ApplicationInformationTable();
    ApplicationInformationTable(unsigned char *raw_buffer);
    ApplicationInformationTable(unsigned char *raw_buffer, unsigned int raw_length);
    virtual ~ApplicationInformationTable();
    virtual void PrintTable();

    /* Interfaces to get information (e.g. getter) */
    unsigned int GetApplicationType() const { return application_type;}
    unsigned int GetVersionNumber() const { return version_number; }
    int GetCurrentNextIndicator() const {return current_next_indicator;}
    unsigned int GetSectionNumber() const { return section_number;}
    unsigned int GetLastSectionNumber() const { return last_section_number;}
    unsigned int GetCommonDescriptorLength() const { return common_descriptors_length;}
    list<mpegh::Descriptor*> GetCommonDescriptors() const { return m_common_descriptors;}
    unsigned int GetApplicationLoopLength() const { return application_loop_length;}
    list<mpegh::Application*> GetApplications() const { return m_applications;}

protected:
    unsigned int application_type;
    unsigned int version_number;
    int current_next_indicator;
    unsigned int section_number;
    unsigned int last_section_number;
    unsigned int common_descriptors_length;
    list<mpegh::Descriptor*> m_common_descriptors;
    unsigned int application_loop_length;
    list<mpegh::Application*> m_applications;

    virtual void __decode_table_body__();
};

/** @} */
}

/** @} */
} // end of sedec namespace

#endif