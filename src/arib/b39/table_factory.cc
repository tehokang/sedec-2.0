#include "base/macro.h"
#include "table_factory.h"
#include "tables/application_information_table.h"

namespace sedec
{

namespace arib::b39
{

base::Table* TableFactory::CreateSection(unsigned char *raw_table)
{
    int table_id = (raw_table[0] & 0xff);
    int table_length = (( raw_table[1] << 8 | raw_table[2] ) & 0x0fff ) + 3;

    base::Table *section = nullptr;

    switch(table_id)
    {
        case APPLICATION_INFORMATION_TABLE:
            section = static_cast<base::Table*>(new ApplicationInformationTable(raw_table));
            break;
        default:
            section = static_cast<base::Table*>(new base::UnknownSection(raw_table, table_length));
            break;
    }

    return section;
}

} // end of dvb namespace

} // end of sedec namespace
