#include "base/macro.h"
#include "table_factory.h"
#include "tables/program_association_table.h"
#include "tables/conditional_access_table.h"
#include "tables/program_map_table.h"
#include "tables/application_information_table.h"

namespace sedec
{

namespace mpegh
{

base::Table* TableFactory::CreateSection(unsigned char *raw_table)
{
    int table_id = (raw_table[0] & 0xff);
    int table_length = (( raw_table[1] << 8 | raw_table[2] ) & 0x0fff ) + 3;

    base::Table *section = nullptr;

    switch(table_id)
    {
        case PROGRAM_ASSOCIATION_TABLE:
            section = static_cast<base::Table*>(new ProgramAssociationTable(raw_table));
            break;
        case CONDITIONAL_ACCESS_TABLE:
            section = static_cast<base::Table*>(new ConditionalAccessTable(raw_table));
            break;
        case PROGRAM_MAP_TABLE:
            section = static_cast<base::Table*>(new ProgramMapTable(raw_table));
            break;
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
