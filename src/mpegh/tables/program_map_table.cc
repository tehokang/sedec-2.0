#include <string.h>
#include <cstddef>
#include <stdlib.h>

#include "base/macro.h"

#include "descriptor_factory.h"
#include "descriptors/descriptor.h"
#include "tables/program_map_table.h"

namespace sedec
{

using namespace mpegh;

ProgramMapTable::ProgramMapTable()
{
    table_id = 0x01;
    section_syntax_indicator = 0x01;
    section_length = 0;
}

ProgramMapTable::ProgramMapTable(unsigned char *raw_buffer)
    : Table(raw_buffer, (( raw_buffer[1] << 8 | raw_buffer[2] ) & 0x0fff ) + 3)
{
    __decode_table_body__();
}


ProgramMapTable::ProgramMapTable(
        unsigned char *raw_buffer, unsigned int raw_length)
    : Table(raw_buffer, raw_length)
{
    __decode_table_body__();
}

ProgramMapTable::~ProgramMapTable()
{
    for (std::list<Descriptor*>::iterator it=descriptors.begin();
            it != descriptors.end(); ++it)
    {
        delete (*it);
    }

    descriptors.clear();
}

void ProgramMapTable::__decode_table_body__()
{
    program_number = Read_On_Buffer(16);
    Skip_On_Buffer(2);
    version_number = Read_On_Buffer(5);
    current_next_indicator = Read_On_Buffer(1);
    section_number = Read_On_Buffer(8);
    last_section_number = Read_On_Buffer(8);
    Skip_On_Buffer(3);
    PCR_PID = Read_On_Buffer(13);
    Skip_On_Buffer(4);
    program_info_length = Read_On_Buffer(12);

    for ( int i=program_info_length; i>0; )
    {
        Descriptor *desc = DescriptorFactory::CreateDescriptor(this);
        i-=desc->GetDescriptorLength();
        descriptors.push_back(desc);
    }

    for ( int i=(section_length-9-program_info_length-4); i>0; )
    {
        Program *program = new Program();
        program->stream_type = Read_On_Buffer(8);
        Skip_On_Buffer(3);
        program->elementary_PID = Read_On_Buffer(13);
        Skip_On_Buffer(4);
        program->ES_info_length = Read_On_Buffer(12);

        for ( int j=program->ES_info_length; j>0; )
        {
            Descriptor *desc = DescriptorFactory::CreateDescriptor(this);
            j-=desc->GetDescriptorLength();
            program->descriptors.push_back(desc);
        }
        i-= (5 + program->ES_info_length);
        programs.push_back(program);
    }
    checksum_CRC32 = Read_On_Buffer(32);
}

void ProgramMapTable::PrintTable()
{
    SECTION_DEBUG("= PAT Section's raw information is followings ===== \n");
    Table::PrintTable();

    SECTION_DEBUG("program_number : 0x%x \n", program_number);
    SECTION_DEBUG("version_number : 0x%x \n", version_number);
    SECTION_DEBUG("current_next_indicator : 0x%x \n", current_next_indicator);
    SECTION_DEBUG("section_number : 0x%x \n", section_number);
    SECTION_DEBUG("last_section_number : 0x%x \n", last_section_number);
    SECTION_DEBUG("PCR_PID : 0x%x \n", PCR_PID);
    SECTION_DEBUG("program_info_length : 0x%x \n", program_info_length);

    for ( list<Descriptor*>::iterator it=descriptors.begin();it!=descriptors.end(); ++it)
    {
        (*it)->PrintDescriptor();
    }

    int i=0;
    for ( list<Program*>::iterator it=programs.begin();it!=programs.end(); ++it)
    {
        Program *program = (*it);
        SECTION_DEBUG("\t[%d] Program \n", i);
        SECTION_DEBUG("\tstream_type : 0x%x \n", program->stream_type);
        SECTION_DEBUG("\telementary_PID : 0x%x \n", program->elementary_PID);
        SECTION_DEBUG("\tES_info_length : 0x%x \n", program->ES_info_length);

        for ( list<Descriptor*>::iterator it=program->descriptors.begin();
                it!=program->descriptors.end(); ++it)
        {
            (*it)->PrintDescriptor();
        }
    }

    SECTION_DEBUG("checksum_CRC32 : 0x%02x%02x%02x%02x \n",
                    (checksum_CRC32 >> 24) & 0xff,
                    (checksum_CRC32 >> 16) & 0xff,
                    (checksum_CRC32 >> 8) & 0xff,
                    checksum_CRC32 & 0xff);
    SECTION_DEBUG("====================================== \n\n");
}

} // end of sedec namespace
