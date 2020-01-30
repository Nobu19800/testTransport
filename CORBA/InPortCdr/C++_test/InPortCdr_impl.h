// -*-C++-*-
/*!
 * @file  CORBASVC_impl.h
 * @brief 
 *
 */

#ifndef CORBASVC_IMPL_H
#define CORBASVC_IMPL_H

#include <vector>
#include <mutex>
#include <fstream>

#include <rtm/idl/InterfaceDataTypesSkel.h>
#include "testDataPortSkel.h"



/*
 * 
 */
class InPortCdrSVC
  : public virtual POA_testOpenRTM::InPortCdr
{
 public:
   InPortCdrSVC();
   ~InPortCdrSVC() override;
   testOpenRTM::PortStatus put(const ::testOpenRTM::CdrData& data) override;
   testOpenRTM::PortStatus put(cdrMemoryStream& data) override;
   testOpenRTM::PortStatus put(cdrStream& data) override;
   void save(CORBA::ULong newsize);

private:
    std::ofstream m_file;
    std::vector<double> m_data;
    CORBA::ULong m_datasize;
    RTC::CameraImage m_image_data;
    std::mutex m_mu;

#ifdef ORB_IS_ORBEXPRESS
    CORBA::Stream m_cdr;
#elif defined(ORB_IS_TAO)
    TAO_OutputCDR m_cdr;
#else
    cdrMemoryStream m_cdr;
#endif
};



#endif // MYSERVICESVC_IMPL_H


