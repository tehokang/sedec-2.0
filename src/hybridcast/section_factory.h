#if !defined __HYBRIDCAST_SECTION_FACTORY_H__
#define __HYBRIDCAST_SECTION_FACTORY_H__

#include "base/section.h"

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
class SectionFactory
{
public:
    static base::Section* CreateSection(unsigned char *raw_table);

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
