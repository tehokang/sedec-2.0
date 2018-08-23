#if !defined(__MPEGH_CAT_SECTION_H__)
#define __MPEGH_CAT_SECTION_H__

#include <list>
#include "base/table.h"

using namespace std;

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace mpegh
{
/**
    @addtogroup mpegh
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

} // end of mpegh namespace

/** @} */

} // end of sedec namespace

#endif
