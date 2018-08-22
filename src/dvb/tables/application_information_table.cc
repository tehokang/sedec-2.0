#include <string.h>
#include <cstddef>
#include <stdlib.h>

#include "base/macro.h"
#include "base/descriptor.h"

#include "descriptor_factory.h"
#include "descriptors/application.h"
#include "tables/application_information_table.h"

namespace sedec
{

using namespace dvb;

ApplicationInformationTable::ApplicationInformationTable()
{
    table_id = 0x74;
    section_syntax_indicator = 0x01;
    section_length = 0;
    test_application_flag = 0;
    application_type = 0; // hbbtv : 0x0010 | oipf : 0x0011
    version_number = 0;
    current_next_indicator = 0;
    section_number = 0;
    last_section_number = 0;
    common_descriptors_length = 0;
}

ApplicationInformationTable::ApplicationInformationTable(unsigned char *raw_buffer)
    : Table(raw_buffer, (( raw_buffer[1] << 8 | raw_buffer[2] ) & 0x0fff ) + 3)
{
    __decode_table_body__();
}


ApplicationInformationTable::ApplicationInformationTable(
        unsigned char *raw_buffer, unsigned int raw_length)
    : Table(raw_buffer, raw_length)
{
    __decode_table_body__();
}

ApplicationInformationTable::~ApplicationInformationTable()
{
    for (std::list<Descriptor*>::iterator it=common_descriptors.begin();
            it != common_descriptors.end(); ++it)
    {
        delete (*it);
    }

    for (std::list<Application*>::iterator it=applications.begin();
            it != applications.end(); ++it)
    {
        delete (*it);
    }

    applications.clear();
    common_descriptors.clear();
}

void ApplicationInformationTable::__decode_table_body__()
{
    test_application_flag = Read_On_Buffer(1);
    application_type = Read_On_Buffer(15);
    Skip_On_Buffer(2);
    version_number = Read_On_Buffer(5);
    current_next_indicator = Read_On_Buffer(1);
    section_number = Read_On_Buffer(8);
    last_section_number = Read_On_Buffer(8);
    Skip_On_Buffer(4);

    common_descriptors_length = Read_On_Buffer(12);
    for(int i=common_descriptors_length;i>0;)
    {
        Descriptor *desc = DescriptorFactory::CreateDescriptor(this);
        i-=desc->GetDescriptorLength();
        common_descriptors.push_back(desc);
    }
    Skip_On_Buffer(4);
    application_loop_length = Read_On_Buffer(12);
    for(int i=application_loop_length;i>0;)
    {
        Application *app = new Application(this);
        i-=app->GetApplicationLength();
        applications.push_back(app);
    }
    checksum_CRC32 = Read_On_Buffer(32);
}

void ApplicationInformationTable::PrintTable()
{
    SECTION_DEBUG("= AIT Section's raw information is followings ===== \n");
    Table::PrintTable();
    SECTION_DEBUG("test_application_flag : 0x%x \n", test_application_flag);
    SECTION_DEBUG("application_type : 0x%04x \n", application_type);
    SECTION_DEBUG("version_number : 0x%x \n", version_number);
    SECTION_DEBUG("current_next_indicator : %x \n", current_next_indicator);
    SECTION_DEBUG("section_number : 0x%x \n", section_number);
    SECTION_DEBUG("last_section_number : 0x%x \n", last_section_number);
    SECTION_DEBUG("common_descriptors_length : 0x%x (%d)\n",
                    common_descriptors_length, common_descriptors_length);

    for (std::list<Descriptor*>::iterator it=common_descriptors.begin();
            it != common_descriptors.end(); ++it)
    {
        ((Descriptor*)*it)->PrintDescriptor();
    }
    SECTION_DEBUG("application_loop_length : 0x%x (%d)\n",
                    application_loop_length, application_loop_length);
    int app_index=0;
    for (std::list<Application*>::iterator it=applications.begin();
            it != applications.end(); ++it)
    {
        SECTION_DEBUG("\n====== [%d] Application list ======\n", app_index++);
        ((Application*)*it)->PrintApplication();
        SECTION_DEBUG("======================================\n");
    }
    SECTION_DEBUG("checksum_CRC32 : 0x%02x%02x%02x%02x \n",
                    (checksum_CRC32 >> 24) & 0xff,
                    (checksum_CRC32 >> 16) & 0xff,
                    (checksum_CRC32 >> 8) & 0xff,
                    checksum_CRC32 & 0xff);
    SECTION_DEBUG("====================================== \n\n");
}

} // end of sedec namespace
