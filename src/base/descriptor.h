#if !defined __DESCRIPTOR_H__
#define __DESCRIPTOR_H__

#include <string>
using namespace std;

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace base
{
/**
    @addtogroup base
    @{
*/

class BitReadWriter;
class Descriptor
{
public:
    Descriptor();
    Descriptor(BitReadWriter *rw);
    virtual ~Descriptor();

    int GetDescriptorLength();
    int GetDescriptorTag();

    virtual void WriteDescriptor(BitReadWriter* rw);
    virtual void PrintDescriptor();
    virtual void PrintDescriptor(string descriptor_name);

protected:
    virtual void updateDescriptorLength() = 0;

    int descriptor_tag;
    int descriptor_length;
};

class UnknownDescriptor : public Descriptor
{
public:
    UnknownDescriptor();
    UnknownDescriptor(BitReadWriter *rw);
    virtual ~UnknownDescriptor();

    virtual void WriteDescriptor(BitReadWriter* rw){};

protected:
    virtual void updateDescriptorLength(){};
};

/** @} */

} // end of base namespace

/** @} */

} // end of sedec namespace
#endif
