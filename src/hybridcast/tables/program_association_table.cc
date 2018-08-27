#include <string.h>
#include <cstddef>
#include <stdlib.h>

#include "base/macro.h"
#include "base/descriptor.h"

#include "descriptor_factory.h"
#include "tables/program_association_table.h"

namespace sedec
{

using namespace hybridcast;

ProgramAssociationTable::ProgramAssociationTable()
{
    table_id = 0x00;
    section_syntax_indicator = 0x01;
    section_length = 0;
}

ProgramAssociationTable::ProgramAssociationTable(unsigned char *raw_buffer)
    : Table(raw_buffer, (( raw_buffer[1] << 8 | raw_buffer[2] ) & 0x0fff ) + 3)
{
    __decode_table_body__();
}


ProgramAssociationTable::ProgramAssociationTable(
        unsigned char *raw_buffer, unsigned int raw_length)
    : Table(raw_buffer, raw_length)
{
    __decode_table_body__();
}

ProgramAssociationTable::~ProgramAssociationTable()
{
    for (std::list<Program*>::iterator it=programs.begin();
            it != programs.end(); ++it)
    {
        delete (*it);
    }

    programs.clear();
}

void ProgramAssociationTable::__decode_table_body__()
{
    transport_stream_id = Read_On_Buffer(16);
    Skip_On_Buffer(2);
    version_number = Read_On_Buffer(5);
    current_next_indicator = Read_On_Buffer(1);
    section_number = Read_On_Buffer(8);
    last_section_number = Read_On_Buffer(8);

    for ( int i=(section_length-9); i>0; )
    {
        int program_number = Read_On_Buffer(16);
        Skip_On_Buffer(3);
        int pid = Read_On_Buffer(13);
        Program *program = new Program(program_number, pid);
        programs.push_back(program);
        i-=4;
    }
    checksum_CRC32 = Read_On_Buffer(32);
}

void ProgramAssociationTable::PrintTable()
{
    Table::PrintTable("ProgramAssociationTable");

    SECTION_DEBUG("transport_stream_id : 0x%x \n", transport_stream_id);
    SECTION_DEBUG("version_number : 0x%x \n", version_number);
    SECTION_DEBUG("current_next_indicator : 0x%x \n", current_next_indicator);
    SECTION_DEBUG("section_number : 0x%x \n", section_number);
    SECTION_DEBUG("last_section_number : 0x%x \n", last_section_number);

    for ( list<Program*>::iterator it=programs.begin();it!=programs.end(); ++it)
    {
        SECTION_DEBUG("\tprogram_number : 0x%x \n", (*it)->program_number);
        SECTION_DEBUG("\tpid : 0x%x \n", (*it)->pid);
    }
    SECTION_DEBUG("checksum_CRC32 : 0x%02x%02x%02x%02x \n",
                    (checksum_CRC32 >> 24) & 0xff,
                    (checksum_CRC32 >> 16) & 0xff,
                    (checksum_CRC32 >> 8) & 0xff,
                    checksum_CRC32 & 0xff);
    SECTION_DEBUG("====================================== \n\n");
}

} // end of sedec namespace
