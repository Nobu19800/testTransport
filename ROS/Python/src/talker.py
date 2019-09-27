#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-


import rospy
from sensor_msgs.msg import Image
import time



def talker():
    pub = rospy.Publisher('chatter', Image, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(500)

    datasize = 100
    count = 0

    while not rospy.is_shutdown():
        msg = Image()
        maxsize = 12000001
        datacount = 50

        logmul = [2.0, 2.5, 2.0]

        if datasize > maxsize:
        	print("finish")
        	return

        msg.height = 100
        msg.width = datasize/msg.height/3
        msg.encoding = "rgb8"
        msg.step = 1920
        msg.data = " "*(msg.height*msg.width*3)

        
        #rospy.loginfo(hello_str)
        
        tm = time.time()
        tm_f = float(tm - long(tm))
        msg.header.stamp.secs = long(float(tm) - float(tm_f))
        msg.header.stamp.nsecs = long(float(tm_f) * float(1000000000))

        pub.publish(msg)

        count += 1
        if count%datacount == 0:
        	print(msg.height*msg.width*3)
        	datasize = int(datasize*logmul[(count/datacount)%3])

        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass



    