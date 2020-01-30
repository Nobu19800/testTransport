// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file testDataPortStub.h 
 * @brief testDataPort client stub header wrapper code
 * @date Mon Jan 27 17:24:42 2020 
 *
 */

#ifndef TESTDATAPORTSTUB_H
#define TESTDATAPORTSTUB_H


#include <rtm/config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#if   defined ORB_IS_TAO
#  include "testDataPortC.h"
#elif defined ORB_IS_OMNIORB
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#    ifdef USE_stub_in_nt_dll
#        undef USE_stub_in_nt_dll
#    endif
#    ifdef OpenRTM_IMPORT_SYMBOL
#        define USE_stub_in_nt_dll
#    endif
#  endif
#  include "testDataPort.hh"
#elif defined ORB_IS_MICO
#  include "testDataPort.h"
#elif defined ORB_IS_ORBIT2
#  include "testDataPort-cpp-stubs.h"
#elif defined ORB_IS_RTORB
#  include "testDataPort.h"
#elif defined ORB_IS_ORBEXPRESS
#  include "testDataPort_c.h"
#else
#  error "NO ORB defined"
#endif

#endif // TESTDATAPORTSTUB_H
