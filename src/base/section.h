// Section.h: interface for the Section class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__SECTION_H__)
#define __SECTION_H__

#include "bit_readwriter.h"

namespace sedec
{
/**
 * @brief Contains classes to de/encode raw section/table of AIT
 */
namespace base
{
/**
    @addtogroup Sedec
    @{
*/

class Section  : public BitReadWriter
{
public:
    Section();
    /* Below constructor is to decode raw section */
    Section(unsigned char* raw_buffer, unsigned int raw_length);
    virtual ~Section();

    void EncodeSection();
    void SaveSection();
    void SaveSection(char *filename);
    int GetSectionLen();
    unsigned char* GetSection();

    void PrintRawSection();
    virtual void PrintSection()=0;

    static enum TABLE_ID
    {
        DVB_APPLICATION_INFORMATION_TABLE = 0x74,
        HC_APPLICATION_INFORMATION_TABLE = 0x74,
        MH_APPLICATION_INFORMATION_TABLE = 0x9C,
        UNKNOWN_TABLE = 0xff,
    }_SUPPORTED_TABLE_ID_;

protected:
    void ReadyBuffer();
    void WriteSectionHeader();
    void MakeCRC();

    virtual void WriteSection()=0;
    virtual void SetSection()=0;
    virtual void CalcSectionLength()=0;
    virtual void decode()=0;

    unsigned char* m_crc;
    unsigned int checksum_CRC32;
    int m_buffer_length;
    unsigned char* m_buffer;
    char *m_section_name;

    unsigned int table_id;
    unsigned int section_syntax_indicator;
    unsigned int section_length;
};

/** @} */

} // end of base namespace

/** @} */

} // end of sedec namespace
#endif
