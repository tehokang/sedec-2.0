#include "macro.h"
#include "table.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

namespace sedec
{

namespace base
{

Table::Table()
{
    m_buffer = NULL;
    m_buffer_length = 0;
}

Table::Table(unsigned char* raw_buffer, unsigned int raw_length)
{
    m_buffer_length = raw_length;
    m_buffer = new unsigned char[m_buffer_length];
    memcpy(m_buffer, raw_buffer, m_buffer_length);
    SetBuffer(m_buffer);

    __decode_table_header__();
}

Table::~Table()
{
    if(m_buffer != NULL)
    {
        delete []m_buffer;
    }
}

void Table::__decode_table_header__()
{
    table_id = Read_On_Buffer(8);
    section_syntax_indicator = Read_On_Buffer(1);
    Skip_On_Buffer(3);
    section_length = Read_On_Buffer(12);
}

void Table::__encode_prepare_buffer__()
{
    if(m_buffer != NULL)
    {
        delete []m_buffer;
    }
    m_buffer_length = section_length + 3;
    m_buffer = new unsigned char[m_buffer_length];

    memset(m_buffer, 0xFF, m_buffer_length);
    SetBuffer(m_buffer);
}

void Table::__encode_write_table_header__()
{
    Write_On_Buffer( table_id, 8 );
    Write_On_Buffer( section_syntax_indicator, 1);
    Write_On_Buffer( 1, 1);
    Write_On_Buffer( 3, 2);
    Write_On_Buffer( section_length, 12);
}

void Table::EncodeTable()
{
    __encode_update_table_length__();
    __encode_preprare_table__();

    __encode_prepare_buffer__();
    __encode_write_table_header__();
    __encode_write_table_body__();
    __encode_make_crc__();
}

void Table::__encode_make_crc__()
{
    m_crc = new unsigned char[section_length-1];
    memcpy( m_crc, m_buffer, section_length-1 );
    checksum_CRC32 = calculate_crc32( m_crc, section_length-1 );
    delete []m_crc;

    Write_On_Buffer(checksum_CRC32, 32);
}


void Table::SaveTable(char *filename)
{
    FILE *fp = NULL;
    fp = fopen(filename, "wb");
    if(fp)
    {
        fwrite(m_buffer, 1, m_buffer_length, fp);
        fclose(fp);
    }
}

void Table::PrintRawTable()
{
    int j=1;
    SECTION_PRINT("#### Section Byte Align #### \n");
    SECTION_PRINT("%03d : ", j);
    for(int i=0; i<m_buffer_length; i++)
    {
        SECTION_PRINT("%02X ", m_buffer[i]);
        if(i%10 == 9) printf("\n%03d : ", ++j);
    }
    SECTION_PRINT("\n################################### \n\n");
}

unsigned char* Table::GetSection()
{
    return m_buffer;
}

int Table::GetSectionLen()
{
    return m_buffer_length;
}

void Table::PrintTable()
{
    SECTION_PRINT("===== Section's information ===== \n");
    SECTION_PRINT("table_id : 0x%x \n", table_id);
    SECTION_PRINT("section_syntax_indicator : 0x%x \n", section_syntax_indicator);
    SECTION_PRINT("section_length : 0x%x (%d) \n", section_length, section_length);
}

void Table::PrintTable(string section_name)
{
    SECTION_PRINT("===== Section's information ===== \n");
    SECTION_PRINT("table_id : 0x%x (%s)\n", table_id, section_name.c_str());
    SECTION_PRINT("section_syntax_indicator : 0x%x \n", section_syntax_indicator);
    SECTION_PRINT("section_length : 0x%x (%d) \n", section_length, section_length);
}

UnknownSection::UnknownSection()
    : Table()
{

}

UnknownSection::UnknownSection(unsigned char* raw_buffer, unsigned int raw_length)
    : Table(raw_buffer, raw_length)
{
    /**
     * @note NOTHING TO DO
     */
}

UnknownSection::~UnknownSection()
{
    /**
     * @note NOTHING TO DO
     */
}

void UnknownSection::__decode_table_body__()
{
    /**
     * @note NOTHING TO DO
     */
}

} // end of base namespace

} // end of sedec namespace
