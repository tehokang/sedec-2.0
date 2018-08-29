#include <stdlib.h>
#include <string.h>
#include "base/macro.h"
#include "descriptors/application_name_descriptor.h"

namespace sedec
{

namespace arib::b24
{

ApplicationNameDescriptor::ApplicationNameDescriptor()
{
    descriptor_tag = 0x01;
    descriptor_length = 0;
    memset(ISO_639_language_code, 0x00, sizeof(ISO_639_language_code));
    application_name_length = 0;
    memset(application_name, 0x00, sizeof(application_name));
}

ApplicationNameDescriptor::ApplicationNameDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    memset(ISO_639_language_code, 0x00, sizeof(ISO_639_language_code));
    application_name_length = 0;
    memset(application_name, 0x00, sizeof(application_name));

    for(int i=descriptor_length;i>0;)
    {
        ISO_639_language_code[0] = rw->Read_On_Buffer(8);
        ISO_639_language_code[1] = rw->Read_On_Buffer(8);
        ISO_639_language_code[2] = rw->Read_On_Buffer(8);
        application_name_length = rw->Read_On_Buffer(8);
        for(int j=0;j<application_name_length;j++)
        {
            application_name[j] = rw->Read_On_Buffer(8);
        }
        i-=(4+application_name_length);
    }
}

ApplicationNameDescriptor::~ApplicationNameDescriptor()
{

}
void ApplicationNameDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    Descriptor::PrintDescriptor("ApplicationNameDescriptor");

    for(int i=descriptor_length;i>0;)
    {
        SECTION_DEBUG("\tISO_639_languahe_code[0] : 0x%x(%c) \n",
                        ISO_639_language_code[0],ISO_639_language_code[0]);
        SECTION_DEBUG("\tISO_639_languahe_code[1] : 0x%x(%c) \n",
                        ISO_639_language_code[1],ISO_639_language_code[1]);
        SECTION_DEBUG("\tISO_639_languahe_code[2] : 0x%x(%c) \n",
                        ISO_639_language_code[2],ISO_639_language_code[2]);
        SECTION_DEBUG("\tapplication_name_length : 0x%x \n", application_name_length);
        SECTION_DEBUG("\tapplication_name : %s \n", application_name);
        i-=(4+application_name_length);
    }
    SECTION_DEBUG("\n");
}

void ApplicationNameDescriptor::updateDescriptorLength()
{
    descriptor_length = 4 + strlen((char*)application_name);
}

void ApplicationNameDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    if( 0 < descriptor_length )
    {
        rw->Write_On_Buffer(ISO_639_language_code[0], 8);
        rw->Write_On_Buffer(ISO_639_language_code[1], 8);
        rw->Write_On_Buffer(ISO_639_language_code[2], 8);
        rw->Write_On_Buffer(application_name_length, 8);

        for(int i=0;i<application_name_length;i++)
        {
            rw->Write_On_Buffer(application_name[i], 8);
        }
    }
}

} // end of hybridcast namespace

} // end of sedec namespace

