// DSISection.h: interface for the MHAit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__MH_AIT_SECTION_H__)
#define __MH_AIT_SECTION_H__

using namespace std;
#include <list>

#include "section.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace mh{
class Application;
class Descriptor;
};

class MHAit : public Section  
{
public:
    MHAit();
    MHAit(unsigned char *raw_buffer);
    MHAit(unsigned char *raw_buffer, unsigned int raw_length);
    virtual ~MHAit();
    virtual void PrintSection();

    /* Interfaces to get information (e.g. getter) */
    unsigned int GetApplicationType() const { return application_type;}
    unsigned int GetVersionNumber() const { return version_number; }
    int GetCurrentNextIndicator() const {return current_next_indicator;}
    unsigned int GetSectionNumber() const { return section_number;}
    unsigned int GetLastSectionNumber() const { return last_section_number;}
    unsigned int GetCommonDescriptorLength() const { return common_descriptors_length;}
    list<mh::Descriptor*> GetCommonDescriptors() const { return m_common_descriptors;}
    unsigned int GetApplicationLoopLength() const { return application_loop_length;}
    list<mh::Application*> GetApplications() const { return m_applications;}

protected:
    unsigned int application_type;
    unsigned int version_number;
    int current_next_indicator;
    unsigned int section_number;
    unsigned int last_section_number;
    unsigned int common_descriptors_length;
    list<mh::Descriptor*> m_common_descriptors;
    unsigned int application_loop_length;
    list<mh::Application*> m_applications;

    virtual void WriteSection();
    virtual void SetSection();
    virtual void CalcSectionLength();
    virtual void decode();
};

/** @} */

} // end of sedec namespace

#endif 
