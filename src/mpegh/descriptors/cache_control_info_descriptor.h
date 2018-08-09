// cache_control_info_descriptor.h: interface for the CacheControlInfoDescriptor class.
//
//////////////////////////////////////////////////////////////////////
#if !defined __MH_CACHE_CONTROL_INFO_DESCRIPTOR_H__
#define __MH_CACHE_CONTROL_INFO_DESCRIPTOR_H__

#include <list>
#include <string.h>
#include <stdlib.h>
#include "descriptor.h"

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

class BitReadWriter;

namespace mh
{
/**
    @addtogroup mh
    @{
*/

class CacheControlInfoDescriptor : public Descriptor
{
public:
    CacheControlInfoDescriptor();
    CacheControlInfoDescriptor(BitReadWriter *rw);
    virtual ~CacheControlInfoDescriptor();

    virtual void WriteDescriptor(BitReadWriter* rw);
    virtual void PrintDescriptor();

    void SetApplicationSize(unsigned int value) { application_size = value;}
    void SetCachePriority(unsigned char value) { cache_priority = value;}
    void SetPackageFlag(unsigned char value) { package_flag = value;}
    void SetApplicationVersion(unsigned char value) { application_version = value;}
    void SetExpire_date(unsigned int value) { expire_date = value;}

    unsigned int GetApplicationSize() { return application_size;}
    unsigned char GetCachePriority() { return cache_priority;}
    unsigned char GetPackageFlag() { return package_flag;}
    unsigned char GetApplicationVersion() { return application_version;}
    unsigned int GetExpire_date() { return expire_date;}

protected:
    virtual void calcLength();

    unsigned int application_size;
    unsigned char cache_priority;
    unsigned char package_flag;
    unsigned char application_version;
    unsigned int expire_date;
};

/** @} */

} // end of mh namespace

/** @} */

} // end of sedec namespace
#endif 
