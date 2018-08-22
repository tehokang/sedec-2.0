#if !defined __DVB_SECTION_FACTORY_H__
#define __DVB_SECTION_FACTORY_H__

#include "base/table.h"

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
class SectionFactory
{
public:
    static base::Table* CreateSection(unsigned char *raw_table);

    enum TableId
    {
        APPLICATION_INFORMATION_TABLE = 0x74,
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
