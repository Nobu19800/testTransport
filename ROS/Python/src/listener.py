#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import rospy
from sensor_msgs.msg import Image
import threading
import time

_file = open("cameratestin.txt", mode='w')
_datasize = 0
_data = []
_mutex = threading.RLock()


def callback(msg):
    global _data
    global _datasize

    if msg and _datasize != len(msg.data):
        save(len(msg.data))

    start = msg.header.stamp.secs + msg.header.stamp.nsecs/1000000000.0
    end = time.time()
    diff = end - start
    _data.append(diff)
    _datasize = len(msg.data)
    #rospy.loginfo(rospy.get_caller_id() + 'I heard %s', data.data)


def save(newsize):
    global _file
    global _data
    global _datasize
    if len(_data) == 0:
        _datasize = newsize
        return
    avg = 0.0
    for data in _data:
        avg += data
    avg /= len(_data)

    print(_datasize, avg, len(_data))
    _file.write(str(_datasize)+"\t"+str(avg)+"\t"+str(len(_data))+"\n")

    _data = []
    datasize = newsize


def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber('chatter', Image, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()


if __name__ == '__main__':
    listener()
