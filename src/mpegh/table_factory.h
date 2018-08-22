#if !defined __MPEGH_SECTION_FACTORY_H__
#define __MPEGH_SECTION_FACTORY_H__

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
    @addtogroup dvb
    @{
*/
class SectionFactory
{
public:
    static base::Table* CreateSection(unsigned char *raw_table);

    enum TableId
    {
        APPLICATION_INFORMATION_TABLE = 0x9C,
        UNKNOWN_TABLE = 0xff,
    };

private:
    SectionFactory(){};
    virtual ~SectionFactory(){};
};

/** @} */

} // end of dvb namespace

/** @} */

} // end of sedec namespace
#endif
