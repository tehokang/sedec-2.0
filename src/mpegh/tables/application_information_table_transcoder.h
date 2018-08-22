#if !defined(__HYBRIDCAST_AIT_SECTION_TRANSCODER_H__)
#define __HYBRIDCAST_AIT_SECTION_TRANSCODER_H__

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

namespace mpegh
{

class Descriptor;
class Application;

class ApplicationInformationTableTranscoder : public ApplicationInformationTable
{
public:
    ApplicationInformationTableTranscoder();
    ApplicationInformationTableTranscoder(unsigned char *raw_buffer);
    ApplicationInformationTableTranscoder(unsigned char *raw_buffer, unsigned int raw_length);
    virtual ~ApplicationInformationTableTranscoder();

protected:
    virtual void __encode_write_table_body__() override;
    virtual void __encode_preprare_table__() override;
    virtual void __encode_update_table_length__() override;

private:
    Descriptor* findDescriptor(
      list<Descriptor*>descriptors, Descriptor::DESCRIPTOR_TAG tag);
};

/** @} */

} // end of dvb namespace

/** @} */

} // end of sedec namespace

#endif
