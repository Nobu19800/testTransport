#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Image

import threading
import time


class Subscriber(Node):

    def __init__(self):
        super().__init__('Subscriber')
        self.subscription = self.create_subscription(
            Image,
            'chatter',
            self.listener_callback,
            10)

        self._file = open("cameratestin.txt", mode='w')
        self._datasize = 0
        self._data = []
        self._mutex = threading.RLock()

    def listener_callback(self, msg):
        # print(msg)
        #self.get_logger().info('I heard: "%s"' % msg.data)

        if msg and self._datasize != len(msg.data):
            self.save(len(msg.data))

        start = msg.header.stamp.sec + msg.header.stamp.nanosec/1000000000.0
        end = time.time()
        diff = end - start
        self._data.append(diff)
        self._datasize = len(msg.data)

    def save(self, newsize):
        if len(self._data) == 0:
            self._datasize = newsize
            return
        avg = 0.0
        for data in self._data:
            avg += data
        avg /= len(self._data)
        self._data = []

        print(self._datasize, avg, len(self._data))
        self._file.write(str(self._datasize)+"\t"+str(avg) +
                         "\t"+str(len(self._data))+"\n")
        datasize = newsize


def main(args=None):
    rclpy.init(args=args)

    subscriber = Subscriber()

    rclpy.spin(subscriber)

    rclpy.shutdown()
    subscriber.save(0)


if __name__ == '__main__':
    main()
