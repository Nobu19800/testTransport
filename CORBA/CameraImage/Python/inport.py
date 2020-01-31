#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys
from omniORB import CORBA, PortableServer
import testOpenRTM
import testOpenRTM__POA
import OpenRTM_aist
import threading


class testOpenRTM_impl(testOpenRTM__POA.testService):
    def __init__(self):
        self._file = open("cameratestin.txt", mode='w')
        self._datasize = 0
        self._data = []
        self._mutex = threading.RLock()

    def put(self, data):
        guard = OpenRTM_aist.ScopedLock(self._mutex)
        try:
            if data and self._datasize != len(data.pixels):
                self.save(len(data.pixels))

            start = OpenRTM_aist.TimeValue(
                data.tm.sec, data.tm.nsec / 1000)
            end = OpenRTM_aist.Time().getTime()
            diff = (end - start).toDouble()
            self._data.append(diff)
            self._datasize = len(data.pixels)
        except:
            import traceback
            print(traceback.format_exc())

    def save(self, newsize):
        if len(self._data) == 0:
            self._datasize = newsize
            return
        avg = 0.0
        for data in self._data:
            avg += data
        avg /= len(self._data)
        print(self._datasize, avg, len(self._data))
        self._file.write(str(self._datasize)+"\t"+str(avg) +
                         "\t"+str(len(self._data))+"\n")
        self._data = []
        self._datasize = newsize


if __name__ == "__main__":
    orb = CORBA.ORB_init(sys.argv, CORBA.ORB_ID)
    poa = orb.resolve_initial_references("RootPOA")
    t_i = testOpenRTM_impl()
    to = t_i._this()
    with open('ior.txt', 'w') as f:
        f.write(orb.object_to_string(to))
    poaManager = poa._get_the_POAManager()
    poaManager.activate()
    try:
        orb.run()
    except:
        pass
    t_i.save(0)
