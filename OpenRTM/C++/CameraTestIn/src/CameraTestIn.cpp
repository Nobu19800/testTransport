// -*- C++ -*-
/*!
 * @file  CameraTestIn.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "CameraTestIn.h"

// Module specification
// <rtc-template block="module_spec">
static const char* cameratestin_spec[] =
  {
    "implementation_id", "CameraTestIn",
    "type_name",         "CameraTestIn",
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
CameraTestIn::CameraTestIn(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inIn("in", m_in), m_datalistener(nullptr)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
CameraTestIn::~CameraTestIn()
{
}



RTC::ReturnCode_t CameraTestIn::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in", m_inIn);
  m_datalistener = new DataListener(m_file);
  m_inIn.addConnectorDataListener(ON_BUFFER_WRITE,
                                    m_datalistener);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CameraTestIn::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraTestIn::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraTestIn::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t CameraTestIn::onActivated(RTC::UniqueId ec_id)
{
  m_file.open("cameratestin.txt");
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CameraTestIn::onDeactivated(RTC::UniqueId ec_id)
{
  m_datalistener->save(0);
  m_file.close();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CameraTestIn::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CameraTestIn::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraTestIn::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraTestIn::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraTestIn::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CameraTestIn::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void CameraTestInInit(RTC::Manager* manager)
  {
    coil::Properties profile(cameratestin_spec);
    manager->registerFactory(profile,
                             RTC::Create<CameraTestIn>,
                             RTC::Delete<CameraTestIn>);
  }
  
};


