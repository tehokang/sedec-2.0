#if !defined __MH_INFO_DESCRIPTOR_H__
#define __MH_INFO_DESCRIPTOR_H__

#include <string.h>
#include "base/bit_readwriter.h"
#include "descriptors/descriptor.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace mpegh
{
/**
    @addtogroup mpegh
    @{
*/

class InfoDescriptor : public Descriptor
{
public:
    InfoDescriptor();
    InfoDescriptor(base::BitReadWriter *rw);
    virtual ~InfoDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw);
    virtual void PrintDescriptor();

    /* Interface to encode (setter) */
    void SetTextChar(char *value)
    {
        memset(text_char, 0x00, sizeof(text_char));
        snprintf(text_char, sizeof(text_char),"%s", value);
        text_char_length = strlen(text_char);
    }

    void SetLanguageCode(unsigned char *value)
    {
        ISO_639_language_code[0] = value[0];
        ISO_639_language_code[1] = value[1];
        ISO_639_language_code[2] = value[2];
    }

    /* Interface to decode (getter) */
    unsigned char *GetLanguageCode(){ return ISO_639_language_code;}
    int GetTextCharLength() { return text_char_length;}
    char *GetTextChar() { return text_char;}

protected:
    virtual void updateDescriptorLength() override;

    unsigned char ISO_639_language_code[3];
    int text_char_length;
    char text_char[256];
};

/** @} */

} // end of mpegh namespace

/** @} */

} // end of sedec namespace

#endif
