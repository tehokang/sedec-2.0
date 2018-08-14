#if !defined __HYBRIDCAST_CONNECTION_REQUIREMENT_DESC___
#define __HYBRIDCAST_CONNECTION_REQUIREMENT_DESC___

#include <list>
#include <string.h>
#include "descriptor.h"
#include "base/bit_readwriter.h"
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

} // end of hybridcast namespace

/** @} */

} // end of sedec namespace

#endif
