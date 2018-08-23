#if !defined(__HYBRIDCAST_CAT_SECTION_H__)
#define __HYBRIDCAST_CAT_SECTION_H__

#include <list>
#include "base/table.h"

using namespace std;

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace hybridcast
{
/**
    @addtogroup hybridcast
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

} // end of hybridcast namespace

/** @} */

} // end of sedec namespace

#endif
