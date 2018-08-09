// transport_protocol_descriptor.h: interface for the TransportProtocolDescriptor class.
//
//////////////////////////////////////////////////////////////////////
#if !defined __HYBRIDCAST_CONNECTION_REQUIREMENT_DESC___
#define __HYBRIDCAST_CONNECTION_REQUIREMENT_DESC___

#include <list>
#include <string.h>
#include "descriptor.h"

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

class ConnectionRequirementDescriptor : public Descriptor
{
public:	
    ConnectionRequirementDescriptor();
    ConnectionRequirementDescriptor(BitReadWriter *rw);
    virtual ~ConnectionRequirementDescriptor();

    virtual void WriteDescriptor(BitReadWriter* rw);
    virtual void PrintDescriptor();

    /* Interface to decode (getter) */
    bool GetIPConnectionRequirementFlag(){ return IP_connection_requirement_flag;}

protected:
    virtual void calcLength();

    bool IP_connection_requirement_flag;
};

/** @} */

} // end of hybridcast namespace

/** @} */

} // end of sedec namespace

#endif 
