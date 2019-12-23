#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-


from setuptools import setup

package_name = 'ros2testpy'

setup(
    name=package_name,
    version='0.0.1',
    packages=['ros2testpy'],
    data_files=[
        ('share/ament_index/resource_index/packages',
         ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    author='aaaaaaaaaaaa',
    author_email='unko@unko.org',
    maintainer='aaaaaaaaa',
    maintainer_email='unko@unko.org',
    keywords=['ROS'],
    classifiers=[
        'Intended Audience :: Developers',
        'License :: OSI Approved :: LGPL',
        'Programming Language :: Python',
        'Topic :: Software Development',
    ],
    description='',
    license='LGPL',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'listener = ros2testpy.listener:main',
            'talker = ros2testpy.talker:main',
        ],
    },
)
