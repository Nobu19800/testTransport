#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file CameraTestInPy.py
 @brief ModuleDescription
 @date $Date$


"""
import threading
import OpenRTM_aist
import RTC
import sys
import time
sys.path.append(".")

# Import RTM module


# Import Service implementation class
# <rtc-template block="service_impl">

# </rtc-template>

# Import Service stub modules
# <rtc-template block="consumer_import">
# </rtc-template>


# This module's spesification
# <rtc-template block="module_spec">
cameratestinpy_spec = ["implementation_id", "CameraTestInPy",
                       "type_name",         "CameraTestInPy",
                       "description",       "ModuleDescription",
                       "version",           "1.0.0",
                       "vendor",            "VenderName",
                       "category",          "Category",
                       "activity_type",     "STATIC",
                       "max_instance",      "1",
                       "language",          "Python",
                       "lang_type",         "SCRIPT",
                       ""]
# </rtc-template>


class DataListener(OpenRTM_aist.ConnectorDataListenerT):
    def __init__(self, f):
        self._file = f
        self._datasize = 0
        self._data = []
        self._mutex = threading.RLock()

    def __del__(self):
        pass

    def __call__(self, info, data):
        try:
            if not self._data or self._datasize == len(data.pixels):
                start = OpenRTM_aist.TimeValue(data.tm.sec, data.tm.nsec/1000)
                end = OpenRTM_aist.Time().getTime()
                diff = (end - start).toDouble()
                self._data.append(diff)
            else:
                self.save(len(data.pixels))
        except:
            import traceback
            print(traceback.format_exc())
        return OpenRTM_aist.ConnectorListenerStatus.NO_CHANGE, data

    def save(self, newsize):
        if len(self._data) == 0:
            self._datasize = newsize
            return
        avg = 0.0
        for data in self._data:
            avg += data
        avg /= len(self._data)
        print(self._datasize, avg, len(self._data))
        self._data = []
        self._file.write(str(self._datasize)+"\t"+str(avg)+"\n")
        self._datasize = newsize

##
# @class CameraTestInPy
# @brief ModuleDescription
#
#


class CameraTestInPy(OpenRTM_aist.DataFlowComponentBase):

        ##
        # @brief constructor
        # @param manager Maneger Object
        #
    def __init__(self, manager):
        OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

        self._d_in = OpenRTM_aist.instantiateDataType(RTC.CameraImage)
        """
		"""
        self._inIn = OpenRTM_aist.InPort("in", self._d_in)

        # initialize of configuration-data.
        # <rtc-template block="init_conf_param">

        # </rtc-template>

    ##
    #
    # The initialize action (on CREATED->ALIVE transition)
    # formaer rtc_init_entry()
    #
    # @return RTC::ReturnCode_t
    #
    #

    def onInitialize(self):
        # Bind variables and configuration variable

        # Set InPort buffers
        self.addInPort("in", self._inIn)
        self._file = open("cameratestin.txt", mode='w')
        self._datalistener = DataListener(self._file)
        self._inIn.addConnectorDataListener(OpenRTM_aist.ConnectorDataListenerType.ON_BUFFER_WRITE,
                                            self._datalistener)

        # Set OutPort buffers

        # Set service provider to Ports

        # Set service consumers to Ports

        # Set CORBA Service Ports

        return RTC.RTC_OK

    ###
    ##
    # The finalize action (on ALIVE->END transition)
    # formaer rtc_exiting_entry()
    ##
    # @return RTC::ReturnCode_t
    #
    ##
    # def onFinalize(self):
    #
    #	return RTC.RTC_OK

    ###
    ##
    # The startup action when ExecutionContext startup
    # former rtc_starting_entry()
    ##
    # @param ec_id target ExecutionContext Id
    ##
    # @return RTC::ReturnCode_t
    ##
    ##
    # def onStartup(self, ec_id):
    #
    #	return RTC.RTC_OK

    ###
    ##
    # The shutdown action when ExecutionContext stop
    # former rtc_stopping_entry()
    ##
    # @param ec_id target ExecutionContext Id
    ##
    # @return RTC::ReturnCode_t
    ##
    ##
    # def onShutdown(self, ec_id):
    #
    #	return RTC.RTC_OK

    ##
    #
    # The activated action (Active state entry action)
    # former rtc_active_entry()
    #
    # @param ec_id target ExecutionContext Id
    #
    # @return RTC::ReturnCode_t
    #
    #
    def onActivated(self, ec_id):

        return RTC.RTC_OK

    ##
    #
    # The deactivated action (Active state exit action)
    # former rtc_active_exit()
    #
    # @param ec_id target ExecutionContext Id
    #
    # @return RTC::ReturnCode_t
    #
    #
    def onDeactivated(self, ec_id):
        self._datalistener.save(0)
        self._file.close()
        return RTC.RTC_OK

    ##
    #
    # The execution action that is invoked periodically
    # former rtc_active_do()
    #
    # @param ec_id target ExecutionContext Id
    #
    # @return RTC::ReturnCode_t
    #
    #
    def onExecute(self, ec_id):

        return RTC.RTC_OK

    ###
    ##
    # The aborting action when main logic error occurred.
    # former rtc_aborting_entry()
    ##
    # @param ec_id target ExecutionContext Id
    ##
    # @return RTC::ReturnCode_t
    ##
    ##
    # def onAborting(self, ec_id):
    #
    #	return RTC.RTC_OK

    ###
    ##
    # The error action in ERROR state
    # former rtc_error_do()
    ##
    # @param ec_id target ExecutionContext Id
    ##
    # @return RTC::ReturnCode_t
    ##
    ##
    # def onError(self, ec_id):
    #
    #	return RTC.RTC_OK

    ###
    ##
    # The reset action that is invoked resetting
    # This is same but different the former rtc_init_entry()
    ##
    # @param ec_id target ExecutionContext Id
    ##
    # @return RTC::ReturnCode_t
    ##
    ##
    # def onReset(self, ec_id):
    #
    #	return RTC.RTC_OK

    ###
    ##
    # The state update action that is invoked after onExecute() action
    # no corresponding operation exists in OpenRTm-aist-0.2.0
    ##
    # @param ec_id target ExecutionContext Id
    ##
    # @return RTC::ReturnCode_t
    ##

    ##
    # def onStateUpdate(self, ec_id):
    #
    #	return RTC.RTC_OK

    ###
    ##
    # The action that is invoked when execution context's rate is changed
    # no corresponding operation exists in OpenRTm-aist-0.2.0
    ##
    # @param ec_id target ExecutionContext Id
    ##
    # @return RTC::ReturnCode_t
    ##
    ##
    # def onRateChanged(self, ec_id):
    #
    #	return RTC.RTC_OK


def CameraTestInPyInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=cameratestinpy_spec)
    manager.registerFactory(profile,
                            CameraTestInPy,
                            OpenRTM_aist.Delete)


def MyModuleInit(manager):
    CameraTestInPyInit(manager)

    # Create a component
    comp = manager.createComponent("CameraTestInPy")


def main():
    mgr = OpenRTM_aist.Manager.init(sys.argv)
    mgr.setModuleInitProc(MyModuleInit)
    mgr.activateManager()
    mgr.runManager()


if __name__ == "__main__":
    main()
