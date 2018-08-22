#if !defined(__SECTION_H__)
#define __SECTION_H__

#include "bit_readwriter.h"
#include <string>
using namespace std;

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

class Table  : public BitReadWriter
{
public:
    Table();
    Table(unsigned char* raw_buffer, unsigned int raw_length);
    virtual ~Table();

    void EncodeSection();
    void SaveSection(char *filename);
    int GetSectionLen();
    unsigned char* GetSection();

    void PrintRawSection();
    virtual void PrintSection();
    virtual void PrintSection(string section_name);

protected:
    /**
     * @warning PLEASE OVERRIDE TO PARSE YOUR SECTION TABLE
     * and this call have to be called in your section's constructor.
     */
    virtual void __decode_section_body__() = 0;

    /**
     * @note Please override followings if you want to modify original data with custom data
     * - __encode_write_section_body__
     * - __encode_preprare_section__
     * - __encode_update_section_length__
     */
    virtual void __encode_write_section_body__() {};
    virtual void __encode_preprare_section__() {};
    virtual void __encode_update_section_length__() {};

    unsigned char* m_crc;
    unsigned int checksum_CRC32;
    int m_buffer_length;
    unsigned char* m_buffer;

    unsigned int table_id;
    unsigned int section_syntax_indicator;
    unsigned int section_length;

private:
    void __decode_section_header__();

    void __encode_prepare_buffer__();
    void __encode_write_section_header__();
    void __encode_make_crc__();
};

class UnknownSection : public Table
{
public:
    UnknownSection();
    UnknownSection(unsigned char* raw_buffer, unsigned int raw_length);
    virtual ~UnknownSection();
    virtual void __decode_section_body__() override;

protected:
    virtual void updateDescriptorLength(){};
};

/** @} */

} // end of base namespace

/** @} */

} // end of sedec namespace
#endif
