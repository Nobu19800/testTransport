#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys
from omniORB import CORBA
import testOpenRTM
import OpenRTM_aist
import RTC
import time


if __name__ == '__main__':
    orb = CORBA.ORB_init(sys.argv, CORBA.ORB_ID)
    with open('ior.txt', 'r') as f:
        ior = f.read()
    obj = orb.string_to_object(ior)
    to = obj._narrow(testOpenRTM.testService)
    if to is None:
        sys.exit(1)

    datasize = 100
    count = 0
    Flag = True

    while Flag:
        data = OpenRTM_aist.instantiateDataType(RTC.CameraImage)
        data.pixels = b""

        maxsize = 12000001
        datacount = 50

        logmul = [2.0, 2.5, 2.0]

        if datasize > maxsize:
            print("finish")
            Flag = False
            continue

        data.height = 100
        data.width = int(datasize/data.height/3)
        data.pixels = b" " * int(data.height * data.width * 3)
        data.format = "rgb8"

        #tm = time.time()
        #tm_f = float(tm - int(tm))
        #data.tm.sec = int(float(tm) - float(tm_f))
        #data.tm.nsec = int(float(tm_f) * float(1000000000))

        OpenRTM_aist.setTimestamp(data)
        to.put(data)

        count += 1

        if count % datacount == 0:
            print(data.height*data.width*3)
            datasize = int(
                datasize*logmul[int(count / datacount) % 3])
        time.sleep(0.01)

    orb.shutdown()
