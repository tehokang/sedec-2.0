#if !defined(__HYBRIDCAST_PMT_SECTION_H__)
#define __HYBRIDCAST_PMT_SECTION_H__

#include <list>
#include "base/table.h"

using namespace std;

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace hybridcast
{
/**
    @addtogroup hybridcast
    @{
*/

class Descriptor;

class ProgramMapTable : public base::Table
{
public:
    class Program
    {
    public:
        unsigned char stream_type;
        int elementary_PID;
        int ES_info_length;
        list<Descriptor*> descriptors;
    };

    ProgramMapTable();
    ProgramMapTable(unsigned char *raw_buffer);
    ProgramMapTable(unsigned char *raw_buffer, unsigned int raw_length);
    virtual ~ProgramMapTable();
    virtual void PrintTable();

protected:
    int program_number;
    unsigned char version_number;
    unsigned char current_next_indicator;
    unsigned char section_number;
    unsigned char last_section_number;
    int PCR_PID;
    int program_info_length;
    list<Descriptor*> descriptors;
    list<Program*> programs;

    virtual void __decode_table_body__();
};

/** @} */

} // end of hybridcast namespace

/** @} */

} // end of sedec namespace

#endif
