#include "base/macro.h"

#include "descriptor_factory.h"
#include "descriptors/descriptor.h"
#include "descriptors/application.h"

#include "descriptors/application_descriptor.h"
#include "descriptors/simple_application_location_descriptor.h"
#include "descriptors/transport_protocol_descriptor.h"

namespace sedec
{

namespace dvb
{

Application::Application()
{
    organization_id = 0;
    application_id = 0;
    application_control_code = 0;
    application_descriptors_loop_length = 0;
    m_application_length = 0;
}

Application::Application(base::BitReadWriter *rw)
{
    organization_id = rw->Read_On_Buffer(32);
    application_id = rw->Read_On_Buffer(16);
    application_control_code = rw->Read_On_Buffer(8);
    rw->Skip_On_Buffer(4);
    application_descriptors_loop_length = rw->Read_On_Buffer(12);
    for(int i=application_descriptors_loop_length;i>0;)
    {
        Descriptor *desc = DescriptorFactory::CreateDescriptor(rw);
        i-=desc->GetDescriptorLength();
        application_descriptors.push_back(desc);
    }
}

Application::~Application()
{
    for (std::list<Descriptor*>::iterator it=application_descriptors.begin();
            it != application_descriptors.end(); ++it)
    {
        delete (*it);
    }
    application_descriptors.clear();
}

void Application::PrintApplication()
{
    SECTION_DEBUG("organization_id : 0x%08x \n", organization_id);
    SECTION_DEBUG("application_id : 0x%04x \n", application_id);
    SECTION_DEBUG("application_control_code : 0x%x \n", application_control_code);
    SECTION_DEBUG("application_descriptors_loop_length : 0x%x (%d)\n",
                    application_descriptors_loop_length, application_descriptors_loop_length);

    for (std::list<Descriptor*>::iterator it=application_descriptors.begin();
            it != application_descriptors.end(); ++it)
    {
        Descriptor *desc = (Descriptor*)*it;
        desc->PrintDescriptor();
    }
}

int Application::GetApplicationLength()
{
    updateDescriptorLength();
    return m_application_length;
}

void Application::updateDescriptorLength()
{
    application_descriptors_loop_length = 0;
    for (std::list<Descriptor*>::iterator it=application_descriptors.begin();
            it != application_descriptors.end(); ++it)
    {
        Descriptor *desc = (Descriptor*)*it;
        application_descriptors_loop_length+=desc->GetDescriptorLength();
    }
    /* application_identifier + control_code + app_loop_length */
    m_application_length = (9+application_descriptors_loop_length);
}

void Application::WriteApplication(base::BitReadWriter *rw)
{
    rw->Write_On_Buffer(organization_id, 32);
    rw->Write_On_Buffer(application_id, 16);
    rw->Write_On_Buffer(application_control_code, 8);
    rw->Write_On_Buffer(0x0f, 4);
    rw->Write_On_Buffer(application_descriptors_loop_length, 12);

    for (std::list<Descriptor*>::iterator it=application_descriptors.begin();
                it != application_descriptors.end(); ++it)
    {
        Descriptor *desc = (Descriptor*)*it;
        desc->WriteDescriptor(rw);
    }
}

} // end of dvb namespace

} // end of sedec namespace
