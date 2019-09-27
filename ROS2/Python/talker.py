#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-


import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Image
import time


logmul = [2.0, 2.5, 2.0]
maxsize = 12000001
datacount = 50

class Publisher(Node):

    def __init__(self):
        super().__init__('publisher')
        self.publisher_ = self.create_publisher(Image, 'topic', 10)
        timer_period = 0.002
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self._datasize = 100
        self._count = 0
        

    def timer_callback(self):
        global logmul
        global maxsize
        global datacount

        if self._datasize > maxsize:
        	#print("finish")
        	return

        msg = Image()
        
        msg.height = 100
        msg.width = int(self._datasize/msg.height/3)
        msg.encoding = "rgb8"
        msg.step = 1920
        msg.data = b" "*(msg.height*msg.width*3)

        tm = time.time()
        tm_f = float(tm - int(tm))
        msg.header.stamp.sec = int(float(tm) - float(tm_f))
        msg.header.stamp.nanosec = int(float(tm_f) * float(1000000000))
        
        self.publisher_.publish(msg)
        #self.get_logger().info('Publishing: "%s"' % msg.data)
        
        self._count += 1
        if self._count%datacount == 0:
        	print(msg.height*msg.width*3)
        	self._datasize = int(self._datasize*logmul[int(self._count/datacount)%3])


def main(args=None):
    rclpy.init(args=args)

    publisher = Publisher()

    rclpy.spin(publisher)

    publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()



    