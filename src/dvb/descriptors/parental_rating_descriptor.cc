#include "base/macro.h"
#include "descriptors/parental_rating_descriptor.h"

namespace sedec
{

namespace dvb
{

ParentalRatingDescriptor::ParentalRatingDescriptor()
{
    descriptor_tag = PARENTAL_RATING_DESCRIPTOR;
    descriptor_length = 0;
    m_parent_rating_count = 0;

    memset(country_code, 0x00, sizeof(country_code[64]));
    memset(rating, 0x00, sizeof(rating[64]));
}

ParentalRatingDescriptor::ParentalRatingDescriptor(base::BitReadWriter *rw) : Descriptor(rw)
{
    int j = 0;
    for(int i=descriptor_length;i>0;j++)
    {
        country_code[j] = rw->Read_On_Buffer(24);
        rating[j] = rw->Read_On_Buffer(8);
        i-=4;
        m_parent_rating_count = j+1;
    }
}

ParentalRatingDescriptor::~ParentalRatingDescriptor()
{

}

void ParentalRatingDescriptor::PrintDescriptor()
{
    SECTION_DEBUG("\n");
    SECTION_DEBUG("\tdescriptor_tag : 0x%02x (parental_rating_descriptor)\n", descriptor_tag);
    SECTION_DEBUG("\tdescriptor_length : 0x%x \n", descriptor_length);
    for(int j=0;j<m_parent_rating_count;j++)
    {
        SECTION_DEBUG("\t country_code[%d] : 0x%x \n", j, country_code[j]);
        SECTION_DEBUG("\t rating[%d] : 0x%x \n", j, rating[j]);
    }
    SECTION_DEBUG("\n");
}

void ParentalRatingDescriptor::calcLength()
{
    descriptor_length = m_parent_rating_count*4;
}

void ParentalRatingDescriptor::WriteDescriptor(base::BitReadWriter *rw)
{
    Descriptor::WriteDescriptor(rw);

    for(int i=0;i<m_parent_rating_count;i++)
    {
        rw->Write_On_Buffer(country_code[i], 24);
        rw->Write_On_Buffer(rating[i], 8);
    }
}

} // end of dvb namespace

} // end of sedec namespace
