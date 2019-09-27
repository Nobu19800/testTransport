// -*- C++ -*-
/*!
 * @file  CameraTestOut.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "CameraTestOut.h"

// Module specification
// <rtc-template block="module_spec">
static const char* cameratestout_spec[] =
  {
    "implementation_id", "CameraTestOut",
    "type_name",         "CameraTestOut",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
CameraTestOut::CameraTestOut(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_outOut("out", m_out)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
CameraTestOut::~CameraTestOut()
{
}



RTC::ReturnCode_t CameraTestOut::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("out", m_outOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CameraTestOut::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraTestOut::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraTestOut::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t CameraTestOut::onActivated(RTC::UniqueId ec_id)
{
  datasize = 100;
  count = 0;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CameraTestOut::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CameraTestOut::onExecute(RTC::UniqueId ec_id)
{
  static const int maxsize = 1200001;
  const int datacount = 500;
  if(datasize > maxsize)
  {
    std::cout << "finish" << std::endl;
    return RTC::RTC_ERROR;
  }

  static double logmul[] = {2.0, 2.5, 2.0};

  
  m_out.height = 100;
  m_out.width = datasize/m_out.height/3;
  m_out.format = CORBA::string_dup("rgb8");
  m_out.pixels.length(m_out.height*m_out.width*3);
  setTimestamp(m_out);
  m_outOut.write();
  
  //if(count%5 == 4)
  //  datasize += 5000;
  
  ++count;
  
  
  if(count%datacount == 0)
    {
      std::cout << m_out.height*m_out.width*3 << std::endl;
      //std::cout << datasize << std::endl;
      //std::cout << m_out.height << std::endl;
      //std::cout << m_out.width << std::endl;
      datasize = static_cast<int>(static_cast<double>(datasize)*logmul[(count/datacount)%3]);
    }
  
    

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CameraTestOut::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraTestOut::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraTestOut::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraTestOut::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraTestOut::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void CameraTestOutInit(RTC::Manager* manager)
  {
    coil::Properties profile(cameratestout_spec);
    manager->registerFactory(profile,
                             RTC::Create<CameraTestOut>,
                             RTC::Delete<CameraTestOut>);
  }
  
};


