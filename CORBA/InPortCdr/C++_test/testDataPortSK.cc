// This file is generated by omniidl (C++ backend)- omniORB_4_2. Do not edit.

#include "testDataPort.hh"
#include <omniORB4/IOP_S.h>
#include <omniORB4/IOP_C.h>
#include <omniORB4/callDescriptor.h>
#include <omniORB4/callHandle.h>
#include <omniORB4/objTracker.h>
#include <omniORB4/internal/giopStream.h>
#include <iostream>
#include <rtm/idl/InterfaceDataTypesSkel.h>

OMNI_USING_NAMESPACE(omni)

static const char* _0RL_library_version = omniORB_4_2;





testOpenRTM::InPortCdr_ptr testOpenRTM::InPortCdr_Helper::_nil() {
  return ::testOpenRTM::InPortCdr::_nil();
}

::CORBA::Boolean testOpenRTM::InPortCdr_Helper::is_nil(::testOpenRTM::InPortCdr_ptr p) {
  return ::CORBA::is_nil(p);

}

void testOpenRTM::InPortCdr_Helper::release(::testOpenRTM::InPortCdr_ptr p) {
  ::CORBA::release(p);
}

void testOpenRTM::InPortCdr_Helper::marshalObjRef(::testOpenRTM::InPortCdr_ptr obj, cdrStream& s) {
  ::testOpenRTM::InPortCdr::_marshalObjRef(obj, s);
}

testOpenRTM::InPortCdr_ptr testOpenRTM::InPortCdr_Helper::unmarshalObjRef(cdrStream& s) {
  return ::testOpenRTM::InPortCdr::_unmarshalObjRef(s);
}

void testOpenRTM::InPortCdr_Helper::duplicate(::testOpenRTM::InPortCdr_ptr obj) {
  if (obj && !obj->_NP_is_nil())  omni::duplicateObjRef(obj);
}

testOpenRTM::InPortCdr_ptr
testOpenRTM::InPortCdr::_duplicate(::testOpenRTM::InPortCdr_ptr obj)
{
  if (obj && !obj->_NP_is_nil())  omni::duplicateObjRef(obj);
  return obj;
}

testOpenRTM::InPortCdr_ptr
testOpenRTM::InPortCdr::_narrow(::CORBA::Object_ptr obj)
{
  if (!obj || obj->_NP_is_nil() || obj->_NP_is_pseudo()) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_realNarrow(_PD_repoId);
  return e ? e : _nil();
}


testOpenRTM::InPortCdr_ptr
testOpenRTM::InPortCdr::_unchecked_narrow(::CORBA::Object_ptr obj)
{
  if (!obj || obj->_NP_is_nil() || obj->_NP_is_pseudo()) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_uncheckedNarrow(_PD_repoId);
  return e ? e : _nil();
}

testOpenRTM::InPortCdr_ptr
testOpenRTM::InPortCdr::_nil()
{
#ifdef OMNI_UNLOADABLE_STUBS
  static _objref_InPortCdr _the_nil_obj;
  return &_the_nil_obj;
#else
  static _objref_InPortCdr* _the_nil_ptr = 0;
  if (!_the_nil_ptr) {
    omni::nilRefLock().lock();
    if (!_the_nil_ptr) {
      _the_nil_ptr = new _objref_InPortCdr;
      registerNilCorbaObject(_the_nil_ptr);
    }
    omni::nilRefLock().unlock();
  }
  return _the_nil_ptr;
#endif
}

const char* testOpenRTM::InPortCdr::_PD_repoId = "IDL:testOpenRTM/InPortCdr:1.0";


testOpenRTM::_objref_InPortCdr::~_objref_InPortCdr() {
  
}


testOpenRTM::_objref_InPortCdr::_objref_InPortCdr(omniIOR* ior, omniIdentity* id) :
   omniObjRef(::testOpenRTM::InPortCdr::_PD_repoId, ior, id, 1)
   ,
   _shortcut(0)
{
  _PR_setobj(this);
}

void*
testOpenRTM::_objref_InPortCdr::_ptrToObjRef(const char* id)
{
  if (id == ::testOpenRTM::InPortCdr::_PD_repoId)
    return (::testOpenRTM::InPortCdr_ptr) this;
  
  if (id == ::CORBA::Object::_PD_repoId)
    return (::CORBA::Object_ptr) this;

  if (omni::strMatch(id, ::testOpenRTM::InPortCdr::_PD_repoId))
    return (::testOpenRTM::InPortCdr_ptr) this;
  
  if (omni::strMatch(id, ::CORBA::Object::_PD_repoId))
    return (::CORBA::Object_ptr) this;

  return 0;
}

void
testOpenRTM::_objref_InPortCdr::_enableShortcut(omniServant* _svt, const _CORBA_Boolean* _inv)
{
  if (_svt)
    _shortcut = (_impl_InPortCdr*)_svt->_ptrToInterface(::testOpenRTM::InPortCdr::_PD_repoId);
  else
    _shortcut = 0;
  _invalid  = _inv;
  
}


//
// Code for testOpenRTM::InPortCdr::put

// Proxy call descriptor class. Mangled signature:
//  _ctestOpenRTM_mPortStatus_i_ctestOpenRTM_mCdrData
class _0RL_cd_acfd8f3c9dc70dc8_00000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_acfd8f3c9dc70dc8_00000000(LocalCallFn lcfn, const char* op_, size_t oplen, _CORBA_Boolean upcall=0)
    : omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  testOpenRTM::CdrData_var arg_0_;
  const testOpenRTM::CdrData* arg_0;
  cdrMemoryStream* argc_0;
  cdrMemoryStream argc_0_;
  testOpenRTM::PortStatus result;
};

void _0RL_cd_acfd8f3c9dc70dc8_00000000::marshalArguments(cdrStream& _n)
{

  argc_0->copy_to(_n, argc_0->bufSize());
}

void _0RL_cd_acfd8f3c9dc70dc8_00000000::unmarshalArguments(cdrStream& _n)
{
  
  cdrMemoryStream cdr;
  cdr.put_octet_array((CORBA::Octet*)_n.inPtr(),4);
  CORBA::ULong bufsize;
  bufsize <<= cdr;

  _n.copy_to(argc_0_, bufsize);
}

void _0RL_cd_acfd8f3c9dc70dc8_00000000::marshalReturnedValues(cdrStream& _n)
{
  result >>= _n;

}

void _0RL_cd_acfd8f3c9dc70dc8_00000000::unmarshalReturnedValues(cdrStream& _n)
{
  (testOpenRTM::PortStatus&)result <<= _n;

}

const char* const _0RL_cd_acfd8f3c9dc70dc8_00000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_acfd8f3c9dc70dc8_10000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_acfd8f3c9dc70dc8_00000000* tcd = (_0RL_cd_acfd8f3c9dc70dc8_00000000*)cd;
  testOpenRTM::_impl_InPortCdr* impl = (testOpenRTM::_impl_InPortCdr*) svnt->_ptrToInterface(testOpenRTM::InPortCdr::_PD_repoId);
  
  tcd->result = impl->put(tcd->argc_0_);
}

testOpenRTM::PortStatus testOpenRTM::_objref_InPortCdr::put(const ::testOpenRTM::CdrData& data)
{
  _impl_InPortCdr* _s = _shortcut;
  if (_s) {
    if (!*_invalid) {
      return _s->put(data);
    }
    else {
      _enableShortcut(0,0);
      // drop through to normal invoke
    }
  }
  _0RL_cd_acfd8f3c9dc70dc8_00000000 _call_desc(_0RL_lcfn_acfd8f3c9dc70dc8_10000000, "put", 4);
  _call_desc.arg_0 = &(::testOpenRTM::CdrData&) data;

  _invoke(_call_desc);
  return _call_desc.result;


}

testOpenRTM::PortStatus testOpenRTM::_objref_InPortCdr::put(const cdrMemoryStream& data)
{
  _0RL_cd_acfd8f3c9dc70dc8_00000000 _call_desc(_0RL_lcfn_acfd8f3c9dc70dc8_10000000, "put", 4);
  _call_desc.argc_0 = &(cdrMemoryStream&) data;

  _invoke(_call_desc);
  return _call_desc.result;
}

testOpenRTM::_pof_InPortCdr::~_pof_InPortCdr() {}


omniObjRef*
testOpenRTM::_pof_InPortCdr::newObjRef(omniIOR* ior, omniIdentity* id)
{
  return new ::testOpenRTM::_objref_InPortCdr(ior, id);
}


::CORBA::Boolean
testOpenRTM::_pof_InPortCdr::is_a(const char* id) const
{
  if (omni::ptrStrMatch(id, ::testOpenRTM::InPortCdr::_PD_repoId))
    return 1;
  
  return 0;
}

const testOpenRTM::_pof_InPortCdr _the_pof_testOpenRTM_mInPortCdr;

testOpenRTM::_impl_InPortCdr::~_impl_InPortCdr() {}


::CORBA::Boolean
testOpenRTM::_impl_InPortCdr::_dispatch(omniCallHandle& _handle)
{
  const char* op = _handle.operation_name();

  if (omni::strMatch(op, "put")) {

    _0RL_cd_acfd8f3c9dc70dc8_00000000 _call_desc(_0RL_lcfn_acfd8f3c9dc70dc8_10000000, "put", 4, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }


  return 0;
}

void*
testOpenRTM::_impl_InPortCdr::_ptrToInterface(const char* id)
{
  if (id == ::testOpenRTM::InPortCdr::_PD_repoId)
    return (::testOpenRTM::_impl_InPortCdr*) this;
  
  if (id == ::CORBA::Object::_PD_repoId)
    return (void*) 1;

  if (omni::strMatch(id, ::testOpenRTM::InPortCdr::_PD_repoId))
    return (::testOpenRTM::_impl_InPortCdr*) this;
  
  if (omni::strMatch(id, ::CORBA::Object::_PD_repoId))
    return (void*) 1;
  return 0;
}

const char*
testOpenRTM::_impl_InPortCdr::_mostDerivedRepoId()
{
  return ::testOpenRTM::InPortCdr::_PD_repoId;
}

testOpenRTM::OutPortCdr_ptr testOpenRTM::OutPortCdr_Helper::_nil() {
  return ::testOpenRTM::OutPortCdr::_nil();
}

::CORBA::Boolean testOpenRTM::OutPortCdr_Helper::is_nil(::testOpenRTM::OutPortCdr_ptr p) {
  return ::CORBA::is_nil(p);

}

void testOpenRTM::OutPortCdr_Helper::release(::testOpenRTM::OutPortCdr_ptr p) {
  ::CORBA::release(p);
}

void testOpenRTM::OutPortCdr_Helper::marshalObjRef(::testOpenRTM::OutPortCdr_ptr obj, cdrStream& s) {
  ::testOpenRTM::OutPortCdr::_marshalObjRef(obj, s);
}

testOpenRTM::OutPortCdr_ptr testOpenRTM::OutPortCdr_Helper::unmarshalObjRef(cdrStream& s) {
  return ::testOpenRTM::OutPortCdr::_unmarshalObjRef(s);
}

void testOpenRTM::OutPortCdr_Helper::duplicate(::testOpenRTM::OutPortCdr_ptr obj) {
  if (obj && !obj->_NP_is_nil())  omni::duplicateObjRef(obj);
}

testOpenRTM::OutPortCdr_ptr
testOpenRTM::OutPortCdr::_duplicate(::testOpenRTM::OutPortCdr_ptr obj)
{
  if (obj && !obj->_NP_is_nil())  omni::duplicateObjRef(obj);
  return obj;
}

testOpenRTM::OutPortCdr_ptr
testOpenRTM::OutPortCdr::_narrow(::CORBA::Object_ptr obj)
{
  if (!obj || obj->_NP_is_nil() || obj->_NP_is_pseudo()) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_realNarrow(_PD_repoId);
  return e ? e : _nil();
}


testOpenRTM::OutPortCdr_ptr
testOpenRTM::OutPortCdr::_unchecked_narrow(::CORBA::Object_ptr obj)
{
  if (!obj || obj->_NP_is_nil() || obj->_NP_is_pseudo()) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_uncheckedNarrow(_PD_repoId);
  return e ? e : _nil();
}

testOpenRTM::OutPortCdr_ptr
testOpenRTM::OutPortCdr::_nil()
{
#ifdef OMNI_UNLOADABLE_STUBS
  static _objref_OutPortCdr _the_nil_obj;
  return &_the_nil_obj;
#else
  static _objref_OutPortCdr* _the_nil_ptr = 0;
  if (!_the_nil_ptr) {
    omni::nilRefLock().lock();
    if (!_the_nil_ptr) {
      _the_nil_ptr = new _objref_OutPortCdr;
      registerNilCorbaObject(_the_nil_ptr);
    }
    omni::nilRefLock().unlock();
  }
  return _the_nil_ptr;
#endif
}

const char* testOpenRTM::OutPortCdr::_PD_repoId = "IDL:testOpenRTM/OutPortCdr:1.0";


testOpenRTM::_objref_OutPortCdr::~_objref_OutPortCdr() {
  
}


testOpenRTM::_objref_OutPortCdr::_objref_OutPortCdr(omniIOR* ior, omniIdentity* id) :
   omniObjRef(::testOpenRTM::OutPortCdr::_PD_repoId, ior, id, 1)
   ,
   _shortcut(0)
{
  _PR_setobj(this);
}

void*
testOpenRTM::_objref_OutPortCdr::_ptrToObjRef(const char* id)
{
  if (id == ::testOpenRTM::OutPortCdr::_PD_repoId)
    return (::testOpenRTM::OutPortCdr_ptr) this;
  
  if (id == ::CORBA::Object::_PD_repoId)
    return (::CORBA::Object_ptr) this;

  if (omni::strMatch(id, ::testOpenRTM::OutPortCdr::_PD_repoId))
    return (::testOpenRTM::OutPortCdr_ptr) this;
  
  if (omni::strMatch(id, ::CORBA::Object::_PD_repoId))
    return (::CORBA::Object_ptr) this;

  return 0;
}

void
testOpenRTM::_objref_OutPortCdr::_enableShortcut(omniServant* _svt, const _CORBA_Boolean* _inv)
{
  if (_svt)
    _shortcut = (_impl_OutPortCdr*)_svt->_ptrToInterface(::testOpenRTM::OutPortCdr::_PD_repoId);
  else
    _shortcut = 0;
  _invalid  = _inv;
  
}


//
// Code for testOpenRTM::OutPortCdr::get

// Proxy call descriptor class. Mangled signature:
//  _ctestOpenRTM_mPortStatus_o_ctestOpenRTM_mCdrData
class _0RL_cd_acfd8f3c9dc70dc8_20000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_acfd8f3c9dc70dc8_20000000(LocalCallFn lcfn, const char* op_, size_t oplen, _CORBA_Boolean upcall=0)
    : omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  
  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  static const char* const _user_exns[];

  testOpenRTM::CdrData_var arg_0;
  testOpenRTM::PortStatus result;
};

void _0RL_cd_acfd8f3c9dc70dc8_20000000::marshalReturnedValues(cdrStream& _n)
{
  result >>= _n;
  (const testOpenRTM::CdrData&) arg_0 >>= _n;

}

void _0RL_cd_acfd8f3c9dc70dc8_20000000::unmarshalReturnedValues(cdrStream& _n)
{
  (testOpenRTM::PortStatus&)result <<= _n;
  arg_0 = new testOpenRTM::CdrData;
  (testOpenRTM::CdrData&)arg_0 <<= _n;

}

const char* const _0RL_cd_acfd8f3c9dc70dc8_20000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_acfd8f3c9dc70dc8_30000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_acfd8f3c9dc70dc8_20000000* tcd = (_0RL_cd_acfd8f3c9dc70dc8_20000000*)cd;
  testOpenRTM::_impl_OutPortCdr* impl = (testOpenRTM::_impl_OutPortCdr*) svnt->_ptrToInterface(testOpenRTM::OutPortCdr::_PD_repoId);
  tcd->result = impl->get(tcd->arg_0.out());


}

testOpenRTM::PortStatus testOpenRTM::_objref_OutPortCdr::get(::testOpenRTM::CdrData_out data)
{
  _impl_OutPortCdr* _s = _shortcut;
  if (_s) {
    if (!*_invalid) {
      return _s->get(data);
    }
    else {
      _enableShortcut(0,0);
      // drop through to normal invoke
    }
  }
  _0RL_cd_acfd8f3c9dc70dc8_20000000 _call_desc(_0RL_lcfn_acfd8f3c9dc70dc8_30000000, "get", 4);


  _invoke(_call_desc);
  data = _call_desc.arg_0._retn();
  return _call_desc.result;


}

testOpenRTM::_pof_OutPortCdr::~_pof_OutPortCdr() {}


omniObjRef*
testOpenRTM::_pof_OutPortCdr::newObjRef(omniIOR* ior, omniIdentity* id)
{
  return new ::testOpenRTM::_objref_OutPortCdr(ior, id);
}


::CORBA::Boolean
testOpenRTM::_pof_OutPortCdr::is_a(const char* id) const
{
  if (omni::ptrStrMatch(id, ::testOpenRTM::OutPortCdr::_PD_repoId))
    return 1;
  
  return 0;
}

const testOpenRTM::_pof_OutPortCdr _the_pof_testOpenRTM_mOutPortCdr;

testOpenRTM::_impl_OutPortCdr::~_impl_OutPortCdr() {}


::CORBA::Boolean
testOpenRTM::_impl_OutPortCdr::_dispatch(omniCallHandle& _handle)
{
  const char* op = _handle.operation_name();

  if (omni::strMatch(op, "get")) {

    _0RL_cd_acfd8f3c9dc70dc8_20000000 _call_desc(_0RL_lcfn_acfd8f3c9dc70dc8_30000000, "get", 4, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }


  return 0;
}

void*
testOpenRTM::_impl_OutPortCdr::_ptrToInterface(const char* id)
{
  if (id == ::testOpenRTM::OutPortCdr::_PD_repoId)
    return (::testOpenRTM::_impl_OutPortCdr*) this;
  
  if (id == ::CORBA::Object::_PD_repoId)
    return (void*) 1;

  if (omni::strMatch(id, ::testOpenRTM::OutPortCdr::_PD_repoId))
    return (::testOpenRTM::_impl_OutPortCdr*) this;
  
  if (omni::strMatch(id, ::CORBA::Object::_PD_repoId))
    return (void*) 1;
  return 0;
}

const char*
testOpenRTM::_impl_OutPortCdr::_mostDerivedRepoId()
{
  return ::testOpenRTM::OutPortCdr::_PD_repoId;
}

POA_testOpenRTM::InPortCdr::~InPortCdr() {}

POA_testOpenRTM::OutPortCdr::~OutPortCdr() {}

