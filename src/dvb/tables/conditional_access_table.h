#if !defined(__DVB_CAT_SECTION_H__)
#define __DVB_CAT_SECTION_H__

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

class Descriptor;

class ConditionalAccessTable : public base::Table
{
public:
    ConditionalAccessTable();
    ConditionalAccessTable(unsigned char *raw_buffer);
    ConditionalAccessTable(unsigned char *raw_buffer, unsigned int raw_length);
    virtual ~ConditionalAccessTable();
    virtual void PrintTable();


protected:
    unsigned char version_number;
    unsigned char current_next_indicator;
    unsigned char section_number;
    unsigned char last_section_number;
    list<Descriptor*> descriptors;

    virtual void __decode_table_body__();
};

/** @} */

} // end of dvb namespace

/** @} */

} // end of sedec namespace

#endif
