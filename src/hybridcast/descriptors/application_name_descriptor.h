// application_name_descriptor.h: interface for the ApplicationNameDescriptor class.
//
//////////////////////////////////////////////////////////////////////
#if !defined __HYBRIDCAST_APPLICATION_NAME_DESCRIPTOR_H__
#define __HYBRIDCAST_APPLICATION_NAME_DESCRIPTOR_H__

#include "descriptor.h"
#include <string.h>

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

class BitReadWriter;

namespace hybridcast
{
/**
    @addtogroup hybridcast
    @{
*/

class ApplicationNameDescriptor : public Descriptor
{
public:	
    ApplicationNameDescriptor();
    ApplicationNameDescriptor(BitReadWriter *rw);
    virtual ~ApplicationNameDescriptor();

    virtual void WriteDescriptor(BitReadWriter* rw);
    virtual void PrintDescriptor();

    /* Interface to encode (setter) */
    void SetApplicationName(char *value)
    {
        memset(application_name, 0x00, sizeof(application_name));
        snprintf(application_name, sizeof(application_name),"%s", value);
        application_name_length = strlen(application_name);
    }
    void SetLanguageCode(unsigned char *value)
    {
        ISO_639_language_code[0] = value[0];
        ISO_639_language_code[1] = value[1];
        ISO_639_language_code[2] = value[2];
    }

    /* Interface to decode (getter) */
    unsigned char *GetLanguageCode(){ return ISO_639_language_code;}
    int GetApplicationNameLength() { return application_name_length;}
    char *GetApplicationName() { return application_name;}

protected:
    virtual void calcLength();

    unsigned char ISO_639_language_code[3];
    int application_name_length;
    char application_name[256];
};

/** @} */

} // end of hybridcast namespace
/** @} */

} // end of sedec namespace

#endif 
