// -*-C++-*-
/*!
 * @file  CORBASVC_impl.h
 * @brief 
 *
 */

#ifndef CORBASVC_IMPL_H
#define CORBASVC_IMPL_H

#include "testServiceSkel.h"
#include <vector>
#include <mutex>
#include <fstream>

/*
 * 
 */
class CORBASVC_impl
  : public virtual POA_testOpenRTM::testService
{
 public:
   CORBASVC_impl();
   ~CORBASVC_impl() override;
   void put(const ::RTC::CameraImage& data) override;
   void save(CORBA::ULong newsize);

private:
    std::ofstream m_file;
    std::vector<double> m_data;
    CORBA::ULong m_datasize;
    std::mutex m_mu;
};



#endif // MYSERVICESVC_IMPL_H


