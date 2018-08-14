#if !defined __DVB_CONNECTION_REQUIREMENT_DESC___
#define __DVB_CONNECTION_REQUIREMENT_DESC___

#include <list>
#include <string.h>
#include "base/bit_readwriter.h"
#include "descriptors/descriptor.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace dvb
{
/**
    @addtogroup dvb
    @{
*/

class ConnectionRequirementDescriptor : public Descriptor
{
public:
    ConnectionRequirementDescriptor();
    ConnectionRequirementDescriptor(base::BitReadWriter *rw);
    virtual ~ConnectionRequirementDescriptor();

    virtual void WriteDescriptor(base::BitReadWriter* rw) override;
    virtual void PrintDescriptor() override;

    /* Interface to decode (getter) */
    bool GetIPConnectionRequirementFlag(){ return IP_connection_requirement_flag;}

protected:
    virtual void updateDescriptorLength() override;

    bool IP_connection_requirement_flag;
};

/** @} */

} // end of dvb namespace

/** @} */

} // end of sedec namespace

#endif
