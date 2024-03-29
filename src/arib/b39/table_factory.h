#if !defined __MPEGH_SECTION_FACTORY_H__
#define __MPEGH_SECTION_FACTORY_H__

#include "base/table.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace arib::b39
{
/**
    @addtogroup dvb
    @{
*/
class TableFactory
{
public:
    static base::Table* CreateSection(unsigned char *raw_table);

    enum TableId
    {
        PROGRAM_ASSOCIATION_TABLE = 0x00,
        CONDITIONAL_ACCESS_TABLE = 0x01,
        PROGRAM_MAP_TABLE = 0x02,
        APPLICATION_INFORMATION_TABLE = 0x9C,
        UNKNOWN_TABLE = 0xff,
    };

private:
    TableFactory(){};
    virtual ~TableFactory(){};
};

/** @} */

} // end of dvb namespace

/** @} */

} // end of sedec namespace
#endif
