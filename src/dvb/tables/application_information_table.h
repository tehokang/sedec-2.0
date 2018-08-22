#if !defined(__DVB_AIT_SECTION_H__)
#define __DVB_AIT_SECTION_H__

#include <list>
#include "base/table.h"

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

class ApplicationInformationTable : public base::Table
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
    list<Descriptor*> GetCommonDescriptors() const { return common_descriptors;}
    unsigned int GetApplicationLoopLength() const { return application_loop_length;}
    list<Application*> GetApplications() const { return applications;}

protected:
    int test_application_flag;
    unsigned int application_type;
    unsigned int version_number;
    int current_next_indicator;
    unsigned int section_number;
    unsigned int last_section_number;
    unsigned int common_descriptors_length;
    list<Descriptor*> common_descriptors;
    unsigned int application_loop_length;
    list<Application*> applications;

    virtual void __decode_section_body__();
};

/** @} */

} // end of dvb namespace

/** @} */

} // end of sedec namespace

#endif
