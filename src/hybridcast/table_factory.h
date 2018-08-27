#if !defined __HYBRIDCAST_SECTION_FACTORY_H__
#define __HYBRIDCAST_SECTION_FACTORY_H__

#include "base/table.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace hybridcast
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
        PROGRAM_MAP_TABLE = 0x02,
        APPLICATION_INFORMATION_TABLE = 0x74,
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
