# 1. testTransport
OpenRTM-aist、ROS、ROS2、Fast-RTPS、omniORB、TAOのデータ転送速度計測用のC++ソースファイル、Pythonスクリプト。

<!-- TOC -->

- [testTransport](#testtransport)
    - [OpenRTM-aist(C++)](#openrtm-aistc)
        - [omniORB](#omniorb)
            - [ビルド手順](#ビルド手順)
                - [Windows](#windows)
                - [Ubuntu](#ubuntu)
            - [実行手順](#実行手順)
                - [Windows](#windows)
                    - [CORBA通信](#corba通信)
                    - [ROS通信](#ros通信)
                - [Ubuntu](#ubuntu)
                    - [CORBA通信](#corba通信)
                    - [ROS通信](#ros通信)
                    - [ROS2通信](#ros2通信)
        - [TAO](#tao)
            - [ビルド手順](#ビルド手順)
                - [Windows](#windows)
                - [Ubuntu](#ubuntu)
            - [実行手順](#実行手順)
                - [Windows](#windows)
                - [Ubuntu](#ubuntu)
    - [ROS(C++)](#rosc)
        - [ビルド手順](#ビルド手順)
            - [Windows](#windows)
            - [Ubuntu](#ubuntu)
        - [実行手順](#実行手順)
            - [Windows](#windows)
            - [Ubuntu](#ubuntu)
    - [ROS2(C++)](#ros2c)
        - [ビルド手順](#ビルド手順)
            - [Windows](#windows)
            - [Ubuntu](#ubuntu)
        - [実行手順](#実行手順)
            - [Windows](#windows)
            - [Ubuntu](#ubuntu)
    - [Fast-RTPS(C++)](#fast-rtpsc)
        - [ビルド手順](#ビルド手順)
            - [Windows](#windows)
            - [Ubuntu](#ubuntu)
        - [実行手順](#実行手順)
            - [Windows](#windows)

<!-- /TOC -->

## 1.1. OpenRTM-aist(C++)


```

cmake .. -DCMAKE_INSTALL_PREFIX=xxxxxxxxxxxxxxxxxx
cmake --build . --target install --config Release
```

### 1.1.1. omniORB

#### 1.1.1.1. ビルド手順

##### 1.1.1.1.1. Windows
以下のコマンドを`OpenRTM/C++/CameraTestIn`、`CameraTestOut`で実行。

```
mkdir build
cd build
cmake .. -DOpenRTM_DIR=${OpenRTM-aistのインストールディレクトリ}/2.0.0/cmake -G "Visual Studio 15 2017" -A x64
cmake --build . --config Release
```


##### 1.1.1.1.2. Ubuntu
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


#### 1.1.1.2. 実行手順
実行前にネームサーバーを起動しておく。

##### 1.1.1.2.1. Windows

###### 1.1.1.2.1.1. CORBA通信

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

###### 1.1.1.2.1.2. ROS通信

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

##### 1.1.1.2.2. Ubuntu

###### 1.1.1.2.2.1. CORBA通信

```
src/CameraTestOutComp -f ../conf/iiop/rtc.conf
```

```
src/CameraTestInComp -f ../conf/iiop/rtc.conf
```

###### 1.1.1.2.2.2. ROS通信

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

###### 1.1.1.2.2.3. ROS2通信

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


### 1.1.2. TAO

#### 1.1.2.1. ビルド手順

##### 1.1.2.1.1. Windows

```
cmake .. -DOpenRTM_DIR=${OpenRTM-aistのインストールディレクトリ}/cmake -G "Visual Studio 15 2017" -A x64
cmake --build . --config Release
```

##### 1.1.2.1.2. Ubuntu
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

#### 1.1.2.2. 実行手順
実行前にネームサーバーを起動しておく。

##### 1.1.2.2.1. Windows

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

##### 1.1.2.2.2. Ubuntu
TAOを任意のディレクトリにインストールしている場合は`LD_LIBRARY_PATH`を設定する。

```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${ACEのインストールディレクトリ}/lib
```

```
src/CameraTestOutComp -f ../conf/iiop/rtc.conf
```

```
src/CameraTestInComp -f ../conf/iiop/rtc.conf
```

## 1.2. ROS(C++)

### 1.2.1. ビルド手順

#### 1.2.1.1. Windows

```
xcopy testTransport\ROS\C++ C:\catkin_ws\src\testTransport_cpp
F:\opt\start_ros.bat
cd C:\catkin_ws
set_rosws
devel\setup.bat
catkin_make
```

#### 1.2.1.2. Ubuntu

```
git clone https://github.com/Nobu19800/testTransport
cp -r testTransport/ROS/C++ ~/catkin_ws/src/testTransport_cpp
```


```
cd ~/catkin_ws
source ./devel/setup.bash
catkin_make
```

### 1.2.2. 実行手順

#### 1.2.2.1. Windows
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

#### 1.2.2.2. Ubuntu

```
roscore
```

```
rosrun cameratest listener
```

```
rosrun cameratest talker
```


## 1.3. ROS2(C++)

### 1.3.1. ビルド手順
colconをインストールする。

```
C:\dev\ros2\local_setup.bat
pip install -U colcon-common-extensions
mkdir C:\ros2_ws
cd C:\ros2_ws
mkdir src
colcon build
```

#### 1.3.1.1. Windows


以下のコマンドは`Developer Command Prompt for VS 2019`で実行する。

```
xcopy testTransport\ROS2\C++ C:\dev\ros2\src\testTransport_cpp
C:\dev\ros2\local_setup.bat
cd C:\ros2_ws
colcon build
```

```

```


#### 1.3.1.2. Ubuntu
```
cp -r testTransport/ROS2/C++ ~/ros2_ws/src/testTransport_cpp
cd ~/ros2_ws
source install/local_setup.bash
colcon build
```

### 1.3.2. 実行手順

#### 1.3.2.1. Windows

```
call install/local_setup.bat
build\ros2test\Release\subscriber.exe
```

```
call install/local_setup.bat
build\ros2test\Release\publisher.exe
```

#### 1.3.2.2. Ubuntu

```
source install/local_setup.bash
ros2 run ros2test subscriber
```

```
source install/local_setup.bash
ros2 run ros2test publisher
```

## 1.4. Fast-RTPS(C++)

### 1.4.1. ビルド手順

#### 1.4.1.1. Windows
```
cd testTransport\FastRTPS
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

#### 1.4.1.2. Ubuntu
```
cd testTransport/FastRTPS
mkdir build
cd build
cmake ..
cmake --build . --config Release -- -j$(nproc)
```

### 1.4.2. 実行手順

#### 1.4.2.1. Windows
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
