﻿// -*- C++ -*-
/*!
 * @file  CameraTestIn.h
 * @brief ModuleDescription
 * @date  $Date$
 *
 * $Id$
 */

#ifndef CAMERATESTIN_H
#define CAMERATESTIN_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "InterfaceDataTypesStub.h"

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="port_stub_h">
// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <iostream>

using namespace RTC;


class DataListener
  : public RTC::ConnectorDataListenerT<RTC::CameraImage>
{
  USE_CONNLISTENER_STATUS;
public:
  DataListener(std::ofstream& file) : m_file(file), m_datasize(0) {}
  ~DataListener() override
  {
  }

  ReturnCode operator()(RTC::ConnectorInfo& info,
                                RTC::CameraImage& data) override
  {
    std::lock_guard<std::mutex> guard(m_mu);
    
    if(!m_data.empty() && m_datasize != data.pixels.length())
    {
      save(data.pixels.length());
    }

    auto end = std::chrono::system_clock::now().time_since_epoch();
    auto start = std::chrono::seconds(data.tm.sec) + std::chrono::nanoseconds(data.tm.nsec);
    double diff = std::chrono::duration<double>(end - start).count();

    m_data.push_back(diff);
    m_times.push_back(end);

    /*
    auto start_ser1 = std::chrono::system_clock::now().time_since_epoch();
    m_cdr.rewindPtrs();
    m_cdr.setByteSwapFlag(true);
    data >>= m_cdr;
    auto start_ser2 = std::chrono::system_clock::now().time_since_epoch();
    data <<= m_cdr;
    auto end_des = std::chrono::system_clock::now().time_since_epoch();

    double diff_ser = std::chrono::duration<double>(start_ser2 - start_ser1).count();
    double diff_des = std::chrono::duration<double>(end_des - start_ser2).count();

    m_serialize_time.push_back(diff_ser);
    m_deserialize_time.push_back(diff_des);
    */
    
    m_datasize = data.pixels.length();

    return NO_CHANGE;
  }
  
  void save(CORBA::ULong newsize)
  {
    if(m_data.size() == 0)
    {
      m_datasize = newsize;
      return;
    }
    double avg = 0;
    for(const auto &data:m_data)
    {
      avg += data;
    }
    avg /= m_data.size();

    double throuput = 0;
    int count = 0;
    std::chrono::nanoseconds start;
    for(const auto &data:m_times)
    {
      if(count > 0)
      {
        double diff = std::chrono::duration<double>(data - start).count();
        throuput += static_cast<double>(m_datasize * 8) / diff;
      }
      count++;
      start = data;
    }
    throuput /= (m_times.size()-1);

    /*
    double serialize_time = 0;
    for(const auto &data:m_serialize_time)
    {
      serialize_time += data;
    }
    serialize_time /= m_serialize_time.size();

    double deserialize_time = 0;
    for(const auto &data:m_deserialize_time)
    {
      deserialize_time += data;
    }
    deserialize_time /= m_deserialize_time.size();
    */

    
    //std::cout << m_datasize << "\t" << avg << "\t" << throuput << "\t" << m_data.size() << "\t" << serialize_time << "\t" << deserialize_time << std::endl;
    //m_file << m_datasize << "\t" << avg << "\t" << throuput << "\t" << m_data.size() << "\t" << serialize_time << "\t" << deserialize_time << std::endl;

    std::cout << m_datasize << "\t" << avg << "\t" << throuput << "\t" << m_data.size() << std::endl;
    m_file << m_datasize << "\t" << avg << "\t" << throuput << "\t" << m_data.size() << std::endl;
    m_data.clear();
    m_times.clear();

    //m_serialize_time.clear();
    //m_deserialize_time.clear();

    m_datasize = newsize;
  }
private:
  std::ofstream& m_file;
  std::vector<double> m_data;
  std::vector<std::chrono::nanoseconds> m_times;
  CORBA::ULong m_datasize;
  std::mutex m_mu;
  cdrMemoryStream m_cdr;
  //std::vector<double> m_serialize_time;
  //std::vector<double> m_deserialize_time;
};

/*!
 * @class CameraTestIn
 * @brief ModuleDescription
 *
 */
class CameraTestIn
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  CameraTestIn(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~CameraTestIn();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::CameraImage m_in;
  /*!
   */
  InPort<RTC::CameraImage> m_inIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
  
  std::ofstream m_file;
  DataListener* m_datalistener;
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void CameraTestInInit(RTC::Manager* manager);
};

#endif // CAMERATESTIN_H
