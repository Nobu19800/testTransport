OpenRTM-aist、ROS、ROS2、Fast-RTPS、omniORB、TAOのデータ転送速度計測用のC++ソースファイル、Pythonスクリプト。


<!-- TOC -->autoauto- [計測用プログラムの概要](#計測用プログラムの概要)auto    - [OpenRTM](#openrtm)auto    - [ROS](#ros)auto    - [ROS2](#ros2)auto    - [FastRTPS](#fastrtps)auto    - [CORBA](#corba)auto- [ビルド、実行](#ビルド実行)auto    - [OpenRTM-aist(C++)](#openrtm-aistc)auto        - [omniORB](#omniorb)auto            - [ビルド手順](#ビルド手順)auto                - [Windows](#windows)auto                - [Ubuntu](#ubuntu)auto            - [実行手順](#実行手順)auto                - [Windows](#windows-1)auto                    - [CORBA通信](#corba通信)auto                    - [ROS通信](#ros通信)auto                - [Ubuntu](#ubuntu-1)auto                    - [CORBA通信](#corba通信-1)auto                    - [ROS通信](#ros通信-1)auto                    - [ROS2通信](#ros2通信)auto        - [TAO](#tao)auto            - [ビルド手順](#ビルド手順-1)auto                - [Windows](#windows-2)auto                - [Ubuntu](#ubuntu-2)auto            - [実行手順](#実行手順-1)auto                - [Windows](#windows-3)auto                - [Ubuntu](#ubuntu-3)auto    - [ROS(C++)](#rosc)auto        - [ビルド手順](#ビルド手順-2)auto            - [Windows](#windows-4)auto            - [Ubuntu](#ubuntu-4)auto        - [実行手順](#実行手順-2)auto            - [Windows](#windows-5)auto            - [Ubuntu](#ubuntu-5)auto    - [ROS2(C++)](#ros2c)auto        - [ビルド手順](#ビルド手順-3)auto            - [Windows](#windows-6)auto            - [Ubuntu](#ubuntu-6)auto        - [実行手順](#実行手順-3)auto            - [Windows](#windows-7)auto            - [Ubuntu](#ubuntu-7)auto    - [Fast-RTPS(C++)](#fast-rtpsc)auto        - [ビルド手順](#ビルド手順-4)auto            - [Windows](#windows-8)auto            - [Ubuntu](#ubuntu-8)auto        - [実行手順](#実行手順-4)auto            - [Windows](#windows-9)auto            - [Ubuntu](#ubuntu-9)auto    - [CORBA(C++)](#corbac)auto        - [omniORB](#omniorb-1)auto            - [ビルド手順](#ビルド手順-5)auto                - [Windows](#windows-10)auto                - [Ubuntu](#ubuntu-10)auto            - [実行手順](#実行手順-5)auto                - [Windows](#windows-11)auto                - [Ubuntu](#ubuntu-11)auto        - [TAO](#tao-1)auto            - [ビルド手順](#ビルド手順-6)auto                - [Windows](#windows-12)auto                - [Ubuntu](#ubuntu-12)auto            - [実行手順](#実行手順-6)auto                - [Windows](#windows-13)auto                - [Ubuntu](#ubuntu-13)auto    - [OpenRTM-aist(Python)](#openrtm-aistpython)auto        - [実行手順](#実行手順-7)auto            - [Windows](#windows-14)auto            - [Ubuntu](#ubuntu-14)auto    - [ROS(Python)](#rospython)auto        - [ビルド手順](#ビルド手順-7)auto            - [Windows](#windows-15)auto            - [Ubuntu](#ubuntu-15)auto        - [実行手順](#実行手順-8)auto            - [Windows](#windows-16)auto            - [Ubuntu](#ubuntu-16)auto    - [ROS2(Python)](#ros2python)auto        - [ビルド手順](#ビルド手順-8)auto            - [Windows](#windows-17)auto            - [Ubuntu](#ubuntu-17)auto        - [実行手順](#実行手順-9)auto            - [Windows](#windows-18)auto            - [Ubuntu](#ubuntu-18)auto    - [CORBA](#corba-1)auto        - [ビルド手順](#ビルド手順-9)auto            - [Windows](#windows-19)auto            - [Ubuntu](#ubuntu-19)auto        - [実行手順](#実行手順-10)auto            - [Windows](#windows-20)auto            - [Ubuntu](#ubuntu-20)autoauto<!-- /TOC -->
# 計測用プログラムの概要
## OpenRTM
OpenRTM-aistのデータポートの通信によるデータ転送の時間を計測。
設定ファイルによりシリアライザ、通信インターフェースを変更することで、IIOP、ROSTCP、DDSの通信に変更可能。
## ROS
## ROS2
## FastRTPS
## CORBA


# ビルド、実行
## OpenRTM-aist(C++)


```

cmake .. -DCMAKE_INSTALL_PREFIX=xxxxxxxxxxxxxxxxxx
cmake --build . --target install --config Release
```

### omniORB

#### ビルド手順

##### Windows
以下のコマンドを`OpenRTM/C++/CameraTestIn`、`CameraTestOut`で実行。

```
mkdir build
cd build
cmake .. -DOpenRTM_DIR=${OpenRTM-aistのインストールディレクトリ}/2.0.0/cmake -G "Visual Studio 15 2017" -A x64
cmake --build . --config Release
```


##### Ubuntu
```
git clone https://github.com/Nobu19800/testTransport
cd testTransport/OpenRTM/C++/CameraTestIn
mkdir build
cd build
cmake .. -DOpenRTM_DIR=${OpenRTM-aistのインストールディレクトリ}/lib/openrtm-2.0/cmake
cmake --build . --config Release -- -j$(nproc)
```

```
cd testTransport/OpenRTM/C++/CameraTestOut
mkdir build
cd build
cmake .. -DOpenRTM_DIR=${OpenRTM-aistのインストールディレクトリ}/lib/openrtm-2.0/cmake
cmake --build . --config Release -- -j$(nproc)
```


#### 実行手順
実行前にネームサーバーを起動しておく。

##### Windows

###### IIOP

必ずCameraTestOutCompから起動する。

```
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\bin\vc141;%PATH%
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\omniORB\4.2.3_vc141\bin\x86_win32;%PATH%
src\Release\CameraTestOutComp.exe -f ../conf/iiop/rtc.conf
```

```
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\bin\vc141;%PATH%
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\omniORB\4.2.3_vc141\bin\x86_win32;%PATH%
src\Release\CameraTestInComp.exe -f ../conf/iiop/rtc.conf
```

###### ROS通信

CameraTestIn、CameraTestOutの`conf/ros/rtc_ros.conf`を環境に合わせて変更する。


```
manager.modules.load_path: ${OpenRTM-aistのインストールディレクトリ}/2.0.0/ext/transport
```

roscoreを起動する。

```
F:\opt\start_ros.bat
roscore
```

```
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\bin\vc141;%PATH%
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\omniORB\4.2.3_vc141\bin\x86_win32;%PATH%
src\Release\CameraTestOutComp.exe -f ../conf/ros/rtc_ros.conf
```

```
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\bin\vc141;%PATH%
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\omniORB\4.2.3_vc141\bin\x86_win32;%PATH%
src\Release\CameraTestInComp.exe -f ../conf/ros/rtc_ros.conf
```

##### Ubuntu

###### IIOP

```
src/CameraTestOutComp -f ../conf/iiop/rtc.conf
```

```
src/CameraTestInComp -f ../conf/iiop/rtc.conf
```

###### ROS通信

CameraTestIn、CameraTestOutの`conf/ros/rtc_ros.conf`を環境に合わせて変更する。


```
manager.modules.load_path: ${OpenRTM-aistのインストールディレクトリ}/lib/openrtm-2.0/transport/
```

roscoreを起動する。

```
roscore
```



```
src/CameraTestOutComp -f ../conf/ros/rtc_ros.conf
```

```
src/CameraTestInComp -f ../conf/ros/rtc_ros.conf
```

###### ROS2通信

CameraTestIn、CameraTestOutの`conf/ros2/rtc_ros2_besteffort.conf`(もしくは`rtc_ros2_reliable.conf`)を環境に合わせて変更する。

```
manager.modules.load_path: ${OpenRTM-aistのインストールディレクトリ}/lib/openrtm-2.0/transport/
```


```
src/CameraTestOutComp -f ../conf/ros/rtc_ros2_besteffort.conf
```

```
src/CameraTestInComp -f ../conf/ros/rtc_ros2_besteffort.conf
```


### TAO

#### ビルド手順

##### Windows

###### IIOP

```
cmake .. -DOpenRTM_DIR=${OpenRTM-aistのインストールディレクトリ}/cmake -G "Visual Studio 15 2017" -A x64
cmake --build . --config Release
```

##### Ubuntu

```
git clone https://github.com/Nobu19800/testTransport
cd testTransport/OpenRTM/C++/CameraTestIn
mkdir build
cd build
cmake .. -DOpenRTM_DIR=${OpenRTM-aistのインストールディレクトリ}/lib/openrtm-2.0/cmake
cmake --build . --config Release -- -j$(nproc)
```

```
cd testTransport/OpenRTM/C++/CameraTestOut
mkdir build
cd build
cmake .. -DOpenRTM_DIR=${OpenRTM-aistのインストールディレクトリ}/lib/openrtm-2.0/cmake -DCORBA=TAO
cmake --build . --config Release -- -j$(nproc)
```

#### 実行手順
実行前にネームサーバーを起動しておく。

##### Windows

###### IIOP

必ずCameraTestOutCompから起動する。

```
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\bin\vc141;%PATH%
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\ACE\vc141\bin;%PATH%
src\Release\CameraTestOutComp.exe -f ../conf/iiop/rtc.conf
```

```
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\bin\vc141;%PATH%
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\ACE\vc141\bin;%PATH%
src\Release\CameraTestInComp.exe -f ../conf/iiop/rtc.conf
```

###### DIOP

```
cp ..\conf/diop\svc.conf .\
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\bin\vc141;%PATH%
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\ACE\vc141\bin;%PATH%
src\Release\CameraTestOutComp.exe -f ../conf/diop/rtc.conf
```

```
cp ..\conf\diop\svc.conf .\
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\bin\vc141;%PATH%
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\ACE\vc141\bin;%PATH%
src\Release\CameraTestInComp.exe -f ../conf/diop/rtc.conf
```

##### Ubuntu

TAOを任意のディレクトリにインストールしている場合は`LD_LIBRARY_PATH`を設定する。

```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${ACEのインストールディレクトリ}/lib
```

###### IIOP

```
src/CameraTestOutComp -f ../conf/iiop/rtc.conf
```

```
src/CameraTestInComp -f ../conf/iiop/rtc.conf
```

###### DIOP

```
cp ../conf/diop/svc.conf ./
src/CameraTestOutComp -f ../conf/diop/rtc.conf
```

```
cp ../conf/diop/svc.conf ./
src/CameraTestInComp -f ../conf/diop/rtc.conf
```

## ROS(C++)

### ビルド手順

#### Windows

```
xcopy testTransport\ROS\C++ C:\catkin_ws\src\testTransport_cpp
F:\opt\start_ros.bat
cd C:\catkin_ws
set_rosws
devel\setup.bat
catkin_make
```

#### Ubuntu

```
git clone https://github.com/Nobu19800/testTransport
cp -r testTransport/ROS/C++ ~/catkin_ws/src/testTransport_cpp
```


```
cd ~/catkin_ws
source ./devel/setup.bash
catkin_make
```

### 実行手順

#### Windows
roscoreを起動する。

```
F:\opt\start_ros.bat
roscore
```

```
rosrun cameratest listener
```

```
rosrun cameratest talker
```

#### Ubuntu

```
roscore
```

```
rosrun cameratest listener
```

```
rosrun cameratest talker
```


## ROS2(C++)

### ビルド手順
colconをインストールする。

```
C:\dev\ros2\local_setup.bat
pip install -U colcon-common-extensions
mkdir C:\ros2_ws
cd C:\ros2_ws
mkdir src
colcon build
```

#### Windows


以下のコマンドは`Developer Command Prompt for VS 2019`で実行する。

```
xcopy testTransport\ROS2\C++ C:\dev\ros2\src\testTransport_cpp
C:\dev\ros2\local_setup.bat
cd C:\ros2_ws
colcon build
```

```

```


#### Ubuntu
```
cp -r testTransport/ROS2/C++ ~/ros2_ws/src/testTransport_cpp
cd ~/ros2_ws
source install/local_setup.bash
colcon build
```

### 実行手順

#### Windows

```
call install/local_setup.bat
build\ros2test\Release\subscriber.exe
```

```
call install/local_setup.bat
build\ros2test\Release\publisher.exe
```

#### Ubuntu

```
source install/local_setup.bash
ros2 run ros2test subscriber
```

```
source install/local_setup.bash
ros2 run ros2test publisher
```

## Fast-RTPS(C++)

### ビルド手順

#### Windows
```
cd testTransport\FastRTPS
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

#### Ubuntu
```
cd testTransport/FastRTPS
mkdir build
cd build
cmake ..
cmake --build . --config Release -- -j$(nproc)
```

### 実行手順

#### Windows
```
CameraImageTest publisher ../conf/test_qos_besteffort.xml
```
```
CameraImageTest subscriber ../conf/test_qos_besteffort.xml
```

#### Ubuntu
```
./CameraImageTest publisher ../conf/test_qos_besteffort.xml
```
```
./CameraImageTest subscriber ../conf/test_qos_besteffort.xml
```
## CORBA(C++)
### omniORB
#### ビルド手順
##### Windows

```
mkdir build
cd build
cmake .. -DOpenRTM_DIR=${OpenRTM-aistのインストールディレクトリ}/2.0.0/cmake -G "Visual Studio 15 2017" -A x64
cmake --build . --config Release
```

##### Ubuntu

```
git clone https://github.com/Nobu19800/testTransport
cd testTransport/CORBA/CameraImage/C++
mkdir build
cd build
cmake .. -DOpenRTM_DIR=${OpenRTM-aistのインストールディレクトリ}/lib/openrtm-2.0/cmake
cmake --build . --config Release -- -j$(nproc)
```

#### 実行手順
##### Windows

```
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\omniORB\4.2.3_vc141\bin\x86_win32;%PATH%
Release\CORBATestIn.exe
```

```
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\omniORB\4.2.3_vc141\bin\x86_win32;%PATH%
Release\CORBATestOut.exe
```


##### Ubuntu

```
./CORBATestIn.exe
```

```
./CORBATestOut.exe
```

### TAO
#### ビルド手順
##### Windows
```
cmake .. -DOpenRTM_DIR=${OpenRTM-aistのインストールディレクトリ}/cmake -G "Visual Studio 15 2017" -A x64
cmake --build . --config Release
```
##### Ubuntu
```
git clone https://github.com/Nobu19800/testTransport
cd testTransport/CORBA/CameraImage/C++
mkdir build
cd build
cmake .. -DOpenRTM_DIR=${OpenRTM-aistのインストールディレクトリ}/lib/openrtm-2.0/cmake
cmake --build . --config Release -- -j$(nproc)
```
#### 実行手順
##### Windows
```
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\ACE\vc141\bin;%PATH%
CORBATestIn.exe
```

```
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\ACE\vc141\bin;%PATH%
CORBATestOut.exe
```
##### Ubuntu
```
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\ACE\vc141\bin;%PATH%
./CORBATestIn.exe
```

```
set PATH=${OpenRTM-aistのインストールディレクトリ}\2.0.0\ACE\vc141\bin;%PATH%
./CORBATestOut
```

## OpenRTM-aist(Python)
### 実行手順
#### Windows

`CameraTestOutPy`、`CameraTestInPy`フォルダに移動して以下のコマンドを実行する。

```
python CameraTestOutPy.py -f conf/iiop/rtc.conf
```

```
python CameraTestInPy.py -f conf/iiop/rtc.conf
```
#### Ubuntu

```
git clone https://github.com/Nobu19800/testTransport
cd testTransport/OpenRTM/Python/CameraTestInPy
python CameraTestOutPy.py -f conf/iiop/rtc.conf
```

```
cd testTransport/OpenRTM/Python/CameraTestOutPy
python CameraTestInPy.py -f conf/iiop/rtc.conf
```

## ROS(Python)
### ビルド手順
#### Windows
```
xcopy testTransport\ROS\Python C:\catkin_ws\src\testTransport_py
F:\opt\start_ros.bat
cd C:\catkin_ws
set_rosws
devel\setup.bat
catkin_make
```
#### Ubuntu
```
git clone https://github.com/Nobu19800/testTransport
cp -r testTransport/ROS/Python ~/catkin_ws/src/testTransport_py
```


```
cd ~/catkin_ws
source ./devel/setup.bash
catkin_make
```

### 実行手順
#### Windows
roscoreを起動する。

```
F:\opt\start_ros.bat
roscore
```

```
rosrun cameratest listener.py
```

```
rosrun cameratest talker.py
```

#### Ubuntu

```
roscore
```

```
rosrun cameratest listener.py
```

```
rosrun cameratest talker.py
```


## ROS2(Python)
### ビルド手順
colconをインストールする。

```
C:\dev\ros2\local_setup.bat
pip install -U colcon-common-extensions
mkdir C:\ros2_ws
cd C:\ros2_ws
mkdir src
colcon build
```

#### Windows

```
xcopy testTransport\ROS2\Python C:\dev\ros2\src\testTransport_py
C:\dev\ros2\local_setup.bat
cd C:\ros2_ws
colcon build
```

```

```


#### Ubuntu

```
cp -r testTransport/ROS2/Python ~/ros2_ws/src/testTransport_py
cd ~/ros2_ws
source install/local_setup.bash
colcon build
```

### 実行手順
#### Windows

```
call install/local_setup.bat
python build\ros2testpy\build\lib\ros2testpy\subscriber.py
```

```
call install/local_setup.bat
python build\ros2testpy\build\lib\ros2testpy\publisher.py
```

#### Ubuntu



```
source install/local_setup.bash
ros2 run ros2testpy subscriber.py
```

```
source install/local_setup.bash
ros2 run ros2testpy publisher.py
```

## CORBA

### ビルド手順
#### Windows
`CameraImage`を実行する場合は`idlcompile.bat`を起動する。
#### Ubuntu
`CameraImage`を実行する場合は`idlcompile.sh`を起動する。

### 実行手順
#### Windows
```
python inport.py
```

```
python outport.py
```

#### Ubuntu

```
python inport.py
```

```
python outport.py
```
