#if !defined(__MPEGH_PAT_SECTION_H__)
#define __MPEGH_PAT_SECTION_H__

#include <list>
#include "base/table.h"

using namespace std;

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace mpegh
{
/**
    @addtogroup dvb
    @{
*/

class Descriptor;

class ProgramAssociationTable : public base::Table
{
public:
    class Program
    {
    public:
        Program(int _program_number, int _pid)
        {
            program_number = _program_number;
            pid = _pid;
        }
        int program_number;
        int pid;
    };
    ProgramAssociationTable();
    ProgramAssociationTable(unsigned char *raw_buffer);
    ProgramAssociationTable(unsigned char *raw_buffer, unsigned int raw_length);
    virtual ~ProgramAssociationTable();
    virtual void PrintTable();


protected:
    int transport_stream_id;
    unsigned char version_number;
    unsigned char current_next_indicator;
    unsigned char section_number;
    unsigned char last_section_number;
    list<Program*> programs;
    virtual void __decode_table_body__();
};

/** @} */

} // end of mpeg namespace

/** @} */

} // end of sedec namespace

#endif
