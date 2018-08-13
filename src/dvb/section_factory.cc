#include "base/macro.h"
#include "base/section.h"
#include "section_factory.h"
#include "sections/application_information_table.h"

namespace sedec
{

namespace dvb
{

base::Section* SectionFactory::CreateSection(unsigned char *raw_table)
{
    int table_id = (raw_table[0] & 0xff);
    int table_length = (( raw_table[1] << 8 | raw_table[2] ) & 0x0fff ) + 3;

    base::Section *section = nullptr;

    switch(table_id)
    {
        /**
         * @note It is related in ETSI TS 102 809 v1.4.1
         **/
        case APPLICATION_INFORMATION_TABLE:
            section = static_cast<base::Section*>(new ApplicationInformationTable(raw_table));
        default:
            section = static_cast<base::Section*>(new base::UnknownSection(raw_table, table_length));
    }

    return section;
}

} // end of dvb namespace

} // end of sedec namespace
