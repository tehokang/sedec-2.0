#include <string.h>
#include <cstddef>
#include <stdlib.h>

#include "base/macro.h"

#include "descriptor_factory.h"
#include "descriptors/descriptor.h"
#include "tables/conditional_access_table.h"

namespace sedec
{

using namespace hybridcast;

ConditionalAccessTable::ConditionalAccessTable()
{
    table_id = 0x01;
    section_syntax_indicator = 0x01;
    section_length = 0;
}

ConditionalAccessTable::ConditionalAccessTable(unsigned char *raw_buffer)
    : Table(raw_buffer, (( raw_buffer[1] << 8 | raw_buffer[2] ) & 0x0fff ) + 3)
{
    __decode_table_body__();
}


ConditionalAccessTable::ConditionalAccessTable(
        unsigned char *raw_buffer, unsigned int raw_length)
    : Table(raw_buffer, raw_length)
{
    __decode_table_body__();
}

ConditionalAccessTable::~ConditionalAccessTable()
{
    for (list<Descriptor*>::iterator it=descriptors.begin();
            it != descriptors.end(); ++it)
    {
        delete (*it);
    }

    descriptors.clear();
}

void ConditionalAccessTable::__decode_table_body__()
{
    Skip_On_Buffer(18);
    version_number = Read_On_Buffer(5);
    current_next_indicator = Read_On_Buffer(1);
    section_number = Read_On_Buffer(8);
    last_section_number = Read_On_Buffer(8);

    for ( int i=(section_length-9); i>0; )
    {
        Descriptor *desc = DescriptorFactory::CreateDescriptor(this);
        i-=desc->GetDescriptorLength();
        descriptors.push_back(desc);
    }
    checksum_CRC32 = Read_On_Buffer(32);
}

void ConditionalAccessTable::PrintTable()
{
    SECTION_DEBUG("= PAT Section's raw information is followings ===== \n");
    Table::PrintTable();

    SECTION_DEBUG("version_number : 0x%x \n", version_number);
    SECTION_DEBUG("current_next_indicator : 0x%x \n", current_next_indicator);
    SECTION_DEBUG("section_number : 0x%x \n", section_number);
    SECTION_DEBUG("last_section_number : 0x%x \n", last_section_number);

    for ( list<Descriptor*>::iterator it=descriptors.begin();it!=descriptors.end(); ++it)
    {
        (*it)->PrintDescriptor();
    }
    SECTION_DEBUG("checksum_CRC32 : 0x%02x%02x%02x%02x \n",
                    (checksum_CRC32 >> 24) & 0xff,
                    (checksum_CRC32 >> 16) & 0xff,
                    (checksum_CRC32 >> 8) & 0xff,
                    checksum_CRC32 & 0xff);
    SECTION_DEBUG("====================================== \n\n");
}

} // end of sedec namespace
